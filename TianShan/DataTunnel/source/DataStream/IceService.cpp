#include "stdafx.h"
#include "DSServantLocatorImpl.h"
#include "IceService.h"
#include "svclog.h"
#include <assert.h>
#include "datastreamcfg.h"
#include "DataDef.h"
#include "Datastreammain.h"

#define Servant_DataStream "DataStreamServantLocator"

extern ZQ::common::Config::Loader<DataStreamCfg> gDataStreamConfig;
extern DataStreamShell dataStreamShell;
class DODLogger: public Ice::Logger {
public:

	virtual void print(const ::std::string& text)
	{
		glog(ZQLIB::Log::L_INFO, text.c_str());
	}

	virtual void trace(const ::std::string& category, const ::std::string& text)
	{
		glog(ZQLIB::Log::L_DEBUG, "%s : %s", category.c_str(), text.c_str());
	}

	virtual void warning(const ::std::string& text)
	{
		glog(ZQLIB::Log::L_WARNING, text.c_str());
	}

	virtual void error(const ::std::string& text)
	{
		glog(ZQLIB::Log::L_ERROR, text.c_str());
	}
};
//////////////////////////////////////////////////////////////////////////

class DataStreamServer : public Ice::Application
{
public:

	DataStreamServer()
	{
		_chkTimeoutStopped = true;
		_stopEvent = NULL;
	}

	virtual int run(int argc, char* argv[]);

	bool stop();

protected:
	bool startCheckTimeout();
	virtual DWORD checkTimeoutRun();
	void stopCheckTimeout();
    static DWORD __stdcall __checkTimeoutThreadProc(void* param);

protected:
	Ice::CommunicatorPtr	_ic;
	HANDLE					_stopEvent;
	HANDLE					_chkTimeoutThread;
	bool					_chkTimeoutStopped;
	ZQADAPTER_DECLTYPE  _adapter;
	::Freeze::DSServantLocatorPtr _dsServantLocator;
	TianShanIce::Streamer::DataOnDemand::DataStreamServiceImpl*	_service;
};

int DataStreamServer::run(int argc, char* argv[])
{
	glog(ZQLIB::Log::L_INFO, "DataStream Ice server is running..." LOG_FMT, 
		LOG_ARG);

	try {
		_ic = communicator();

		Ice::PropertiesPtr _properties = communicator()->getProperties();

		const std::map<std::string, std::string> iceConfig = 
			gDataStreamConfig.icePropMap;

		std::map<std::string, std::string>::const_iterator iter = iceConfig.begin();
		for (int i = 0; iter != iceConfig.end(); ++iter) 
		{
			_properties->setProperty(iter->first, iter->second);
			i++;
		}
//		_adapter = _ic->createObjectAdapter(ICE_ADAPTER_NAME);
		_adapter = ZQADAPTER_CREATE(_ic, ICE_ADAPTER_NAME, gDataStreamConfig.endpoint.c_str(), glog);

		if (_adapter == NULL) {
			
			glog(ZQLIB::Log::L_CRIT, 
				"Communicator::createObjectAdapter() failed");
			return -1;
		}

		try
		{
			_dsServantLocator = new ::Freeze::DSServantLocatorImpl(_adapter,_ic);
			//................................
            // add clear all object in evictor
			//................................
/*			Ice::ObjectFactoryPtr factory = new TianShanIce::Streamer::DataOnDemand::DataStreamFactory(_adapter, _evictor);

			_ic->addObjectFactory(factory, "TianShanIce::Streamer::DataOnDemand::DataStream");
			_ic->addObjectFactory(factory, "TianShanIce::Streamer::DataOnDemand::MuxItem");*/
			_adapter->addServantLocator(_dsServantLocator, "");

		}
		catch (Ice::Exception& ex)
		{
			glog(ZQ::common::Log::L_ERROR,
				"run()fail to create evictor,caught ice exception(%s)",
				ex.ice_name().c_str());
			dataStreamShell.OnStop();
			return -1;
		}
		catch (...)
		{
			glog(ZQ::common::Log::L_ERROR,
				"run()fail to create evictor, caught unknown exception (%d)", GetLastError());
			dataStreamShell.OnStop();
			return -1;
		}

		_service = new TianShanIce::Streamer::DataOnDemand::DataStreamServiceImpl(_adapter, _dsServantLocator);

		if (!_service->init()) {
			glog(ZQLIB::Log::L_CRIT, 
				"DataStreamService initilization failed.\n");
			dataStreamShell.OnStop();
			return -1;
		}

		/*		if (_adapter->add(_service, 
		_ic->stringToIdentity(ICE_SERVICE_NAME)) == NULL)*/

		// add datastream servant
		try
		{
			_adapter->ZQADAPTER_ADD(_ic, _service, ICE_SERVICE_NAME);
		}
		catch (const Ice::Exception& ex)
		{
			glog(ZQ::common::Log::L_ERROR,
				"run() add DataStreamService servant caught ice exception '%s'", 
				ex.ice_name().c_str());
			dataStreamShell.OnStop();
			return -1;
		}
		catch (...)
		{
			glog(ZQ::common::Log::L_ERROR,
				"run() add DataStreamService servant caught unknown exception(%d)",
				GetLastError());
			dataStreamShell.OnStop();
			return -1;
		}
         ignoreInterrupt();
		_adapter->activate();
		startCheckTimeout();

		glog(ZQLIB::Log::L_DEBUG, "wait for shutdown...");
		
		_stopEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
		WaitForSingleObject(_stopEvent, INFINITE);
		CloseHandle(_stopEvent);
		_stopEvent = NULL;
		// Ice::Application::shutdownOnInterrupt();
		// _ic->waitForShutdown();

	} catch (Ice::Exception& e) {
		glog(ZQLIB::Log::L_CRIT, "%s:\t%s:%d (occurred a Ice exception)", 
			__FUNCTION__, e.ice_file(), e.ice_line());
		return -1;
	}

	return 0;
}

bool DataStreamServer::stop()
{
	glog(ZQLIB::Log::L_INFO, "DataStream Ice server is stopping..." LOG_FMT, 
		LOG_ARG);

	stopCheckTimeout();	

	if (_service)
		_service->destroy();

	try {
		if (_adapter != NULL)
			_adapter->deactivate();
		_ic->destroy();

	} catch (::Ice::Exception& e) {

		glog(ZQLIB::Log::L_WARNING, "DataStreamServer::stop():\t"
			"occurred exception: %s", e.ice_name().c_str());

	} catch (...) {

		glog(ZQLIB::Log::L_WARNING, "DataStreamServer::stop():\t"
			"occurred a unknown exception");
	}

	SetEvent(_stopEvent);
	return true;
}

bool DataStreamServer::startCheckTimeout()
{
	DWORD threadId;
	_chkTimeoutThread = CreateThread(NULL, 0, __checkTimeoutThreadProc, 
		this, 0, &threadId);

	return _chkTimeoutThread != NULL;
}

DWORD DataStreamServer::checkTimeoutRun()
{
	_chkTimeoutStopped = false;
	assert(_service);

	while (!_chkTimeoutStopped) {
		try {

			// service->checkTimeout(120 * 60 * 1000); // 2 hour
			_service->checkTimeout(gDataStreamConfig.checkStreamTimeout* 1000);

		} catch(Ice::Exception& e) {
			glog(ZQLIB::Log::L_ERROR, 
				"%s:\tcheckTimeout() occurred a exception(%s).", 
				__FUNCTION__, e.ice_name().c_str());
		}

		// check it after 10 minute
		for (int i = 0; i < 10; i ++) {
			if (_chkTimeoutStopped)
				break;

			Sleep(1000);
		}		
	}

	return 0;
}

void DataStreamServer::stopCheckTimeout()
{
	_chkTimeoutStopped = true;
	WaitForSingleObject(_chkTimeoutThread, INFINITE);
}

DWORD __stdcall DataStreamServer::__checkTimeoutThreadProc(void* param)
{
	DataStreamServer* thisPtr = (DataStreamServer* )param;
	return thisPtr->checkTimeoutRun();
}

//////////////////////////////////////////////////////////////////////////

IceService::IceService()
{
	_stopped = true;
	_exitEvent = ::CreateEvent(NULL,TRUE, FALSE, NULL);
}

IceService::~IceService()
{
	CloseHandle(_exitEvent);
}

bool IceService::start()
{
	_threadHandle = ::CreateThread(NULL, 0, win32ThreadProc, this, 0, 
		&_threadId );

	if (_threadHandle == NULL)
		return false;

	return true;
}

bool IceService::stop()
{
	if (_stopped)
		return true;

	bool r = _server->stop();
	WaitForSingleObject(_exitEvent, INFINITE);
	return r;
}

DWORD __stdcall IceService::win32ThreadProc(void* param)
{
	IceService* me = (IceService* )param;
	me->_stopped = false;
	assert(me);
	if (!me->init()) {
		glog(ZQLIB::Log::L_DEBUG, "IceService::init() result is false.");
		return -1;
	}

	DWORD r;
	__try {
		r = me->run();
	} __finally {
		me->final();
		me->_stopped = true;
	}

	return r;
}

bool IceService::init()
{
	return true;
}

unsigned long  IceService::run()
{
	::Ice::InitializationData initData;

	_server = new DataStreamServer();
	::Ice::LoggerPtr logger = new DODLogger();
	
	::Ice::PropertiesPtr props = Ice::createProperties();

	std::map<std::string, std::string>::iterator porpitor;
	for (porpitor = gDataStreamConfig.icePropMap.begin(); porpitor != gDataStreamConfig.icePropMap.end(); porpitor ++) {
		props->setProperty(porpitor->first, porpitor->second);
	}

	initData.logger = logger;
	initData.properties = props;
	return _server->main(__argc, __argv, initData);
}

void IceService::final()
{
	delete _server;
	SetEvent(_exitEvent);
}
