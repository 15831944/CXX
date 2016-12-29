// File Name : StreamEventSinkI.cpp

#include "StreamEventSinkI.h"

#include "GBssConfig.h"

#include "Environment.h"

#include "CRGSessionManager.h"

#include "RtspRelevant.h"

#include "RtspHeaderDefines.h"

#define ANNOUNCELOG _fileLog

namespace GBss
{

class SmartServerRequest
{
public: 
	SmartServerRequest(IServerRequest*& pServerRequest);
	virtual ~SmartServerRequest();

private:
	IServerRequest*& _pServerRequest;
};

StreamEventSinkI::StreamEventSinkI(ZQ::common::Log& fileLog, Environment& env)
:_fileLog(fileLog), _env(env)
{

}

StreamEventSinkI::~StreamEventSinkI()
{
}

void StreamEventSinkI::ping(::Ice::Long lv, const ::Ice::Current& ic)
{
}

void StreamEventSinkI::onAnnounce(const ::std::string& proxy, const ::std::string& uid, 
								  GBssStreamEventType GBssEventType, 
								  TianShanIce::Properties& extendProps, const ::Ice::Current& ic) const
{
	if (0 == _GBssConfig._announce._SRMEnabled && 0 == _GBssConfig._announce._STBEnabled)
	{
		// ANNOUNCELOG(ZQ::common::Log::L_INFO, CLOGFMT(StreamEventSinkI, "disable send stream event to SRM and STB"));
		return ;
	}

	::std::vector<Ice::Identity> idents = _env.getSessionManager().findStreams(uid, 1);
	if (idents.size() == 0)
	{
		// ANNOUNCELOG(ZQ::common::Log::L_DEBUG, CLOGFMT(StreamEventSinkI, "unknown streamID[%s], ignore the event"), uid.c_str());
		return ;
	}

	// get session context
	TianShanIce::Properties sessionContext;
	SsmGBss::CRGSessionPrx sessionProxy = _env.getSessionManager().getSessionContext(idents[0].name, sessionContext);
	if (NULL == sessionProxy)
	{
		ANNOUNCELOG(ZQ::common::Log::L_ERROR, CLOGFMT(StreamEventSinkI, "failed to get session[%s] context for stream[%s]"), idents[0].name.c_str(), uid.c_str());
		return ;
	}

	// rtsp announce header
	std::string responseHead = "ANNOUNCE " + sessionContext[SESSION_META_DATA_REQUEST_URL] + " RTSP/1.0";

	// CSeq header
	std::string sequence;
	if (_GBssConfig._announce._useGlobalCSeq > 0)
	{
		sequence = _env.getAnnounceSequence();
	}
	else
	{
		try
		{
			sequence = sessionProxy->getAnnounceSeq();
		}
		catch (const Ice::Exception& ex)
		{
			ANNOUNCELOG(ZQ::common::Log::L_ERROR, CLOGFMT(StreamEventSinkI, "caught [%s] when got announce CSeq from session[%s]"), ex.ice_name().c_str(), idents[0].name.c_str());
			return ;
		}
	}

	// Data header
	std::string currentDate = _env.getUTCTime();

	std::string strEvent;
	// Notice header
	std::string strSRMNotice;
	std::string strSTBNotice;
	switch (GBssEventType)
	{
	case ON_END_OF_STREAM:
		strSTBNotice = generatorNoticeString("2101", "End-of-Stream Reached", currentDate);
		strSRMNotice = strSTBNotice;
		strEvent = "End-of-Stream";
		break;
	case ON_BEGINGNING_OF_STREAM :
		strSTBNotice = generatorNoticeString("2104", "Begin-of-Stream Reached", currentDate);
		strSRMNotice = generatorNoticeString("2104", "Begin-of-Stream Reached", currentDate);
		strEvent = "Beginning-of-Stream";
		break;
	case ON_SPEED_CHANGED:
		strSTBNotice = generatorNoticeString("8801", "Scale Changed", currentDate);
		strSRMNotice = generatorNoticeString("1300", "Scale Changed", currentDate); 
		strEvent = "On-Speed-Change";
		break;
	case ON_STATE_CHANGED:
		strSTBNotice = generatorNoticeString("8802", "State Changed", currentDate);
		strSRMNotice = generatorNoticeString("1200", "State Changed", currentDate); 
		strEvent = "On-State-Changed";
		break;
	case ON_EXIT:
		strEvent = "On-Exit";
		break;
	case ON_EXIT2:
		strEvent = "On-Exit";
		break;
	default:
		strEvent = "unknown-Event";
		break;
	}

	// Date
	if (_GBssConfig._announce._SRMEnabled > 0)
	{
		/// send SRM Announce
		std::vector<std::string> srmConnections;
		_env.getSRMConnectionIDs(srmConnections);
		std::vector<std::string>::iterator iter = srmConnections.begin();
		for (; iter != srmConnections.end(); iter++)
		{
			//std::string SRMConnId = sessionContext[SESSION_META_DATA_SRM_CONNECTION_ID];
			std::string& SRMConnId = *iter;
			IServerRequest* SRMAnnounce = _env.getStreamSmithSite().newServerRequest(idents[0].name.c_str(), SRMConnId);
			SmartServerRequest smartSRMAnnounce(SRMAnnounce);
			if (!SRMAnnounce)
			{
				ANNOUNCELOG(ZQ::common::Log::L_ERROR, CLOGFMT(StreamEventSinkI, "session[%s] failed to create SRM ANNOUNCE Request"), idents[0].name.c_str());
				continue;
			}

			SRMAnnounce->printCmdLine((char*)responseHead.c_str());
			SRMAnnounce->printHeader(HeaderSequence, (char*)sequence.c_str());
			SRMAnnounce->printHeader(HeaderSession, (char*)idents[0].name.c_str());
			SRMAnnounce->printHeader(HeaderGlobalSessId, (char*)sessionProxy->getGlobalSessId().c_str());
			SRMAnnounce->printHeader(HeaderGBNotice, (char*)strSRMNotice.c_str());
			SRMAnnounce->printHeader(HeaderServer, ZQ_COMPONENT_NAME);
			SRMAnnounce->printHeader("Date", (char*)currentDate.c_str());
			SRMAnnounce->post();
			ANNOUNCELOG(ZQ::common::Log::L_INFO, CLOGFMT(StreamEventSinkI, "session[%s] Event(%s) has been posted to SRM"), idents[0].name.c_str(), strEvent.c_str());
		}
	}

	if (_GBssConfig._announce._STBEnabled > 0)
	{
		/// send STB Annnounce
		std::string STBConnId = sessionContext[SESSION_META_DATA_STB_CONNECTION_ID];
		IServerRequest* STBAnnounce = _env.getStreamSmithSite().newServerRequest(idents[0].name.c_str(), STBConnId);
		SmartServerRequest smartSTBAnnounce(STBAnnounce);
		if (!STBAnnounce)
		{
			ANNOUNCELOG(ZQ::common::Log::L_ERROR, CLOGFMT(StreamEventSinkI, "session[%s] failed to create STB ANNOUNCE Request"), idents[0].name.c_str());
			return;
		}

		STBAnnounce->printCmdLine((char*)responseHead.c_str());
		STBAnnounce->printHeader(HeaderSequence, (char*)sequence.c_str());
		STBAnnounce->printHeader(HeaderSession, (char*)idents[0].name.c_str());
		STBAnnounce->printHeader(HeaderGlobalSessId, (char*)sessionProxy->getGlobalSessId().c_str());
		STBAnnounce->printHeader(HeaderGBNotice, (char*)strSTBNotice.c_str());
		STBAnnounce->printHeader(HeaderServer, ZQ_COMPONENT_NAME);
		STBAnnounce->printHeader("Date", (char*)currentDate.c_str());
		STBAnnounce->post();
		ANNOUNCELOG(ZQ::common::Log::L_INFO, CLOGFMT(StreamEventSinkI, "session[%s] Event(%s) has been posted to STB"), idents[0].name.c_str(), strEvent.c_str());
	}
}

std::string StreamEventSinkI::generatorNoticeString(const std::string& strNoticeCode, 
													const std::string& strNoticeString, 
													const std::string& strEventDate) const
{
	return strNoticeCode + " " + strNoticeString + " " + "Event-date=" + strEventDate;
}


//bool StreamEventSinkI::getSessionContext(const std::string& sessId, SsmGBss::CRGSessionPrx& sessionProxy, TianShanIce::Properties& sessionContext) const
//{
//	// find session proxy 
//	int statusCode;
//	std::string strLastError;
//	sessionProxy = _env.getSessionManager().findSession(sessId, strLastError, statusCode);
//	if (NULL == sessionProxy)
//	{
//		return false;
//	}
//
//	try
//	{
//		sessionContext = sessionProxy->getMetaData();
//		_fileLog(ZQ::common::Log::L_DEBUG, CLOGFMT(StreamEventSinkI, "successed to get session[%s] context"), sessId.c_str());
//	}
//	catch (const Ice::Exception& ex)
//	{
//		_fileLog(ZQ::common::Log::L_ERROR, CLOGFMT(RequestHandler, "get session[%s] context caught[%s]"), sessId.c_str(), ex.ice_name().c_str());
//		return false;
//	}
//	return true;
//}

void StreamEventSinkI::OnBeginningOfStream(const ::std::string& proxy, const ::std::string& uid, const TianShanIce::Properties& props, const ::Ice::Current& ic)const
{
	//ANNOUNCELOG(ZQ::common::Log::L_INFO, CLOGFMT(StreamEventSinkI, "Event(Beginning-of-Stream): [%s]"), proxy.c_str());
	TianShanIce::Properties extendProps;
	onAnnounce(proxy, uid, ON_BEGINGNING_OF_STREAM, extendProps, ic);
}

void StreamEventSinkI::OnSpeedChanged(const ::std::string& proxy, const ::std::string& uid, ::Ice::Float prevSpeed, ::Ice::Float currentSpeed, const TianShanIce::Properties& props, const ::Ice::Current& ic)const
{
	//ANNOUNCELOG(ZQ::common::Log::L_INFO, CLOGFMT(StreamEventSinkI, "Event(Scale Changed): [%s] from [%f] to[%f]"), proxy.c_str() , prevSpeed , currentSpeed );
//	TianShanIce::Properties extendProps;
//	onAnnounce(proxy, uid, ON_SPEED_CHANGED, extendProps, ic);
}

void StreamEventSinkI::OnStateChanged(const ::std::string& proxy, const ::std::string& uid, ::TianShanIce::Streamer::StreamState prevState, ::TianShanIce::Streamer::StreamState curState, const TianShanIce::Properties& props, const ::Ice::Current& ic/* = ::Ice::Current */)const
{
	//ANNOUNCELOG(ZQ::common::Log::L_INFO, CLOGFMT(StreamEventSinkI, "Event(State Changed): [%s]"), proxy.c_str());
//	TianShanIce::Properties extendProps;
//	onAnnounce(proxy, uid, ON_STATE_CHANGED, extendProps, ic);
}

void StreamEventSinkI::OnEndOfStream(const ::std::string& proxy, const ::std::string& uid, const TianShanIce::Properties& props, const ::Ice::Current& ic)const
{
	//ANNOUNCELOG(ZQ::common::Log::L_INFO, CLOGFMT(StreamEventSinkI, "Event(End-of-Stream): [%s]"), proxy.c_str());
	TianShanIce::Properties extendProps;
	onAnnounce(proxy, uid, ON_END_OF_STREAM, extendProps, ic);
}

void StreamEventSinkI::OnExit(const ::std::string& proxy, const ::std::string& uid, ::Ice::Int nExitCode, const ::std::string& sReason,  const ::Ice::Current& ic /*= ::Ice::Current()*/) const
{
	//ANNOUNCELOG(ZQ::common::Log::L_INFO, CLOGFMT(StreamEventSinkI, "Event(Exit-of-Stream): [%s]"), proxy.c_str());
}

void StreamEventSinkI::OnExit2(const ::std::string& proxy, const ::std::string&, ::Ice::Int nExitCode, const ::std::string& sReason, const TianShanIce::Properties&, const ::Ice::Current&) const
{
}

void StreamEventSinkI::sessionInProgressAnnounce(GBss::CRGSessionImpl &sessionContext)
{
	// only send to STB
	_fileLog(ZQ::common::Log::L_DEBUG, CLOGFMT(StreamEventSinkI, "Session[%s] preparing Session-In-Progress"), sessionContext.ident.name.c_str());
	if (0 == _GBssConfig._announce._SRMEnabled)
	{
		_fileLog(ZQ::common::Log::L_DEBUG, CLOGFMT(StreamEventSinkI, "Session[%s] Session-In-Progress is cancelled per SRMEnabled[0]"), sessionContext.ident.name.c_str());
		return;
	}

	// rtsp announce header
	std::string responseHead = "ANNOUNCE " + sessionContext.requestURL + " RTSP/1.0";

	// CSeq header
	std::string sequence;
	if (_GBssConfig._announce._useGlobalCSeq > 0)
		sequence = _env.getAnnounceSequence();
	else
		sequence = sessionContext.getAnnounceSeq();

	std::string currentDate = _env.getUTCTime();
	std::string strSTBNotice = generatorNoticeString("5700", "Session In Progress", currentDate);

	std::vector<std::string> srmConnections;
	_env.getSRMConnectionIDs(srmConnections);
	_fileLog(ZQ::common::Log::L_DEBUG, CLOGFMT(StreamEventSinkI, "Session[%s] advertizing Session-In-Progress to SRM thru %d conns"), sessionContext.ident.name.c_str(), srmConnections.size());

	for (std::vector<std::string>::iterator iter = srmConnections.begin(); iter < srmConnections.end(); iter++)
	{
		std::string& SRMConnId = *iter;
		IServerRequest* SRMAnnounce = _env.getStreamSmithSite().newServerRequest(sessionContext.ident.name.c_str(), SRMConnId);
		if (!SRMAnnounce)
		{
			_fileLog(ZQ::common::Log::L_ERROR, CLOGFMT(StreamEventSinkI, "session[%s] failed to create ANNOUNCE Request on conn[%s]"), sessionContext.ident.name.c_str(), SRMConnId.c_str());
			continue;
		}

		SRMAnnounce->printCmdLine((char*)responseHead.c_str());
		SRMAnnounce->printHeader(HeaderSequence, (char*)sequence.c_str());
		SRMAnnounce->printHeader(HeaderSession, (char*)sessionContext.ident.name.c_str());
		SRMAnnounce->printHeader(HeaderGlobalSessId, (char*)sessionContext.getGlobalSessId( Ice::Current() ).c_str());
		SRMAnnounce->printHeader(HeaderGBNotice, (char*)strSTBNotice.c_str());
		SRMAnnounce->printHeader(HeaderServer, ZQ_COMPONENT_NAME);
		SRMAnnounce->printHeader("Date", (char*)currentDate.c_str());
		SRMAnnounce->post();
		ANNOUNCELOG(ZQ::common::Log::L_INFO, CLOGFMT(StreamEventSinkI, "session[%s] Event(Session-In-Progress) has been posted"), sessionContext.ident.name.c_str());
	}
}

void StreamEventSinkI::terminatedAnnounce(GBss::CRGSessionImpl& sessionContext)
{
	_fileLog(ZQ::common::Log::L_DEBUG, CLOGFMT(StreamEventSinkI, "Session[%s] preparing Terminated Announce"), sessionContext.ident.name.c_str());

	if (0 == _GBssConfig._announce._SRMEnabled && 0 == _GBssConfig._announce._STBEnabled)
	{
		ANNOUNCELOG(ZQ::common::Log::L_DEBUG, CLOGFMT(StreamEventSinkI, "Session[%s] Session-In-Progress is cancelled per SRMEnabled[0] and STBEnabled[0]"), sessionContext.ident.name.c_str());
		return ;
	}

	// rtsp announce header
	std::string responseHead = "ANNOUNCE " + sessionContext.requestURL + " RTSP/1.0";

	// CSeq header
	std::string sequence;
	if (_GBssConfig._announce._useGlobalCSeq > 0)
		sequence = _env.getAnnounceSequence();
	else
		sequence = sessionContext.getAnnounceSeq();

	// Date 
	std::string currentDate = _env.getUTCTime();

	if (_GBssConfig._announce._SRMEnabled > 0)
	{
		// Notice header
		std::string strSRMNotice = generatorNoticeString("5402", "Client Session Terminated", currentDate);

		/// send SRM Announce
		std::vector<std::string> srmConnections;
		_env.getSRMConnectionIDs(srmConnections);
		_fileLog(ZQ::common::Log::L_DEBUG, CLOGFMT(StreamEventSinkI, "Session[%s] advertizing Session-In-Progress to SRM thru %d conns"), sessionContext.ident.name.c_str(), srmConnections.size());
		for (std::vector<std::string>::iterator iter = srmConnections.begin(); iter != srmConnections.end(); iter++)
		{
			std::string& SRMConnId = *iter;
			IServerRequest* SRMAnnounce = _env.getStreamSmithSite().newServerRequest(sessionContext.ident.name.c_str(), SRMConnId);
			SmartServerRequest smartSRMAnnounce(SRMAnnounce);
			if (!SRMAnnounce)
			{
				ANNOUNCELOG(ZQ::common::Log::L_ERROR, CLOGFMT(StreamEventSinkI, "session[%s] failed to create SRM ANNOUNCE Request on conn[%s]"), sessionContext.ident.name.c_str(), SRMConnId.c_str());
				continue;
			}

			SRMAnnounce->printCmdLine((char*)responseHead.c_str());
			SRMAnnounce->printHeader(HeaderSequence, (char*)sequence.c_str());
			SRMAnnounce->printHeader(HeaderSession, (char*)sessionContext.ident.name.c_str());
			SRMAnnounce->printHeader(HeaderGlobalSessId, (char*)sessionContext.getGlobalSessId( Ice::Current() ).c_str());
			SRMAnnounce->printHeader(HeaderGBNotice, (char*)strSRMNotice.c_str());
			SRMAnnounce->printHeader(HeaderServer, ZQ_COMPONENT_NAME);
			SRMAnnounce->printHeader("Date", (char*)currentDate.c_str());
			SRMAnnounce->post();
			ANNOUNCELOG(ZQ::common::Log::L_INFO, CLOGFMT(StreamEventSinkI, "session[%s] Event(Terminated) has been posted to SRM"), sessionContext.ident.name.c_str());
		}
	}

	if (_GBssConfig._announce._STBEnabled > 0)
	{
		/// send STB Annnounce
		std::string strSTBNotice = generatorNoticeString("5402", "Client Session Terminated", currentDate);

		std::string STBConnId = sessionContext.STBConnectionID;
		IServerRequest* STBAnnounce = _env.getStreamSmithSite().newServerRequest(sessionContext.ident.name.c_str(), STBConnId);
		SmartServerRequest smartSTBAnnounce(STBAnnounce);
		if (!STBAnnounce)
		{
			ANNOUNCELOG(ZQ::common::Log::L_ERROR, CLOGFMT(StreamEventSinkI, "session[%s] failed to create ANNOUNCE Request on ctrl-conn[%s]"), sessionContext.ident.name.c_str(), STBConnId.c_str());
			return;
		}

		STBAnnounce->printCmdLine((char*)responseHead.c_str());
		STBAnnounce->printHeader(HeaderSequence, (char*)sequence.c_str());
		STBAnnounce->printHeader(HeaderSession, (char*)sessionContext.ident.name.c_str());
		STBAnnounce->printHeader(HeaderGlobalSessId, (char*)sessionContext.getGlobalSessId().c_str());
		STBAnnounce->printHeader(HeaderGBNotice, (char*)strSTBNotice.c_str());
		STBAnnounce->printHeader(HeaderServer, ZQ_COMPONENT_NAME);
		STBAnnounce->printHeader("Date", (char*)currentDate.c_str());
		STBAnnounce->post();
		ANNOUNCELOG(ZQ::common::Log::L_INFO, CLOGFMT(StreamEventSinkI, "session[%s] Event(Terminated) has been posted to STB"), sessionContext.ident.name.c_str());
	}
}


PlayListEventSinkI::PlayListEventSinkI(ZQ::common::Log& fileLog, Environment& env):_env(env),_fileLog(fileLog)
{

}

PlayListEventSinkI::~PlayListEventSinkI()
{

}

void PlayListEventSinkI::OnItemStepped(const ::std::string& proxy, const ::std::string& playlistId, ::Ice::Int currentUserCtrlNum, ::Ice::Int prevUserCtrlNum, const ::TianShanIce::Properties& ItemProps, const ::Ice::Current& ic /* = ::Ice::Current */) const
{
	_fileLog(ZQ::common::Log::L_DEBUG, CLOGFMT(PlayListEventSinkI, "OnItemStepped(%s)"), proxy.c_str());
	if (0 == _GBssConfig._announce._SRMEnabled && 0 == _GBssConfig._announce._STBEnabled)
	{
		// ANNOUNCELOG(ZQ::common::Log::L_INFO, CLOGFMT(StreamEventSinkI, "disable send stream event to SRM and STB"));
		return ;
	}

	::std::vector<Ice::Identity> idents = _env.getSessionManager().findStreams(playlistId, 1);
	if (idents.size() == 0)
	{
		// ANNOUNCELOG(ZQ::common::Log::L_DEBUG, CLOGFMT(StreamEventSinkI, "unknown streamID[%s], ignore the event"), uid.c_str());
		return ;
	}

	// get session context
	TianShanIce::Properties sessionContext;
	SsmGBss::CRGSessionPrx sessionProxy = _env.getSessionManager().getSessionContext(idents[0].name, sessionContext);
	if (NULL == sessionProxy)
	{
		_fileLog(ZQ::common::Log::L_ERROR, CLOGFMT(StreamEventSinkI, "failed to get session[%s] context for stream[%s]"), idents[0].name.c_str(), playlistId.c_str());
		return ;
	}

	// rtsp announce header
	std::string responseHead = "ANNOUNCE " + sessionContext[SESSION_META_DATA_REQUEST_URL] + " RTSP/1.0";

	// CSeq header
	std::string sequence;
	if (_GBssConfig._announce._useGlobalCSeq > 0)
	{
		sequence = _env.getAnnounceSequence();
	}
	else
	{
		try
		{
			sequence = sessionProxy->getAnnounceSeq();
		}
		catch (const Ice::Exception& ex)
		{
			_fileLog(ZQ::common::Log::L_ERROR, CLOGFMT(StreamEventSinkI, "caught [%s] when got announce CSeq from session[%s]"), ex.ice_name().c_str(), idents[0].name.c_str());
			return ;
		}
	}

	// Data header
	std::string currentDate = _env.getUTCTime();

	//get announce error
	std::string errorCode = "";
	std::string errorDetail = "";
	std::string errorDesc = "";
	TianShanIce::Properties::const_iterator it = ItemProps.find("ItemSkipErrorCode");
	if(it == ItemProps.end())
	{
		_fileLog(ZQ::common::Log::L_ERROR, CLOGFMT(PlayListEventSinkI, "session[%s] can not find metadata[ItemSkipErrorCode]"), idents[0].name.c_str());
		return;
	}
	errorCode = it->second.c_str();

	if(!errorCode.empty())
	{
		it = ItemProps.find("errorDetail");
		if(it == ItemProps.end())
		{
			_fileLog(ZQ::common::Log::L_ERROR, CLOGFMT(PlayListEventSinkI, "session[%s] can not find metadata[errorDetail]"), idents[0].name.c_str());
			return;
		}
		errorDetail = it->second.c_str();

		it = ItemProps.find("ItemSkipErrorDescription");
		if(it == ItemProps.end())
		{
			_fileLog(ZQ::common::Log::L_ERROR, CLOGFMT(PlayListEventSinkI, "session[%s] can not find metadata[ItemSkipErrorDescription]"), idents[0].name.c_str());
			return;
		}
		errorDesc = it->second.c_str();
		//announce.postAnnounce( info , errors[errorCode].errorCodeStr , errors[errorCode].errorDescStr );
	}

	// Notice header
	std::string strSRMNotice = errorCode + " " + errorDetail + " " + "Event-date=" + currentDate;
	std::string strSTBNotice = strSRMNotice;

	// Date
	if (_GBssConfig._announce._SRMEnabled > 0)
	{
		/// send SRM Announce
		std::vector<std::string> srmConnections;
		_env.getSRMConnectionIDs(srmConnections);
		std::vector<std::string>::iterator iter = srmConnections.begin();
		for (; iter != srmConnections.end(); iter++)
		{
			//std::string SRMConnId = sessionContext[SESSION_META_DATA_SRM_CONNECTION_ID];
			std::string& SRMConnId = *iter;
			IServerRequest* SRMAnnounce = _env.getStreamSmithSite().newServerRequest(idents[0].name.c_str(), SRMConnId);
			SmartServerRequest smartSRMAnnounce(SRMAnnounce);
			if (!SRMAnnounce)
			{
				_fileLog(ZQ::common::Log::L_ERROR, CLOGFMT(StreamEventSinkI, "session[%s] failed to create SRM ANNOUNCE Request"), idents[0].name.c_str());
				continue;
			}

			SRMAnnounce->printCmdLine((char*)responseHead.c_str());
			SRMAnnounce->printHeader(HeaderSequence, (char*)sequence.c_str());
			SRMAnnounce->printHeader(HeaderSession, (char*)idents[0].name.c_str());
			SRMAnnounce->printHeader(HeaderGlobalSessId, (char*)sessionProxy->getGlobalSessId().c_str());
			SRMAnnounce->printHeader(HeaderGBNotice, (char*)strSRMNotice.c_str());
			SRMAnnounce->printHeader(HeaderServer, ZQ_COMPONENT_NAME);
			SRMAnnounce->printHeader("Date", (char*)currentDate.c_str());
			SRMAnnounce->post();
			_fileLog(ZQ::common::Log::L_INFO, CLOGFMT(StreamEventSinkI, "session[%s] Event(%s) has been posted to SRM"), idents[0].name.c_str(), errorDetail.c_str());
		}
	}

	if (_GBssConfig._announce._STBEnabled > 0)
	{
		/// send STB Annnounce
		std::string STBConnId = sessionContext[SESSION_META_DATA_STB_CONNECTION_ID];
		IServerRequest* STBAnnounce = _env.getStreamSmithSite().newServerRequest(idents[0].name.c_str(), STBConnId);
		SmartServerRequest smartSTBAnnounce(STBAnnounce);
		if (!STBAnnounce)
		{
			_fileLog(ZQ::common::Log::L_ERROR, CLOGFMT(StreamEventSinkI, "session[%s] failed to create STB ANNOUNCE Request"), idents[0].name.c_str());
			return;
		}

		STBAnnounce->printCmdLine((char*)responseHead.c_str());
		STBAnnounce->printHeader(HeaderSequence, (char*)sequence.c_str());
		STBAnnounce->printHeader(HeaderSession, (char*)idents[0].name.c_str());
		STBAnnounce->printHeader(HeaderGlobalSessId, (char*)sessionProxy->getGlobalSessId().c_str());
		STBAnnounce->printHeader(HeaderGBNotice, (char*)strSTBNotice.c_str());
		STBAnnounce->printHeader(HeaderServer, ZQ_COMPONENT_NAME);
		STBAnnounce->printHeader("Date", (char*)currentDate.c_str());
		STBAnnounce->post();
		_fileLog(ZQ::common::Log::L_INFO, CLOGFMT(StreamEventSinkI, "session[%s] Event(%s) has been posted to STB"), idents[0].name.c_str(), errorDetail.c_str());
	}

}

void PlayListEventSinkI::ping(::Ice::Long lv, const ::Ice::Current& ic /* = ::Ice::Current */)
{

}

SmartServerRequest::SmartServerRequest(IServerRequest*& pServerRequest) : _pServerRequest(pServerRequest)
{
}

SmartServerRequest::~SmartServerRequest()
{
	if (NULL != _pServerRequest)
	{
		_pServerRequest->release();
	}
	_pServerRequest = NULL;
}

} // end GBss

