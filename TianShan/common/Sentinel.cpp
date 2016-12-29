#include "Sentinel.h"

namespace EventChannel{

    
/// Messenger implement
    Messenger::Messenger()
    {
        _lastStamp = 0;
    }

    Messenger::~Messenger()
    {
    }

    void Messenger::ping(::Ice::Long timestamp, const ::Ice::Current& c)
    {
        Ice::Context::const_iterator it = c.ctx.find("from");
        if(it != c.ctx.end() && it->second == c.id.name) {
            _lastStamp = timestamp;
            _hEvent.signal();
        }
    }

    bool Messenger::checkResponse(::Ice::Long stamp, Ice::Long timeout, Ice::Long *delay)
    {
        Ice::Long expiredTime = ZQTianShan::now() + timeout;
        Ice::Long waitTime = timeout;
        while(waitTime > 0) {
            SYS::SingleObject::STATE st = _hEvent.wait(waitTime);
            switch(st)
            {
            case SYS::SingleObject::SIGNALED:
                {
                    if (_lastStamp < stamp) { // discard this message
                        waitTime = expiredTime - ZQTianShan::now();
                        continue;
                    } else {
                        if(delay) {
                            *delay = ZQTianShan::now() - stamp;
                        }
                        return (_lastStamp == stamp);
                    }
                }
                
            case SYS::SingleObject::TIMEDOUT:
            default:
                return false;
            }
        }
        return false;
    }

    /// Sentinel implement
    const std::string Sentinel::TopicOfSentinelEvent = "TianShan/Event/Sentinel";

    Sentinel::Sentinel(ZQ::common::Log& log, const std::string& endpoint, ExternalControlData *extData)
        :_log(log), _extData(extData), _senThrdId(-1)
    {
        Ice::InitializationData initData;
        _communicator = Ice::initialize(initData);

        std::string proxyStr = endpoint;
        Ice::ObjectPrx prx = _communicator->stringToProxy(proxyStr);
        _topicMgr = IceStorm::TopicManagerPrx::uncheckedCast(prx);
    }

    Sentinel::~Sentinel()
    {
        if(isRunning())
        {
            _hQuit.signal();
            _log(ZQ::common::Log::L_INFO, CLOGFMT(Sentinel, "~Sentinel() the sentinel thread (%d) is quiting..."), _senThrdId);
            waitHandle(-1);
            _log(ZQ::common::Log::L_INFO, CLOGFMT(Sentinel, "~Sentinel() the sentinel thread (%d) quit"), _senThrdId);
        }
        else
        {
            _log(ZQ::common::Log::L_INFO, CLOGFMT(Sentinel, "~Sentinel() the sentinel thread (%d) is not running."), _senThrdId);
        }

        try{
            _communicator->destroy();
        }
        catch(...)
        {
        }
    }

    
    void Sentinel::stop()
    {
        _hQuit.signal();
    }

    int Sentinel::run()
    {
        bool bQuit = false;
        uint32 curThrdId = id();

        _senThrdId = curThrdId;

        _log(ZQ::common::Log::L_INFO, CLOGFMT(Sentinel, "(%d) sentinel thread enter."), curThrdId);

        Messenger::Ptr messenger;
        Ice::ObjectPrx messengerPrx;
        Ice::ObjectAdapterPtr adapter;
        // setup
        try{
            adapter = _communicator->createObjectAdapterWithEndpoints("Sentinel", "tcp");
            messenger = new Messenger();
            messengerPrx = adapter->addWithUUID(messenger);
            adapter->activate();
        }catch(const Ice::Exception &e)
        {
            _log(ZQ::common::Log::L_ERROR, CLOGFMT(Sentinel, "(%d) Caught [%s] during the setup of working thread. Quit."), curThrdId, e.ice_name().c_str());
            return -1;
        }
        catch(...)
        {
            _log(ZQ::common::Log::L_ERROR, CLOGFMT(Sentinel, "(%d) Caught known exception during the setup of working thread. Quit."), curThrdId);
            return -1;
        }

        if(_extData->checkTimeout < 500)
            _extData->checkTimeout = 500; // 500 msec
        if(_extData->checkTimeout > 30000)
            _extData->checkTimeout = 30000; // 30 sec

        int retryCount = 0;
        // wait time: 1,1,1,2,2,2,4,4,4,8,8,8,16,16,16,32,32,32,32....
#define RetryWaitTime ((1 << (retryCount < 15 ? retryCount / 3 : 5)) * 1000)
        // generate a topic for the sentinel
        std::string messagerId = messengerPrx->ice_getIdentity().name;
        while(!bQuit)
        {
            // connect
            IceStorm::TopicPrx  topic;
            TianShanIce::Events::BaseEventSinkPrx publisher;
            try
            {
	            try
	            {
		            topic = _topicMgr->retrieve(TopicOfSentinelEvent);
	            }
	            catch(const IceStorm::NoSuchTopic&)
	            {
		            topic = _topicMgr->create(TopicOfSentinelEvent);
	            }

                Ice::ObjectPrx obj = topic->subscribeAndGetPublisher(IceStorm::QoS(), messengerPrx);
                publisher = TianShanIce::Events::BaseEventSinkPrx::uncheckedCast(obj);
                _log(ZQ::common::Log::L_INFO, CLOGFMT(Sentinel, "(%d) Connection established. Start monitoring the EventChannel."), curThrdId);
            }
            catch(const IceStorm::AlreadySubscribed&)
            {
                // rare case, but actually may occur when the unsubscribe failed
                _log(ZQ::common::Log::L_WARNING, CLOGFMT(Sentinel, "(%d) AreadySubscribed caught. unsubscribe and retry."), curThrdId);
                try{
                    publisher = NULL;
                    topic->unsubscribe(messengerPrx);
                    topic = NULL;
                }catch(...){} // not care the error here
                // report the bad connection
                try { _extData->reportBadConnection(); }catch(...){}
                // check the quiting status, and retry immediately
                bQuit = (SYS::SingleObject::SIGNALED == _hQuit.wait(1));
                continue;
            }
            catch(const Ice::Exception &e)
            {
                _log(ZQ::common::Log::L_WARNING, CLOGFMT(Sentinel, "(%d) Cought [%s] during connect EventChannel. Retry after %d msec"), curThrdId, e.ice_name().c_str(), RetryWaitTime);
                // report the bad connection
                try { _extData->reportBadConnection(); }catch(...){}
                bQuit = (SYS::SingleObject::SIGNALED == _hQuit.wait(RetryWaitTime));
                ++retryCount;
                continue;
            }
            catch(...)
            {
                _log(ZQ::common::Log::L_WARNING, CLOGFMT(Sentinel, "(%d) Cought known exception during connect EventChannel. Retry after %d msec"), curThrdId, RetryWaitTime);
                // report the bad connection
                try { _extData->reportBadConnection(); }catch(...){}
                bQuit = (SYS::SingleObject::SIGNALED == _hQuit.wait(RetryWaitTime));
                ++retryCount;
                continue;
            }
            retryCount = 0;
            try { _extData->onConnectionEstablished(); }catch(...){}
             // work
            try
            {
                unsigned long lastOKPrintingTime = 0;
                while(true)
                {
                    if(_extData->checkInterval < 500)
                        _extData->checkInterval = 500; // 500 msec
                    if(_extData->checkInterval > 300000)
                        _extData->checkInterval = 300000; // 5 min

                    SYS::SingleObject::STATE st = _hQuit.wait(_extData->checkInterval);
                    if(st == SYS::SingleObject::TIMEDOUT)
                    {
                        Ice::Long stamp = ZQTianShan::now(); // generate the stamp
                        Ice::Context ctx;
                        ctx["from"] = messagerId;
                        publisher->ping(stamp, ctx);

                        Ice::Long delay = -1;
                        if(messenger->checkResponse(stamp, _extData->checkTimeout, &delay))
                        {
                            _extData->lastCheckDelay = delay;
                            unsigned long nowTime = SYS::getTickCount();
                            if(nowTime - lastOKPrintingTime > 300000) // 5 min
                            {
                                _log(ZQ::common::Log::L_DEBUG, CLOGFMT(Sentinel, "(%d) EventChannel response with %d msec delay."), curThrdId, delay);
                                lastOKPrintingTime = nowTime;
                            }
                        }
                        else
                        { // we believe the connection is broken
                            _extData->lastCheckDelay = -1;
                            _log(ZQ::common::Log::L_WARNING, CLOGFMT(Sentinel, "(%d) Message lost or EventChannel not response in %d msec!"), curThrdId, _extData->checkTimeout);
                            break;
                        }
                    }
                    else if(st == SYS::SingleObject::SIGNALED)
                    { // normal quit
                        bQuit = true;
                        _log(ZQ::common::Log::L_DEBUG, CLOGFMT(Sentinel, "(%d) Sentinel working thread normal quit."), curThrdId);
                        break;
                    }
                    else
                    { // what happened?
                    }
                }// end while(true)
            }
            catch(const Ice::Exception &e)
            {
                _log(ZQ::common::Log::L_WARNING, CLOGFMT(Sentinel, "(%d) Caught [%s] during the working. The connection with EventChannel is broken."), curThrdId, e.ice_name().c_str());
            }
            catch(...)
            {
                _log(ZQ::common::Log::L_WARNING, CLOGFMT(Sentinel, "(%d) Caught unknown exception during the working."), curThrdId);
            }

            // report the bad connection
            try { _extData->reportBadConnection(); }catch(...){}
            // disconnect
            try
            {
                publisher = NULL;
                topic->unsubscribe(messengerPrx);
                topic = NULL;
            }catch(const Ice::Exception &e)
            {
                _log(ZQ::common::Log::L_WARNING, CLOGFMT(Sentinel, "(%d) Caught [%s] during disconnect EventChannel."), curThrdId, e.ice_name().c_str());
            }
            catch(...)
            {
                _log(ZQ::common::Log::L_WARNING, CLOGFMT(Sentinel, "(%d) Caught unknown exception during disconnect EventChannel."), curThrdId);
            }
        }
        //  cleanup
        try{
            adapter->remove(messengerPrx->ice_getIdentity());
            adapter->deactivate();
            adapter = NULL;
            messengerPrx = NULL;
            messenger = NULL;
        }catch(const Ice::Exception &e)
        {
            _log(ZQ::common::Log::L_ERROR, CLOGFMT(Sentinel, "(%d) Caught [%s] during the cleanup."), curThrdId, e.ice_name().c_str());
        }
        catch(...)
        {
            _log(ZQ::common::Log::L_ERROR, CLOGFMT(Sentinel, "(%d) Caught unknown exception during the cleanup."), curThrdId);
        }

        _log(ZQ::common::Log::L_INFO, CLOGFMT(Sentinel, "(%d) sentinel thread leave."), curThrdId);

        return 0;
    }

}
