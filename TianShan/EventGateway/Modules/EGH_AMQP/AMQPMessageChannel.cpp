#include "AMQPMessageChannel.h"
#include "AMQPMessageTransporter.h"
#include <TimeUtil.h>
#include "amqp_tcp_socket.h"

#define MessageChannel_ExitTimeoutMSec      5000
#define MessageChannel_ResendIntevalMSec    2000
#define MessageChannel_ReConnectIntevalMSec 5000

#define MSGLOGFMT(_C, _X) "%-18s [%s:%d/%p] " _X, #_C, _name.c_str(), _chId, this

namespace EventGateway{
namespace AMQP{
using namespace ZQ::common;

std::string amqp_error_string(amqp_rpc_reply_t x)
{
	switch (x.reply_type)
	{
	case AMQP_RESPONSE_NORMAL:
		return "";

	case AMQP_RESPONSE_NONE:
		return std::string("missing RPC reply type");

	case AMQP_RESPONSE_LIBRARY_EXCEPTION:
		return std::string(amqp_error_string2(x.library_error));

	case AMQP_RESPONSE_SERVER_EXCEPTION:
		switch (x.reply.id)
		{
		case AMQP_CONNECTION_CLOSE_METHOD:
			{
				char buf[1024];
				memset(buf, 0, sizeof(buf));
				amqp_connection_close_t *m = (amqp_connection_close_t *) x.reply.decoded;
				sprintf_s(buf, sizeof(buf) -1, "server connection error %d, message: %.*s",m->reply_code,
					(int) m->reply_text.len, (char *) m->reply_text.bytes);
				return std::string(buf);						  
			}
		case AMQP_CHANNEL_CLOSE_METHOD:
			{
				char buf[1024];
				memset(buf, 0, sizeof(buf));
				amqp_channel_close_t *m = (amqp_channel_close_t *) x.reply.decoded;
				sprintf_s(buf, sizeof(buf) -1, "server channel error %d, message: %.*s",m->reply_code,
					(int) m->reply_text.len, (char *) m->reply_text.bytes);
				return std::string(buf);
			}
		default:
			char buf[1024];
			memset(buf, 0, sizeof(buf));
			sprintf_s(buf, sizeof(buf) -1, "unknown server error, method id 0x%08X", x.reply.id);
			return std::string(buf);
		}
		break;
	}
	return std::string("unknown server error");
}

MessageChannel::MessageChannel(MessageTransporter& messageTransporter, ZQ::common::Log& log, const ChannelConfig& config, const Freeze::ConnectionPtr& dbConn)
: _messageTransporter(messageTransporter),_log(log), _config(config), _queue(0), _conn(NULL), _socket(NULL)
{
    _name = _config.name;
	_chId   = _config.id;
	_exchange = _config.name;
	_exchangeType = (ExchangeType)_config.msgType;
	_queueName = _config.name;
	_routingKey= _config.name;
	_nConnOk = false;

    // create the safe queue
    _queue = new SafeQueue<MessageRecord>(dbConn, _config.name); // may throw here

    _quit = false;
	buildConnectLostLists();
	buildMessageProperties(_msgProps);
    notifyNewMessage(); // start the serve cycle
    start();
}
MessageChannel::~MessageChannel()
{
    // stop the sending thread
    _quit = true;
    notifyNewMessage(); // signal to quit thread
    _log(Log::L_INFO, MSGLOGFMT(MessageChannel, "signal the working thread to quit..."));
    if(waitHandle(MessageChannel_ExitTimeoutMSec))
    {
        // the thread can't quit normally
        _log(Log::L_WARNING, MSGLOGFMT(MessageChannel, "The thread can't quit normally in %d milliseconds, terminate it manually."), MessageChannel_ExitTimeoutMSec);
        terminate(0);
    }

	close();
    if(_queue)
    {
        try{
            delete _queue;
        } catch (...){}
        _queue = NULL;
    }
}
static void showAMQPMessage(const Message& msg, std::string& txt) {
    txt.clear();
    std::ostringstream buf;
    if(msg.size() == 1 && msg.begin()->first.empty()) {
        buf << "TextMessage{" << msg.begin()->second << "}";
    } else {
        buf << "MapMessage{";
        for(Message::const_iterator it = msg.begin(); it != msg.end(); ++it) {
            buf << it->first << ":" << it->second << ";";
        }
        buf << "}";
    }
    buf.str().swap(txt);
}

void MessageChannel::push(const Message& msg)
{
    ZQ::common::MutexGuard sync(_lockMessage);
    _queue->push(msg);
    notifyNewMessage();
    _log(Log::L_DEBUG, MSGLOGFMT(MessageChannel, "push() New message arrived, [%u] pending messages in the queue."), _queue->size());
}

int MessageChannel::run()
{ // the message sending thread
    _log(Log::L_INFO, MSGLOGFMT(MessageChannel, "working thread enter."));
    timeout_t waitTimeoutMSec = 0; // the timeout of waiting new message
    int64 ttl = _config.optionEnabled ? _config.TTL : 0;
    bool sentOK = false;
    int64 firstRetryStamp = 0;
    while(true)
    {
        _hNotifyNewMessage.wait(waitTimeoutMSec);
		
		// we can quit the thread safely now
		if(_quit)
		{
			break;
		}

		if(!_nConnOk)
		{
			if(!connect())
			{
				waitTimeoutMSec =  MessageChannel_ReConnectIntevalMSec; // retry after interval
				continue;
			}
		}

        Message msg;
        // take new message
        {
            ZQ::common::MutexGuard sync(_lockMessage);

            if(sentOK)
            {
                if(!_queue->empty())
                {
                    _queue->pop();
                }
                else
                {
                    // can not happen;
                }
                // update the status
                sentOK = false;
                waitTimeoutMSec = TIMEOUT_INF; // reset the timeout for new nessage

                _log(Log::L_DEBUG, MSGLOGFMT(MessageChannel, "run() Current message processing finished. [%u] pending messages in the queue."), _queue->size());
            }

            // we can quit the thread safely now
            if(_quit)
            {
                break;
            }

            if(!_queue->empty())
            {
                msg = _queue->front();
            }
            else
            {		
				checkConnection();
				buildTestMessage();
				SYS::sleep(30000);
                continue; // wait for new message's arrival
	
            }
        }

        // now we got the message, send it
        sentOK = send(msg);
        if(sentOK)
        {
            firstRetryStamp = 0; // reset the retry timer
            notifyNewMessage(); // need next cycle to remove the message from the queue
            std::string txt;
            showAMQPMessage(msg, txt);
            _log(Log::L_INFO, MSGLOGFMT(MessageChannel, "Sent out message:%s"), txt.c_str());
        }
        else
        { // can't send message, may the connection broken
            if(ttl > 0) { // discard the message if the retry time exceed ttl
                if(firstRetryStamp > 0) {
                    int64 retryCost = ZQ::common::now() - firstRetryStamp;
                    if(retryCost > ttl) {
                        // discard the message
                        sentOK = true; // just fake a successfully sending
                        firstRetryStamp = 0; // reset the retry timer
                        notifyNewMessage(); // need next cycle to remove the message from the queue
                        std::string txt;
                        showAMQPMessage(msg, txt);
                        _log(Log::L_WARNING, MSGLOGFMT(MessageChannel, "Discard the message due to can't send message in %lld msec. TTL:%lld, message:%s"), retryCost, ttl, txt.c_str());
                        continue;
                    }
                } else { // first retry, set the timer
                    firstRetryStamp = ZQ::common::now();
                }
            } else { // not discard the message
            }
            // pause the processing when the channel is closed
            waitTimeoutMSec = _nConnOk ? MessageChannel_ResendIntevalMSec : MessageChannel_ReConnectIntevalMSec; // retry after interval
            _log(Log::L_WARNING, MSGLOGFMT(MessageChannel, "Failed to send message, retry in [%d] milliseconds."), waitTimeoutMSec);
        }
    } // while(true)
    _log(Log::L_INFO, MSGLOGFMT(MessageChannel, "working thread leave."));
    return 0;
}
void MessageChannel::buildMessageProperties(amqp_basic_properties_t& props)
{
	_msgProps._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG|AMQP_BASIC_EXPIRATION_FLAG;;
	_msgProps.content_type = amqp_cstring_bytes("text/plain");
	//props.delivery_mode = AMQP_DELIVERY_PERSISTENT; /* persistent delivery mode */
	_msgProps.delivery_mode = AMQP_DELIVERY_NONPERSISTENT;
	_msgProps.expiration = amqp_cstring_bytes("300000");


	StringProperties::iterator it = _config.msgPropertiesString.begin();
	while(it!=  _config.msgPropertiesString.end())
	{
		if(it->first == "content_type")
		{
			_msgProps.content_type = amqp_cstring_bytes(it->second.c_str());
		}
		else if(it->first == "expiration")
		{
			_msgProps.expiration = amqp_cstring_bytes(it->second.c_str());
		}
		++it;
	}

	 IntProperties::iterator itInt = _config.msgPropertiesInt.begin();
	 while(itInt!=  _config.msgPropertiesInt.end())
	 {
		 if(itInt->first == "delivery_mode")
		 {
			 	_msgProps.delivery_mode = itInt->second;
		 }
		 ++itInt;
	 }
	  _log(Log::L_DEBUG, MSGLOGFMT(MessageChannel, "buildMessageProperties()"));
}
bool MessageChannel::send(const Message &msg)
{
	if(msg.size() == 1 && msg.begin()->first.empty())
	{ // treat as text message
		return publish(msg.begin()->second, _msgProps,_config.mandatory, _config.immediate);
	}
	return false;
}

void MessageChannel::notifyNewMessage()
{
    _hNotifyNewMessage.signal();
}

void MessageChannel::OnConnected(const std::string& notice) {
    _nConnOk = true;
    _log(Log::L_INFO, MSGLOGFMT(MessageChannel, "Connected: %s"), notice.c_str());
}
void MessageChannel::OnConnectionLost(const std::string& notice) {
    _nConnOk = false;
    _log(Log::L_INFO, MSGLOGFMT(MessageChannel, "ConnectionLost: %s"), notice.c_str());
}

std::string  MessageChannel::converExchangeType(const ExchangeType&  exchangeType)
{
	switch(exchangeType)
	{
	case Direct:
		return "direct";
	case Fanout:
		return "fanout";
	case Topic:
		return "topic";
	default:
		break;
	}
	return "unkonwn";
}

bool MessageChannel::close()
{
	if(!_nConnOk)
		return true;

	amqp_rpc_reply_t reply = amqp_connection_close(_conn, AMQP_REPLY_SUCCESS);
	if(reply.reply_type !=  AMQP_RESPONSE_NORMAL)
	{
		_log(ZQ::common::Log::L_ERROR, MSGLOGFMT(MessageChannel, "faile to closing connection with error:%s"), amqp_error_string(reply).c_str());
	}

	int nReply = amqp_destroy_connection(_conn);
	if(nReply!=  AMQP_STATUS_OK)
		_log(ZQ::common::Log::L_ERROR, MSGLOGFMT(MessageChannel, "faile to destroy connection with error:%s"), amqp_error_string(reply).c_str());

	_nConnOk = false;
	return true;
}

bool MessageChannel::connect()
{
	if(_nConnOk)
		return true;

	ServerConfig& serverConfig =  _messageTransporter.getServerConfig();

	if(NULL == _conn)
		_conn = amqp_new_connection();

	if(NULL == _conn)
	{
     _log(ZQ::common::Log::L_ERROR,  MSGLOGFMT(MessageChannel, "failed to creating connection"));		
	 return false;
	}

	if(NULL == _socket)
		_socket = amqp_tcp_socket_new(_conn);

	if (!_socket) {
		_log(ZQ::common::Log::L_ERROR,  MSGLOGFMT(MessageChannel, "failed to creating TCP socket"));
		return false;
	}

	int status = amqp_socket_open(_socket, serverConfig.ip.c_str(), serverConfig.port);
	if (status) {
		_log(ZQ::common::Log::L_ERROR,  MSGLOGFMT(MessageChannel, "failed to opening TCP socket"));
		return false;
	}

	amqp_rpc_reply_t reply = amqp_login(_conn, serverConfig.vHost.c_str(), 0, serverConfig.frame_max, 0, AMQP_SASL_METHOD_PLAIN, (char*)serverConfig.user.c_str(), (char*)serverConfig.passwd.c_str());
	if(reply.reply_type !=  AMQP_RESPONSE_NORMAL)
	{
		_log(ZQ::common::Log::L_ERROR,  MSGLOGFMT(MessageChannel, "failed to Logging in with error:%s"), amqp_error_string(reply).c_str());
		return false;
	}

	_log(ZQ::common::Log::L_INFO,  MSGLOGFMT(MessageChannel, "Logged in %s:%s@%s:%d"), serverConfig.user.c_str(), serverConfig.passwd.c_str(), serverConfig.ip.c_str(), serverConfig.port);

	//step 1. 创建Channel
	amqp_channel_open(_conn, _chId);
	reply = amqp_get_rpc_reply(_conn);
	if(reply.reply_type != AMQP_RESPONSE_NORMAL)
	{
		_log(ZQ::common::Log::L_ERROR,  MSGLOGFMT(MessageChannel, "failed to openning channel with error:%s"), amqp_error_string(reply).c_str());
		return false;
	}

	/*
	有三种类型的Exchanges：direct, fanout,topic  每个实现了不同的路由算法（routing algorithm）。
	•        Direct exchange: 如果 routing key 匹配, 那么Message就会被传递到相应的queue中。
	其实在queue创建时，它会自动的以queue的名字作为routing key来绑定那个exchange。
	•        Fanout exchange: 会向响应的queue广播。
	•        Topic exchange: 对key进行模式匹配，比如ab*可以传递到所有ab*的queue。
	*/
	//step 2. 如果是Produce，则要declare exchange
	std::string  exchangeType =  converExchangeType(_exchangeType);

	amqp_exchange_declare(_conn, _chId, amqp_cstring_bytes(_exchange.c_str()), amqp_cstring_bytes(exchangeType.c_str()),
		0, 0, amqp_empty_table);

	reply = amqp_get_rpc_reply(_conn);

	if(reply.reply_type != AMQP_RESPONSE_NORMAL)
	{
		_log(ZQ::common::Log::L_ERROR, MSGLOGFMT(MessageChannel,"faile to declaring exchange with error:%s"),  amqp_error_string(reply).c_str());
		return false;
	}

	//step3. 创建一个Queue， 将Exchange与 _routingKey绑定

	//AMQP_PUBLIC_FUNCTION amqp_queue_declare_ok_t * AMQP_CALL amqp_queue_declare(amqp_connection_state_t state, 
	//amqp_channel_t channel, amqp_bytes_t queue, amqp_boolean_t passive, amqp_boolean_t durable,
	//amqp_boolean_t exclusive, amqp_boolean_t auto_delete, amqp_table_t arguments);

	amqp_bytes_t queue = amqp_cstring_bytes(_queueName.c_str());
	amqp_table_t queueTable = { 0, NULL };
	amqp_queue_declare_ok_t *r = amqp_queue_declare(_conn, _chId, queue, 0, 0, 0, 0, queueTable);

	reply = amqp_get_rpc_reply(_conn);

	if(reply.reply_type != AMQP_RESPONSE_NORMAL)
	{
		_log(ZQ::common::Log::L_ERROR,  MSGLOGFMT(MessageChannel, "failed to Declaring queue with error:%s"),  amqp_error_string(reply).c_str());
		return false;
	}

	//  AMQP_PUBLIC_FUNCTION amqp_queue_bind_ok_t * AMQP_CALL 
	//  amqp_queue_bind(amqp_connection_state_t state, 
	//                  amqp_channel_t channel, amqp_bytes_t queue, amqp_bytes_t exchange, 
	//                  amqp_bytes_t routing_key, amqp_table_t arguments)

	amqp_queue_bind(_conn, _chId, amqp_cstring_bytes(_queueName.c_str()), amqp_cstring_bytes(_exchange.c_str()), 
		amqp_cstring_bytes(_routingKey.c_str()),amqp_empty_table);

	reply = amqp_get_rpc_reply(_conn);

	if(reply.reply_type != AMQP_RESPONSE_NORMAL)
	{
		_log(ZQ::common::Log::L_ERROR,  MSGLOGFMT(MessageChannel, "failed to binding queue with error:%s"),  amqp_error_string(reply).c_str());
		return false;
	} 

	_log(ZQ::common::Log::L_INFO,  MSGLOGFMT(MessageChannel, "init channel success.queueName[%s], exchange[%s], exchangeType[%s] routingKey[%s]"),
		_queueName.c_str(), _exchange.c_str(), converExchangeType(_exchangeType).c_str(), _routingKey.c_str());

	_nConnOk = true;
	return true;
}
/*
AMQP_PUBLIC_FUNCTION
int
AMQP_CALL amqp_basic_publish(amqp_connection_state_t state, amqp_channel_t channel,
amqp_bytes_t exchange, amqp_bytes_t routing_key,
amqp_boolean_t mandatory, amqp_boolean_t immediate,
struct amqp_basic_properties_t_ const *properties,
amqp_bytes_t body);
*/
std::string  amqpStatusErrorStr(int code)
{
	std::string error= "unknown";
	switch(code)
	{
	case AMQP_STATUS_OK:
		error = "AMQP_STATUS_OK";
		break;
	case AMQP_STATUS_NO_MEMORY:
		error = "AMQP_STATUS_NO_MEMORY";
		break;
	case AMQP_STATUS_BAD_AMQP_DATA:
		error = "AMQP_STATUS_BAD_AMQP_DATA";
		break;
	case AMQP_STATUS_UNKNOWN_CLASS:
		error = "AMQP_STATUS_UNKNOWN_CLASS";
		break;
	case AMQP_STATUS_UNKNOWN_METHOD:
		error = "AMQP_STATUS_UNKNOWN_METHOD";
		break;
	case AMQP_STATUS_HOSTNAME_RESOLUTION_FAILED:
		error = "AMQP_STATUS_HOSTNAME_RESOLUTION_FAILED";
		break;
	case AMQP_STATUS_INCOMPATIBLE_AMQP_VERSION:
		error = "AMQP_STATUS_INCOMPATIBLE_AMQP_VERSION";
		break;
	case AMQP_STATUS_CONNECTION_CLOSED:
		error = "AMQP_STATUS_CONNECTION_CLOSED";
		break;
	case AMQP_STATUS_BAD_URL:
		error = "AMQP_STATUS_BAD_URL";
		break;
	case AMQP_STATUS_SOCKET_ERROR:
		error = "AMQP_STATUS_SOCKET_ERROR";
		break;
	case AMQP_STATUS_INVALID_PARAMETER:
		error = "AMQP_STATUS_INVALID_PARAMETER";
		break;
	case AMQP_STATUS_TABLE_TOO_BIG:
		error = "AMQP_STATUS_TABLE_TOO_BIG";
		break;
	case AMQP_STATUS_WRONG_METHOD:
		error = "AMQP_STATUS_WRONG_METHOD";
		break;
	case AMQP_STATUS_TIMEOUT:
		error = "AMQP_STATUS_TIMEOUT";
		break;
	case AMQP_STATUS_TIMER_FAILURE:
		error = "AMQP_STATUS_TIMER_FAILURE";
		break;
	case AMQP_STATUS_HEARTBEAT_TIMEOUT:
		error = "AMQP_STATUS_HEARTBEAT_TIMEOUT";
		break;
	case AMQP_STATUS_UNEXPECTED_STATE:
		error = "AMQP_STATUS_UNEXPECTED_STATE";
		break;
	case AMQP_STATUS_TCP_ERROR:
		error = "AMQP_STATUS_TCP_ERROR";
		break;
	case AMQP_STATUS_TCP_SOCKETLIB_INIT_ERROR:
		error = "AMQP_STATUS_TCP_SOCKETLIB_INIT_ERROR";
		break;
	case AMQP_STATUS_SSL_ERROR:
		error = "AMQP_STATUS_SSL_ERROR";
		break;
	case AMQP_STATUS_SSL_HOSTNAME_VERIFY_FAILED:
		error = "AMQP_STATUS_SSL_HOSTNAME_VERIFY_FAILED";
		break;
	case AMQP_STATUS_SSL_PEER_VERIFY_FAILED:
		error = "AMQP_STATUS_SSL_PEER_VERIFY_FAILED";
		break;
	case AMQP_STATUS_SSL_CONNECTION_FAILED:
		error = "AMQP_STATUS_SSL_CONNECTION_FAILED";
		break;
	default:
         break;
	}
	return error;
}
bool MessageChannel::publish(const std::string& message, const amqp_basic_properties_t& props,amqp_boolean_t mandatory, amqp_boolean_t immediate)
{
	int reply = amqp_basic_publish(_conn, _chId, amqp_cstring_bytes(_exchange.c_str()),
		amqp_cstring_bytes(_routingKey.c_str()),mandatory,immediate, &props, amqp_cstring_bytes(message.c_str()));
	if(reply != AMQP_STATUS_OK)
	{
		_log(ZQ::common::Log::L_ERROR,  MSGLOGFMT(MessageChannel, "failed to publish message[%s] to rabbitmq with errorcode[%d:%s]. queueName[%s], exchange[%s], routingKey[%s]"),
			message.c_str(), reply, (amqpStatusErrorStr(reply)).c_str(), _queueName.c_str(), _exchange.c_str(), _routingKey.c_str());
		{
			std::vector<int>::iterator itor = std::find(_connectLostCode.begin(), _connectLostCode.end(), reply);
			if(itor != _connectLostCode.end())
			{
				_log(ZQ::common::Log::L_INFO,  MSGLOGFMT(MessageChannel, "ready to reconnect"));
				_nConnOk = false;
			}
		}

		return false;
	}
	_log(ZQ::common::Log::L_DEBUG,  MSGLOGFMT(MessageChannel, " publish message[%s] to rabbitmq queueName[%s], exchange[%s], routingKey[%s], message[%s] successful"), 
		message.c_str(), _queueName.c_str(), _exchange.c_str(), _routingKey.c_str(), message.c_str());
	return true;
}

void MessageChannel::buildConnectLostLists()
{
	_connectLostCode.push_back(AMQP_STATUS_CONNECTION_CLOSED); //-7
	_connectLostCode.push_back(AMQP_STATUS_SOCKET_ERROR);//-9
	_connectLostCode.push_back(AMQP_STATUS_TCP_ERROR);//0x0100
	_connectLostCode.push_back(AMQP_STATUS_TCP_SOCKETLIB_INIT_ERROR);//-9
}

void MessageChannel::checkConnection()
{
   
}

void MessageChannel::buildTestMessage()
{
/*	static int count = 0;
	for(int i = 0 ; i < 10;++i)
	{
		char message[1024];
		memset(message, 0, sizeof(message));
		sprintf(message, "[[%s:%d/%p]count:%u: test message] ", _name.c_str(), _chId, this, count);

		Message msg;
		msg[""] = message;
		push(msg);
		count++;
	}*/
}
} // namespace AMQP
} // namespace EventGateway
