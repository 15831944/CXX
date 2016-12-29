#include <syslog.h>
#include <sstream>

#include "XMLPreferenceEx.h"
#include "strHelper.h"
#include "FileLog.h"
#include "SnmpUtil.h"
#include "ZQSnmp.h"
#include "Locks.h"
#include "UDPSocket.h"
#include "SnmpInteractive.h"

#include <net-snmp/agent/net-snmp-agent-includes.h>

#define MYLOG (*logger)

using namespace ZQ::common;

namespace {
	// .iso.org.dod.internet.private.enterprises.ZQ.SE1.TianShan
	const char* OID_PREFIX = ".1.3.6.1.4.1.22839.4.1";
	// .serviceID.Service/Shell.name/value/perm.variable_number
	// .2.2.1.11

	const char* MODULE_NAME = "SnmpAgent";
	const char* CONFIG  = "/etc/TianShan.xml";

	bool loggingMask = false;
	std::string logFilename;

	FileLog nullLog;
	FileLog* logger = &nullLog;
	
	uint32        g_snmpUdpBasePort      = 10000;
	timeout_t     g_snmpAgentPendTimeOut = 5000;
	unsigned long g_agentRecvCount       = 0;

	Mutex reqlock;
}

extern XMLPreferenceEx* getPreferenceNode(const std::string&, XMLPreferenceDocumentEx&); 
extern bool loadConfig();
extern void print_requests(netsnmp_request_info*);

#ifdef __cplusplus
extern "C" {

	extern int agentHandler(
		netsnmp_mib_handler* handler,
		netsnmp_handler_registration* reginfo,
		netsnmp_agent_request_info* reqinfo,
		netsnmp_request_info* requests); 

	extern void init_SNMPAgent(); 

}
#endif

void init_SNMPAgent()
{
	MYLOG(Log::L_DEBUG, "initializing SNMP extension agent, loading SNMP extension agent configuration");
	if(!loadConfig())
	{
		MYLOG(Log::L_DEBUG, "failed to load configuration");
		return;
	}

	//prepare root oid	
	static oid myOid[MAX_OID_LEN];
	size_t len = MAX_OID_LEN;

	MYLOG(Log::L_DEBUG, "creating rootOid");
	if (!read_objid(OID_PREFIX, myOid, &len))
	{
		MYLOG(Log::L_ERROR, "failed to read root oid");
		return;
	}
	
	//register request handler	
	MYLOG(Log::L_DEBUG, "registering handler");
	netsnmp_handler_registration* myHandler = netsnmp_create_handler_registration(
		"agentHandler",
		agentHandler,
		myOid,
		len,
		HANDLER_CAN_RWRITE);

	if(!myHandler) 
	{
		MYLOG(Log::L_ERROR, "failed to create agent handler");
		return;
	}

	netsnmp_register_handler(myHandler);

    MYLOG(Log::L_INFO, "SNMPAgent initialized: oid[%s], handler[%p], snmpUdpBasePort[%d], snmpPendTimeOut[%d]", myOid, myHandler, g_snmpUdpBasePort, g_snmpAgentPendTimeOut);									 
}


int agentHandler(netsnmp_mib_handler* handler,
				 netsnmp_handler_registration* reginfo,
				 netsnmp_agent_request_info* reqinfo,
				 netsnmp_request_info* requests) 
{
	print_requests(requests);

	while(requests) 
	{
		variable_list* vars = requests->requestvb;
		MYLOG(Log::L_INFO, "processing request[%u]", requests->index);
		
		//parse the oid to get service ID		
		uint32_t svcId, procId, infoType, idx;
		if(!ZQSNMP::Util::parseOid(vars->name, vars->name_length, svcId, procId, infoType, idx)) 
		{
			MYLOG(Log::L_DEBUG, "faled to parse oid:name[%s],len[%d]", vars->name, vars->name_length);
			return SNMP_ERR_RESOURCEUNAVAILABLE;
		}

		MYLOG(Log::L_DEBUG, "request for service[%u] process[%u]", svcId, procId);

		// encode message
		size_t len = ZQSNMP_MSG_LEN_MAX;
		u_char buff[ZQSNMP_MSG_LEN_MAX] = {0};
		int32_t err = SNMP_ERR_NOERROR;
		u_char mode = ZQSNMP_PDU_UNKNOWN;

		switch(reqinfo->mode)
		{
		case MODE_GET:
			mode = ZQSNMP_PDU_GET;
			break;
		case MODE_GETNEXT:
			mode = ZQSNMP_PDU_GETNEXT;
			break;
		case MODE_SET_RESERVE1:
		case MODE_SET_RESERVE2:
		case MODE_SET_COMMIT:       
		case MODE_SET_ACTION:       
			mode = ZQSNMP_PDU_SET;
			break;
		default:
			break;
		}

		if (mode == ZQSNMP_PDU_UNKNOWN)
		{
			MYLOG(Log::L_ERROR, "unknown request PDU[%d]", reqinfo->mode);
			return SNMP_ERR_WRONGTYPE;
		}

		if(!ZQSNMP::Util::encodeMsg(buff, &len, mode, err, vars)) 
		{
			MYLOG(Log::L_ERROR, "failed to encode request");
			return SNMP_ERR_RESOURCEUNAVAILABLE;
		} 

		timeout_t        timeout        = g_snmpAgentPendTimeOut;
		size_t           reslen         = ZQSNMP_MSG_LEN_MAX; 
		int32            snmpServerPort = svcId + procId + g_snmpUdpBasePort;
		u_char           response[ZQSNMP_MSG_LEN_MAX] = {0};
		InetHostAddress  udpSvcAddress("127.0.0.1");
		UDPSocket        udpAgnet;

		udpAgnet.setCompletion(false);
		MYLOG(Log::L_DEBUG, "udpSvcAddress[%s] snmpServerPort[%d]: %d+%d+%d", udpSvcAddress.getHostAddress(), snmpServerPort, g_snmpUdpBasePort, svcId, procId);

		{
			MutexGuard guard(reqlock);
			if (!udpAgnet.isPending(Socket::pendingOutput, timeout))
			{
				MYLOG(Log::L_ERROR, "agent Output timeout[%d]", timeout);
				return SNMP_ERR_RESOURCEUNAVAILABLE;
			}

			MYLOG(Log::L_DEBUG, "sending to request to %s /%d", udpSvcAddress.getHostAddress(), snmpServerPort);
			
			InterActive      sendToSvc       = {0};
			unsigned long    requestLinePos  = (unsigned long) &((((struct InterActive*) 0)->_content).request);
			sendToSvc._head._agentRecvSeq  = g_agentRecvCount;
			memcpy((sendToSvc._content.request), buff, len);
			
			int sentState = udpAgnet.sendto(&sendToSvc, len + requestLinePos, udpSvcAddress, snmpServerPort);
			if (0 >= sentState)
			{
				MYLOG(Log::L_ERROR, "failed to send to udpSvcAddress[%s /%d] msgLen[%d], agentRecvCount[%d]", udpSvcAddress.getHostAddress(), snmpServerPort, len + requestLinePos, g_agentRecvCount);
				return SNMP_ERR_RESOURCEUNAVAILABLE;
			}

			if (!udpAgnet.isPending(Socket::pendingInput, timeout))
			{
				MYLOG(Log::L_ERROR, "timeout at waiting for response from snmpServerPort[%d] timeout[%d]", snmpServerPort, timeout);
				return SNMP_ERR_RESOURCEUNAVAILABLE;
			}

			InterActive    recvFromSvc     = {0};
			reslen = udpAgnet.receiveFrom(&recvFromSvc, sizeof(InterActive), udpSvcAddress, snmpServerPort);
			MYLOG(Log::L_DEBUG, "received %d bytes from udpSvcAddress[%s / %d]", reslen, udpSvcAddress.getHostAddress(), snmpServerPort);

			if (0 >= reslen 
				|| (recvFromSvc._head._agentRecvSeq) != g_agentRecvCount
				|| 0 >= (reslen - requestLinePos))
			{
				MYLOG(Log::L_ERROR, "agent processing snmp udp server[%s], snmpServerPort[%d], agentRecvCount[%d] recv erro", udpSvcAddress.getHostAddress(), snmpServerPort, g_agentRecvCount);
				return SNMP_ERR_RESOURCEUNAVAILABLE;
			}

			++g_agentRecvCount;
			memcpy(response, (recvFromSvc._content.request), (reslen - requestLinePos));
		}

		MYLOG(Log::L_INFO, "received %d bytes from udpSvcAddress[%s / %d] agentRecvCount[%d]", reslen, udpSvcAddress.getHostAddress(), snmpServerPort, g_agentRecvCount);
		
		//decode message
		if(!ZQSNMP::Util::decodeMsg(response, reslen, &mode, &err, vars)) 
		{
			MYLOG(Log::L_ERROR, "failed to decode response from udpSvcAddress[%s / %d]  agentRecvCount[%d]", udpSvcAddress.getHostAddress(), snmpServerPort, g_agentRecvCount);
			return SNMP_ERR_RESOURCEUNAVAILABLE;
		}

		requests = requests->next;
	}

	return SNMP_ERR_NOERROR;
}

void deinit_myAgent()
{
	unlink(AGENT_PIPE); 
	if(logger != &nullLog) 
	{
		delete logger;
		logger = 0;
	}
}


bool loadConfig() 
{
	XMLPreferenceDocumentEx doc; 
	if(!doc.open(CONFIG)) 
	{
		syslog(LOG_ERR, "failed to load configuration from (%s)", CONFIG);
		return false;
	}

	XMLPreferenceEx* node = getPreferenceNode("SNMP", doc);
	if(!node) 
	{
		syslog(LOG_ERR, "failed to get log configuration");
		return false;
	}

	char value[256];
	bool res = false;
	std::istringstream is;
	memset(value, '\0', 256);

	 //enable 
	res = node->getAttributeValue("loggingMask", value);
	if(res) 
	{
		is.str(value);
		is >> loggingMask;
	}

	memset(value, '\0', 256);
	res = node->getAttributeValue("SnmpUdpBasePort", value);
	if(res) 
	{
		std::istringstream snmpIs;
		const unsigned int portMaxLimit = 65535;
		snmpIs.str(value);
		snmpIs >> g_snmpUdpBasePort;
		g_snmpUdpBasePort = (g_snmpUdpBasePort < portMaxLimit) ? g_snmpUdpBasePort : 10000;
	}

	memset(value, '\0', 256);
	res = node->getAttributeValue("SnmpAgentPendTimeOut", value);
	if(res) 
	{
		std::istringstream snmpPendTime;
		snmpPendTime.str(value);
		snmpPendTime >> g_snmpAgentPendTimeOut;
		g_snmpAgentPendTimeOut = g_snmpAgentPendTimeOut > 0 ? g_snmpAgentPendTimeOut : 500;
	}

	if(loggingMask) 
	{
		res = node->getAttributeValue("logPath", value);//path 
		if(!res) 
		{
			syslog(LOG_ERR, "failed to get log path");
			node->free();
			return false;
		}

		logFilename = std::string(value) + "/" + MODULE_NAME;
		try 
		{
			logger = new FileLog(logFilename.c_str(), Log::L_DEBUG);
		}
		catch(const FileLogException& ex) 
		{
			syslog(LOG_ERR, "failed to initialize logger: (%s)", ex.getString());
			return false;
		}
	}

	node->free();
	return true;
}

void print_requests(netsnmp_request_info* requests) 
{
	//#ifdef _DEBUG
	std::ostringstream req;
	req << "request: [mode: (";
	switch(requests->agent_req_info->mode) 
	{
	case MODE_GET:
		req << "GET";
		break;
	case MODE_GETNEXT:
		req << "GETNEXT";
		break;
	case MODE_SET_RESERVE1:
	case MODE_SET_RESERVE2:
	case MODE_SET_COMMIT:       
	case MODE_SET_ACTION:       
		req << "SET";
		break;
	default:
		req << "UNKNOWN";
		break;
	}
	req << ") ";

	uint16_t numVariables = 0;
	while(requests) 
	{
		variable_list* vars = requests->requestvb;

		++numVariables;
		req << "var[" << numVariables << "]: (";
		for(size_t i = 0; i < vars->name_length; ++i) 
		{
			req << vars->name[i];
			if(i != vars->name_length-1)
			{
				req << '.';
			}
		}
		req << ") ";
		requests = requests->next;
	}

	MYLOG(Log::L_DEBUG, req.str().c_str());
	//#endif
}

