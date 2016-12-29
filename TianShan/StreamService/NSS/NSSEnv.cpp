#ifndef    LOGFMTWITHTID
#  define  LOGFMTWITHTID
#endif 

#include "NSSEnv.h"
#include "NGODSession.h"
#include "NSSUtil.h"
#include "NSSCfgLoader.h"

#include "SsServiceImpl.h"
#include "IPathHelperObj.h"
#include "TsStreamer.h"
#include "SystemUtils.h"
#include "Guid.h"
#include "ZQResource.h"

#include <TianShanIceHelper.h>

bool bDecimalNpt=true; // TODO: to be a configuration

extern ZQTianShan::NSS::NSSBaseConfig::NSSHolder	*pNSSBaseConfig;

namespace ZQTianShan {
namespace NGODSS {

using namespace ZQ::common;
using namespace ZQ::StreamService;

NSSEnv::NSSEnv(ZQ::common::Log& mainLog, ZQ::common::Log& sessLog, ZQ::common::NativeThreadPool& rtspThpool, ZQ::common::NativeThreadPool& ssThpool)
: _bRun(false), _rtspTraceLevel(Log::L_INFO), _sessTimeout(MAX_IDLE), _rtspThpool(rtspThpool),
  SsEnvironment(mainLog,sessLog,ssThpool)
{
}

NSSEnv::~NSSEnv()
{
	_bRun = false;
}

void NSSEnv::init()
{
	streamsmithConfig.iEnableSGScaleChangeEvent = pNSSBaseConfig->_postEvent.enableScaleChangeEvent;
	streamsmithConfig.iEnableSGStateChangeEvent = pNSSBaseConfig->_postEvent.enableStateChangeEvent;
	streamsmithConfig.iPassSGScaleChangeEvent	= pNSSBaseConfig->_postEvent.passScaleChangeEvent;
	streamsmithConfig.iPassSGStateChangeEvent	= pNSSBaseConfig->_postEvent.passStateChangeEvent;
	streamsmithConfig.iMaxPendingRequestSize	= pNSSBaseConfig->_bind.pendingMax;
	
	try
	{
		_watchDog = new WatchDog(*this);
	}
	catch (...)
	{
	}

	try
	{
		_logger.open(pNSSBaseConfig->_sessionHistory.path.c_str(),
			pNSSBaseConfig->_sessionHistory.level,
			ZQLOG_DEFAULT_FILENUM,
			pNSSBaseConfig->_sessionHistory.size,
			pNSSBaseConfig->_sessionHistory.bufferSize,
			pNSSBaseConfig->_sessionHistory.flushTimeout);
	}
	catch( const ZQ::common::FileLogException& ex)
	{
		glog(ZQ::common::Log::L_ERROR, CLOGFMT(NSSEnv,"failed to open session history log file[%s] because [%s]"),
			pNSSBaseConfig->_sessionHistory.path.c_str(), ex.what() );
	}

	_userAgent =  std::string("NSS/") + __STR1__(ZQ_PRODUCT_VER_MAJOR) "." __STR1__(ZQ_PRODUCT_VER_MINOR);

	if (_rtspTraceLevel < _logger.getVerbosity())
		_rtspTraceLevel = (ZQ::common::Log::loglevel_t)_logger.getVerbosity();
		
	// initialize sessiongroup
	int32& maxSessionGroups = pNSSBaseConfig->_videoServer.SessionInterfaceMaxSessionGroup;
	int32& maxSessionsPerGroup = pNSSBaseConfig->_videoServer.SessionInterfaceMaxSessionsPerGroup;

	// step 1. adjust the configuration
	if (maxSessionGroups < 1)
	{
		maxSessionGroups = 2;
		glog(::ZQ::common::Log::L_WARNING, CLOGFMT(NSSEnv, "invalid max SessionGroups(%d), reset to 2"), maxSessionGroups);	
	}
	else if (maxSessionGroups > 99)
	{
		maxSessionGroups = 99;
		glog(::ZQ::common::Log::L_WARNING, CLOGFMT(NSSEnv, "invalid max SessionGroups(%d), reset to 99"), maxSessionGroups);	
	}

	if (maxSessionsPerGroup > 800)
	{
		glog(::ZQ::common::Log::L_WARNING, CLOGFMT(NSSEnv, "invalid MasSessionsPerGroup number(%d) exceed maximum, reset to 800"), maxSessionsPerGroup);	
		maxSessionsPerGroup = 800;
	}
	else if (maxSessionsPerGroup < 10)
	{
		glog(::ZQ::common::Log::L_WARNING, CLOGFMT(NSSEnv,"invalid MasSessionsPerGroup number(%d) less than minimum, reset to 20"), maxSessionsPerGroup);	
		maxSessionsPerGroup = 10;
	}

	// step 2. generate baseURL
	std::string baseURL = std::string("rtsp://") + pNSSBaseConfig->_videoServer.SessionInterfaceIp;

	if (554 != pNSSBaseConfig->_videoServer.SessionInterfacePort)
	{
		char buf[32];
		snprintf(buf, sizeof(buf)-2, ":%d", pNSSBaseConfig->_videoServer.SessionInterfacePort);
		baseURL += buf;
	}

	if (pNSSBaseConfig->_videoServer.SessionInterfaceBind.empty())
	{
		_bindAddr = InetHostAddress(pNSSBaseConfig->_videoServer.SessionInterfaceBind.c_str());
		glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(NSSEnv, "taking localAddr[%s, %s] to bind"), pNSSBaseConfig->_videoServer.SessionInterfaceBind.c_str(), _bindAddr.getHostAddress());	
	}

	if (pNSSBaseConfig->_videoServer.sessionRenewInterval > 10)
		_sessTimeout = pNSSBaseConfig->_videoServer.sessionRenewInterval *1000;
	
	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(NSSEnv, "taking session timeout[%d]msec"), _sessTimeout);	

	NGODClient::_bTryDecimalNpt = (pNSSBaseConfig->_videoServer.SessionInterfaceTryDecimalNpt !=0);
	if (NGODClient::_bTryDecimalNpt)
		glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(NSSEnv, "decimalNPT proto versioning enabled"));	
	
	// step 3. create the session groups
	{
		MutexGuard g(NGODSessionGroup::_lockGroups);
		for (int i = 0; i < maxSessionGroups; i++)
		{

			//		NGODClient* client = new NGODClient(*mainLogger, *mainThreadPool, bindAddress, std::string("rtsp://") + ss.str(), NULL, Log::L_DEBUG);
			//		NGODSessionGroup::addNGODClient(std::string("rtsp://") + ss.str(), client);

			char groupName[100];
			snprintf(groupName, sizeof(groupName)-2, "%s.%02d", _netId.c_str(), (i+1));
			NGODSessionGroup::Ptr group = new NGODSessionGroup(*this, groupName, baseURL, maxSessionsPerGroup, pNSSBaseConfig->_videoServer.streamSyncInterval*1000);
			NGODSessionGroup::_groupMap.insert(NGODSessionGroup::SessionGroupMap::value_type(groupName, group));

			if (_watchDog)
				_watchDog->watch(group, pNSSBaseConfig->_videoServer.streamSyncInterval*1000);

			glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(NSSEnv, "SessionGroup[%s] created to SS[%s]"), groupName, baseURL.c_str());	
		}
	}

	streamsmithConfig.iSupportPlaylist = LIB_SUPPORT_NORMAL_STREAM;
}

void NSSEnv::start()
{
	_bRun = true;
	if (_watchDog)
		_watchDog->start();
}

void NSSEnv::uninit()
{
	_bRun = false;
	try
	{
		if (_watchDog)
			delete _watchDog;
		_watchDog = NULL;

		NGODSessionGroup::clearSessionGroup();
	}
	catch (...)
	{
	}
}

// -----------------------------
// class WatchDog
// -----------------------------
WatchDog::WatchDog(NSSEnv& env)
: _env(env)
{
}

WatchDog::~WatchDog()
{	
	//exit thread
	terminate(0);

	{
		ZQ::common::MutexGuard gd(_lockGroups);
		_groupsToSync.clear();
	}	
}

int WatchDog::terminate(int code)
{
	_event.signal();
	//wait until the run function exit
	waitHandle(100000);
	return 1;
}

int WatchDog::run()
{
	while (_env.isRunning())
	{
		ZQ::common::MutexGuard gd(_lockGroups);
//		Ice::Long stampNow = now();
		Ice::Long _nextWakeup = 0;

		if (!_env.isRunning())
			break;

		for (SyncMap::iterator iter = _groupsToSync.begin(); _env.isRunning() && iter != _groupsToSync.end(); iter++)
		{
			NGODSessionGroup::Ptr group = iter->first;
			if (group)
			{
				group->OnTimer();
				if (0 == _nextWakeup )
					_nextWakeup = group->getLastSync() + group->getSyncInterval();
				else
					_nextWakeup = (_nextWakeup > (group->getLastSync() + group->getSyncInterval())) ? (group->getLastSync() + group->getSyncInterval()) : _nextWakeup;
			}
		}

		long sleepTime = (long) (_nextWakeup - now());

		if (sleepTime < 100)
			sleepTime = 100;

		if (!_env.isRunning())
			continue;

		_event.wait(sleepTime);
	}

	return 1;
}

void WatchDog::watch(NGODSessionGroup::Ptr group, ::Ice::Long syncInterval)
{
	{
		ZQ::common::MutexGuard gd(_lockGroups);

		if (syncInterval < 0)
			syncInterval = 0;
		::Ice::Long newSync = now() + syncInterval;

		_groupsToSync.insert(std::make_pair(group, newSync));
	}

	_event.signal();
}

}}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//	SsServiceImpl interface
namespace ZQ {
namespace StreamService {

using namespace ZQ::common;
using namespace ZQTianShan::NGODSS;

TianShanIce::Variant GetResourceMapData(const TianShanIce::SRM::ResourceMap& rcMap,
										const TianShanIce::SRM::ResourceType& type,
										const std::string& strkey)
{
	TianShanIce::SRM::ResourceMap::const_iterator itResMap=rcMap.find(type);
	if (itResMap==rcMap.end())
	{
		char szBuf[1024];
		snprintf(szBuf, sizeof(szBuf), "GetResourceMapData() type %d not found", type);

		ZQTianShan::_IceThrow<TianShanIce::InvalidParameter>("NSS",1001,szBuf );
	}

	TianShanIce::ValueMap::const_iterator it=itResMap->second.resourceData.find(strkey);
	if (it==itResMap->second.resourceData.end())
	{
		char szBuf[1024];
		snprintf(szBuf, sizeof(szBuf), "GetResourceMapData() value with key=%s not found", strkey.c_str());
		ZQTianShan::_IceThrow<TianShanIce::InvalidParameter>("NSS",1002,szBuf);
	}

	return it->second;
}

//add for CCUR
void calcScale(float& fScale, SsContext& ctx )
{
	if( pNSSBaseConfig->_videoServer.FixedSpeedSetEnable <= 0 )
		return; // keep current scale

	//detect request scale attribute
	int requestDirection = 0 ;
	if ((fScale - 1.0f) > 0.0001f )
		requestDirection = 1; //fast forward
	else if( fScale < 0.0f )
	 	requestDirection = -1; //fast rewind
	else
	{
		//reset last scale status
		ctx.updateContextProperty(SPEED_LASTIDX, -1);
		ctx.updateContextProperty(SPEED_LASTDIR, 1);
		return ;
	}

	int iLastIndex = atoi(ctx.getContextProperty(SPEED_LASTIDX).c_str());

	int lastDirection = atoi(ctx.getContextProperty(SPEED_LASTDIR).c_str());

	bool bUseForwardSet = requestDirection > 0;

	std::vector<float> scaleSet;
	if( bUseForwardSet )
		scaleSet = pNSSBaseConfig->_videoServer.FixedSpeedSetForwardSet;
	else
		scaleSet = pNSSBaseConfig->_videoServer.FixedSpeedSetBackwardSet;

	if (scaleSet.size() <= 0 )
	{
		ctx.updateContextProperty(SPEED_LASTIDX, -1);
		ctx.updateContextProperty(SPEED_LASTDIR, requestDirection);
		return ;
	}

	if (pNSSBaseConfig->_videoServer.EnableFixedSpeedLoop >= 1 )//EnableFixedSpeedLoop
	{
		iLastIndex = ( lastDirection * requestDirection ) < 0 ? 0 : ( (++iLastIndex) % (int) scaleSet.size() );
	}
	else
	{
		iLastIndex = ( lastDirection * requestDirection ) < 0 ? 0 : (++iLastIndex);
		if( iLastIndex >= (int) scaleSet.size() ) 
		{
			//reach the end of the fix speed set
			ZQTianShan::_IceThrow<TianShanIce::InvalidStateOfArt>(glog, "NSS", 0, "session[%s] can't loop the speed, we already reach the end of speed set", ctx.id().c_str()  );
		}
	}

	float fOldScale = fScale;

	fScale = scaleSet[iLastIndex];

	//reset last scale status
	ctx.updateContextProperty(SPEED_LASTIDX, iLastIndex);
	ctx.updateContextProperty(SPEED_LASTDIR, requestDirection);

	glog(ZQ::common::Log::L_DEBUG, CLOGFMT(NSS, "calcScale() session[%s] convert speed from [%f] to [%f] according to fix speed set"), ctx.id().c_str(), fOldScale, fScale);

	return;
}

int32	HandleRtspCode(NGODSession::Ptr sess, std::string cmd)
{
	if (sess->_resultCode >= RTSPSink::rcOK && sess->_resultCode < 300)
		return ERR_RETURN_SUCCESS;

	switch (sess->_resultCode)
	{
	//withdrew case 400: // 400 was due to some ease-made NGOD pumper error, and assume our TEARDOWN request were always good 
	case RTSPSink::rcObjectNotFound:
	case RTSPSink::rcSessNotFound:
		if ("TEARDOWN" == cmd)
			return ERR_RETURN_SUCCESS;
		else 
			return ERR_RETURN_OBJECT_NOT_FOUND; // ticket#14624

		// NOTE: no "break;" here

	case RTSPSink::rcInternalError:
		if ("PLAY" == cmd || "PAUSE" == cmd)
		{
			std::string tempNotice = sess->_tianShanNotice;
			std::transform(tempNotice.begin(), tempNotice.end(), tempNotice.begin(), (int(*)(int)) toupper);

			// transfer VSTRM_GEN_CONTROL_PORT_SPEED to 503 Service Unavailable
			if (std::string::npos != tempNotice.find("VSTRM_GEN_CONTROL_PORT_SPEED"))
				sess->_resultCode = RTSPSink::rcServiceUnavail;
		}
		// be sure no 'break' here

	default:
		ZQTianShan::_IceThrow<TianShanIce::ServerError> (glog, "RtspProxying", sess->_resultCode, "doAction(%s) failed; error[%d %s]", cmd.c_str(), sess->_resultCode, sess->_tianShanNotice.c_str());
	}

	return ERR_RETURN_SERVER_ERROR;
}

bool	SsServiceImpl::listAllReplicas( SsServiceImpl& ss, OUT SsReplicaInfoS& infos )
{
	SsReplicaInfo replica;
	replica.bHasPorts = false;
	replica.streamerType = "NSS";
	replica.bStreamReplica = true;
	replica.replicaState = TianShanIce::stInService;
	replica.replicaId = "VSOP";
	infos.insert(std::make_pair("NSS", replica));

	return  true;
}

bool SsServiceImpl::allocateStreamResource(	SsServiceImpl& ss, 
										   IN const std::string& streamerId,
										   IN const std::string& portId,
										   IN const TianShanIce::SRM::ResourceMap&	resource )
{
	return  true;
}


bool SsServiceImpl::releaseStreamResource(SsServiceImpl& ss, SsContext& sessCtx, 
											IN const std::string& streamerReplicaId,
											OUT TianShanIce::Properties& feedback  )
{
	std::string ODSessId  = sessCtx.getContextProperty(ONDEMANDNAME_NAME);
	std::string groupName = sessCtx.getContextProperty(SESSION_GROUP);
	std::string reason = sessCtx.getContextProperty(DESTROY_REASON);

	if (ODSessId.empty())
		ODSessId = sessCtx.id();

	if (ODSessId.empty() || groupName.empty())
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl, "releaseStreamResource() invalid OnDemandSessId[%s] or SessGroup[%s]"), ODSessId.c_str(), groupName.c_str());
		return false;
	}

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl, "releaseStreamResource() session[%s]"), ODSessId.c_str());

	NGODSession::Ptr clientSession = NGODSessionGroup::openSession(ODSessId, groupName);
	if (!clientSession)
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl, "releaseStreamResource() session[%s] of sessGroup[%s] not found"), ODSessId.c_str(), groupName.c_str());
		return false;
	}

	bool bSucc = false;
	do {
		NGODClient* client = clientSession->getR2Client(); 
		if (!client)
		{
			glog(::ZQ::common::Log::L_WARNING, CLOGFMT(SsServiceImpl, "releaseStreamResource() session[%s:%s] failed to access R2 connection"), ODSessId.c_str(), groupName.c_str());
			break;
		}

		glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl, "releaseStreamResource() sess[%s:%s] messaging thru client[%p]"), ODSessId.c_str(), groupName.c_str(), client);

		RTSPMessage::AttrMap     headers;
		std::string rtspSessId = clientSession->getSessionId();
		if (rtspSessId.empty() || 0 == ODSessId.compare(rtspSessId)) // no RTSPSessionId has ever successfully been setup, skip TEARDOWN
			break;

		MAPSET(RTSPMessage::AttrMap, headers, "Session",		   rtspSessId);
		MAPSET(RTSPMessage::AttrMap, headers, "OnDemandSessionId", ODSessId);
		MAPSET(RTSPMessage::AttrMap, headers, "Reason", reason.empty() ? "200 \"user pressed stop\"" : reason);

		//	MAPSET(RTSPMessage::AttrMap, headers, "Require",           R2Require);

		int currentCSeq = client->sendTEARDOWN(*clientSession, NULL, headers);
		if (currentCSeq <= 0 || !client->waitForResponse(currentCSeq))
		{
			glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl, "releaseStreamResource() session[%s]cseq(%d) request failed/timeout"), ODSessId.c_str(), currentCSeq);
			break;
		}

		if (pNSSBaseConfig->_sessionHistory.enable)
		{
			ZQ::StreamService::NSSEnv* pEnv = dynamic_cast<ZQ::StreamService::NSSEnv*>(ss.env);
			if (pEnv)
			{
				std::replace(clientSession->_sessionHistory.begin(), clientSession->_sessionHistory.end(), '\r', '.');
				std::replace(clientSession->_sessionHistory.begin(), clientSession->_sessionHistory.end(), '\n', '.');
				pEnv->_logger(Log::L_INFO, CLOGFMT(NGODSession, "releaseStreamResource() session[%s:%s] hist: %s"), ODSessId.c_str(), groupName.c_str(), clientSession->_sessionHistory.c_str());
			}
		}

		TianShanIce::Properties feedbacks;

		switch(clientSession->_resultCode)
		{
		case RTSPSink::rcOK:
			//TODO read the header playlist-wide FinalNPT
			if (clientSession->_props.end() != clientSession->_props.find(SYS_PROP(FinalNPT)))
				MAPSET(TianShanIce::Properties, feedback, SYS_PROP(FinalNPT), clientSession->_props[SYS_PROP(FinalNPT)]);

		case RTSPSink::rcObjectNotFound:
		case RTSPSink::rcSessNotFound:
		case RTSPSink::rcBadRequest:
			// consider as teardown successfully
			bSucc =true;
			break;
		}

	} while (0);

	clientSession->destroy();
	HandleRtspCode(clientSession, "TEARDOWN");

	return bSucc;
}

int32	SsServiceImpl::doValidateItem(  SsServiceImpl& ss, 
									  IN SsContext& ctx,
									  INOUT TianShanIce::Streamer::PlaylistItemSetupInfo& info )
{
	//set content as InService, so that no more GET_PARAMETER will be used to get the content play duration
	Ice::Int state = 1;
	ZQTianShan::Util::updateValueMapData( info.privateData , "StreamService.ContentInService" , state );
	return ERR_RETURN_SUCCESS;
}


int32 SsServiceImpl::doCommit(SsServiceImpl& ss, 
							  IN SsContext& ctx,								
							  IN PlaylistItemSetupInfos& items,
							  IN TianShanIce::SRM::ResourceMap& requestResources )
{
	std::string volumeName, dest, type; //MP2T/DVBC/UDP as default
	std::string strClient, bandwidth, sop_name, sop_group;

	::Ice::Identity ident;
	ident.name = ctx.id();

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(NSS, "doCommit() stream[%s]"), ident.name.c_str());

	::TianShanIce::Transport::PathTicketPrx _pathTicket = ss.getPathTicket(ident.name);
	if (!_pathTicket)
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(NSS, "stream[%s] null PathTicket bound"), ident.name.c_str());
		return ERR_RETURN_SERVER_ERROR;
	}

	// read the PathTicket
	::std::string strTicket = ss.env->getCommunicator()->proxyToString(_pathTicket);
	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(NSS, "doCommit() stream[%s] reading PathTicket[%s]"), ident.name.c_str(), strTicket.c_str());

	::TianShanIce::ValueMap pMap = _pathTicket->getPrivateData();
	::TianShanIce::SRM::ResourceMap resMap = _pathTicket->getResources();
	::TianShanIce::Transport::StorageLinkPrx storageLink = _pathTicket->getStorageLink();
	std::string	storageLinkType = storageLink->getType();
	std::string	streamLinkType = _pathTicket->getStreamLink()->getType();
	dest = "dvbc://@";
	if (pNSSBaseConfig->_videoServer.bSeperateIPStreaming && std::string::npos == streamLinkType.find("DVBC")) // ip streaming
		dest = "udp://@";

	TianShanIce::Variant	valBandwidth;
	TianShanIce::Variant	valDestAddr;
	TianShanIce::Variant	valDestPort;
	TianShanIce::Variant	valDestMac;

	// read the resource of ticket
	// 1. client mac(client_id), and mac may not available
	try
	{
		valDestMac = GetResourceMapData(requestResources, TianShanIce::SRM::rtEthernetInterface, "destMac");
		if (valDestMac.type != TianShanIce::vtStrings || valDestMac.strs.size () == 0 )
		{
			glog(::ZQ::common::Log::L_WARNING, CLOGFMT(NSS, "doCommit() stream[%s]ticket[%s] invalid dest mac type or no data"), ident.name.c_str(), strTicket.c_str());
			return ERR_RETURN_INVALID_PARAMATER;
		}

		strClient = valDestMac.strs[0];
	}
	catch (TianShanIce::InvalidParameter&)
	{
		glog(::ZQ::common::Log::L_WARNING, CLOGFMT(NSS, "doCommit() stream[%s]ticket[%s] no dest mac information"), ident.name.c_str(), strTicket.c_str());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	// 2. destination IP
	try
	{
		valDestAddr = GetResourceMapData (requestResources,TianShanIce::SRM::rtEthernetInterface, "destIP");
		if (valDestAddr.type != TianShanIce::vtStrings || valDestAddr.strs.size () == 0)
		{
			glog(::ZQ::common::Log::L_WARNING, CLOGFMT(NSS, "doCommit() stream[%s]ticket[%s] invalid destAddress type or no data"), ident.name.c_str(), strTicket.c_str());
			return ERR_RETURN_INVALID_PARAMATER;
		}

		dest += valDestAddr.strs[0];
	}
	catch (TianShanIce::InvalidParameter&)
	{
		glog(::ZQ::common::Log::L_WARNING, CLOGFMT(NSS, "doCommit() stream[%s]ticket[%s] invalid destAddress type or no data"), ident.name.c_str(), strTicket.c_str());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	//get destination port
	try
	{
		valDestPort = GetResourceMapData(requestResources,TianShanIce::SRM::rtEthernetInterface,"destPort");
		if ( valDestPort.type != TianShanIce::vtInts || valDestPort.ints.size() == 0 )
		{
			glog(::ZQ::common::Log::L_WARNING, CLOGFMT(NSS, "doCommit() stream[%s]ticket[%s] invalid destPort type or no data"), ident.name.c_str(), strTicket.c_str());
			return ERR_RETURN_INVALID_PARAMATER;
		}

		::std::stringstream ss;
		ss << valDestPort.ints[0];
		dest = dest + ":" + ss.str();
	}
	catch (TianShanIce::InvalidParameter&)
	{
		glog(::ZQ::common::Log::L_WARNING, CLOGFMT(NSS, "doCommit() stream[%s]ticket[%s] invalid destPort type or no data"), ident.name.c_str(), strTicket.c_str());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	//get bandwidth
	try
	{
		valBandwidth = GetResourceMapData(requestResources, TianShanIce::SRM::rtTsDownstreamBandwidth, "bandwidth");
		if (valBandwidth.type != TianShanIce::vtLongs || valBandwidth.lints.size () == 0 )
		{
			glog(::ZQ::common::Log::L_WARNING, CLOGFMT(NSS, "doCommit() stream[%s]ticket[%s] invalid bandwidth type or no data"), ident.name.c_str(), strTicket.c_str());
			return ERR_RETURN_INVALID_PARAMATER;
		}

		long lBandwidth =0;
		if (::TianShanIce::vtLongs == valBandwidth.type)
			lBandwidth = (long) valBandwidth.lints[0];
		else if (::TianShanIce::vtInts == valBandwidth.type)
			lBandwidth = valBandwidth.ints[0];

		::std::stringstream ss;
		ss << lBandwidth;
		bandwidth = ss.str();
	}
	catch (TianShanIce::InvalidParameter&)
	{
		glog(::ZQ::common::Log::L_WARNING, CLOGFMT(NSS, "doCommit() stream[%s]ticket[%s] invalid bandwidth type or no data"), ident.name.c_str(), strTicket.c_str());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	try
	{
		::TianShanIce::ValueMap::iterator itPV = pMap.find(PathTicketPD_Field(sop_name));
		if (pMap.end() != itPV && itPV->second.strs.size() >0)
			sop_name = itPV->second.strs[0];

		itPV = pMap.find(PathTicketPD_Field(sop_group));
		if (pMap.end() != itPV && itPV->second.strs.size() >0)
			sop_group = itPV->second.strs[0];
	}
	catch (...)
	{
		glog(::ZQ::common::Log::L_WARNING, CLOGFMT(NSS, "doCommit() stream[%s]ticket[%s] invalid SOP"), ident.name.c_str(), strTicket.c_str());
		return ERR_RETURN_SERVER_ERROR;
	}

	std::string storageNetId;
	//resMap
	TianShanIce::SRM::ResourceMap::const_iterator itStorageNetId = resMap.find( TianShanIce::SRM::rtStorage );
	if( itStorageNetId != resMap.end() )
	{
		const TianShanIce::SRM::Resource& resStorageNetId = itStorageNetId->second;
		const TianShanIce::ValueMap::const_iterator itNetId = resStorageNetId.resourceData.find("NetworkId");
		if (itNetId != resStorageNetId.resourceData.end() && itNetId->second.type == TianShanIce::vtStrings && itNetId->second.strs.size() > 0 )
			storageNetId = itNetId->second.strs[0];
	}

	if (storageLinkType == "SeaChange.NSS.C2Transfer")
	{
		if (!pNSSBaseConfig->_videoServer.libraryVolume.empty())
			volumeName = pNSSBaseConfig->_videoServer.libraryVolume;
		else
			volumeName = "library";
	}
	else
	{
		if( storageNetId.empty() )
			volumeName = pNSSBaseConfig->_videoServer.vols[0].targetName;
		else
			volumeName = storageNetId;
	}

	glog(::ZQ::common::Log::L_INFO, CLOGFMT(NSS, "Stream[%s] read ticket[%s]: dest[%s], destMAC[%s], bandwidth[%s], SOP[%s], volume[%s]"), 
		ident.name.c_str(), strTicket.c_str(), dest.c_str(), strClient.c_str(), bandwidth.c_str(), sop_name.c_str(), volumeName.c_str());

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl,"doCommit() creating NGODSession[%s]"), ident.name.c_str());

//	NGODSession::Ptr clientSession = new NGODSession(*(ss.env->getMainLogger()), ss.env->getMainThreadPool(), dest.c_str(), NULL, Log::L_DEBUG, pNSSBaseConfig->_videoServer.sessionRenewInterval*1000, ident.name.c_str());

	 NGODSession::Ptr clientSession = NGODSessionGroup::createSession(ident.name, dest);

	if (!clientSession || clientSession->getBaseURL().empty())
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl, "doCommit() create NGODSession[%s] failed with no valid session group"), ident.name.c_str());
		return ERR_RETURN_SERVER_ERROR;
	}

	clientSession->_volumeName = volumeName;
	std::string groupName = clientSession->getSessionGroupName();
	ctx.updateContextProperty(SESSION_GROUP,     groupName);
	ctx.updateContextProperty(VOLUME_NAME,       volumeName);
	ctx.updateContextProperty(ONDEMANDNAME_NAME, ident.name);
	///register session id to stream service library if commit succeed
	ctx.updateContextProperty(STREAMING_ATTRIBUTE_STREAM_SESSION_ID, ident.name);
	ctx.updateContextProperty(DESTINATION_NAME,  dest);
	ctx.updateContextProperty(CONTROL_URI,       clientSession->getBaseURL());

	std::string varname;  // for Linux compatiblity, TODO: the prototype of RTSPSession::addTransportEx() should be connected
	varname = "client";	    clientSession->addTransportEx(varname,    strClient);
	varname = "bandwidth";	clientSession->addTransportEx(varname,    bandwidth);
	varname = "sop_name";	clientSession->addTransportEx(varname,    sop_name);
	varname = "sop_group";
	if (!sop_group.empty())
		clientSession->addTransportEx(varname,  sop_group); 
	else if (0 ==pNSSBaseConfig->_videoServer.vendor.compare("SeaChange"))
		clientSession->addTransportEx(varname,  sop_name); 

	MAPSET(TianShanIce::Properties, clientSession->_props, "Content-Type",      "application/sdp");
//	MAPSET(TianShanIce::Properties, clientSession->_props, "Require",           R2Require);
	MAPSET(TianShanIce::Properties, clientSession->_props, "SessionGroup",      groupName);
	MAPSET(TianShanIce::Properties, clientSession->_props, "OnDemandSessionId", ident.name);
	MAPSET(TianShanIce::Properties, clientSession->_props, "Volume",            volumeName);
	MAPSET(TianShanIce::Properties, clientSession->_props, "StreamControlProto", "rtsp");

	std::string zero("0");
	clientSession->setSDPValue_v(zero);
	
	//line: o=- 814bd88e-bcab-4383-9c83-30198c70ade7 250531234 IN IP4 :25635
	//setSDPValue_o(std::string& userName, std::string& sessionId, std::string& sessVersion, 
	//				std::string& sessNetType, std::string& sessAddrType, std::string& sessAddr)
	std::string userName("-"), sessVersion(""), sessNetType("IN"), sessAddrType("IP4"), sessAddr("0.0.0.0");
	clientSession->setSDPValue_o(userName, ident.name, sessVersion, sessNetType, sessAddrType, sessAddr);

	clientSession->setSDPValue_t(zero, zero);

	NGODClient* client = clientSession->getR2Client(); 
	if (!client)
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl, "doCommit() sess[%s:%s] failed to retrive R2 connection"), ident.name.c_str(), groupName.c_str());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	std::string strStartPoint = "1 0.0";

	for (PlaylistItemSetupInfos::const_iterator iter = items.begin(); iter != items.end(); iter++)
	{
		// read the PID/PAID from different formats
		::TianShanIce::ValueMap pMap = iter->privateData;
		::TianShanIce::ValueMap::iterator mapIter;
		std::string pid, paid;
		size_t index = iter->contentName.find("_");
		if (index != std::string::npos)
		{
			paid	= iter->contentName.substr(0,index);
			pid	= iter->contentName.substr(index+1);
		}

		if ((mapIter = pMap.find("PAID")) != pMap.end())
		{
			//get client_id
			if ((*mapIter).second.type == ::TianShanIce::vtStrings)	
				paid = (*mapIter).second.strs[0];
		}

		if ((mapIter = pMap.find("PID")) != pMap.end())
		{
			//get client_id
			if ((*mapIter).second.type == ::TianShanIce::vtStrings)
				pid = (*mapIter).second.strs[0];
		}

		glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl, "doCommit() session[%s] adding playlist-item PAID[%s]/PID[%s]"), ident.name.c_str(), paid.c_str(), pid.c_str());

		// CR#034, Cisco server stupidlly only takes decimal_npts in SDP X-playlist-item regardless the Require header
		const char* tmpRequire = NULL;
		if (std::string::npos != pNSSBaseConfig->_videoServer.vendor.find("Cisco"))
			tmpRequire = "com.comcast.ngod.r2.decimal_npts";

		std::stringstream ss;
		ss << "X-playlist-item: " << pid << " " << paid << " " << client->formatNptValue((long) iter->inTimeOffset, tmpRequire) << "-";
		if (iter->outTimeOffset > 0)
			ss << client->formatNptValue((long)iter->outTimeOffset, tmpRequire);

		if (iter->inTimeOffset >0 && items.begin() == iter)
			strStartPoint = std::string("1 ") + client->formatNptValue((long) iter->inTimeOffset, "com.comcast.ngod.r2.decimal_npts");

		// compose a X-playlist-item line
		std::string restriction = "tricks/";
		if(iter->flags & TianShanIce::Streamer::PLISFlagNoFF)
			restriction += "F";
		if(iter->flags & TianShanIce::Streamer::PLISFlagNoRew)
			restriction += "R";
		if(iter->flags & TianShanIce::Streamer::PLISFlagNoPause)
			restriction += "P";

		if(restriction.size() > sizeof("tricks/")-1)
			ss << " " << restriction;
			
		std::string tmp = ss.str();
		clientSession->addSDPValue_a(tmp);
	}

	clientSession->setSDPValue_c(sessNetType, sessAddrType,  sessAddr, sessVersion);

	// line: m=video 0 udp MP2T
	ZQ::common::RTSPSession::MediaPropertyData mpd;
	mpd.mediaType = "video";
	mpd.mediaPort = 0;
	mpd.mediaTransport = "udp";
	mpd.mediaFmt = "MP2T";
	clientSession->addSDPValue_m(mpd);

	// I03 NGOD-GEN 8.28 StartPoint
	// Note that the NPT value is absolute. That is, the NPT is not relative to the NPT start time 
	// specified for that segment of the asset list (SDP payload data). 
	MAPSET(TianShanIce::Properties, clientSession->_props, "StartPoint", strStartPoint); // per ticket#14876, I03-Gen-RTSP: Index (1 based) of asset list element

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(NSS, "doCommit() sess[%s:%s] messaging thru client[%p]"), ident.name.c_str(), groupName.c_str(), client);
	int64 stampNow = ZQ::common::now();
	int currentCSeq = client->sendSETUP(*clientSession, NULL, NULL, clientSession->_props);
	if (currentCSeq <= 0 || !client->waitForResponse(currentCSeq))
	{
		glog(ZQ::common::Log::L_ERROR, CLOGFMT(NSS,"doCommit() RTSP request failed/timeout [%lld]msec"), ZQ::common::now() -stampNow);
		ZQTianShan::_IceThrow<TianShanIce::ServerError> (glog, "RtspProxying", RTSPSink::rcServiceUnavail, "doCommit() RTSP request failed/timeout ");
	}

	ctx.updateContextProperty(SESSION_ID, clientSession->getSessionId());	// update session id from server
	ctx.updateContextProperty(CONTROL_URI, clientSession->controlUri());
	if (!clientSession->_primartItemNPT.empty())
		ctx.updateContextProperty("sys.primaryItemNPT", clientSession->_primartItemNPT);

	if (RTSPSink::rcOK == clientSession->_resultCode)
	{
		ctx.updateContextProperty(SETUP_TIMESTAMP, clientSession->getStampSetup());		
	}


	return HandleRtspCode(clientSession, "SETUP");
}


int32 SsServiceImpl::doDestroy(SsServiceImpl& ss, SsContext&  contextKey,IN const std::string& streamId )
{
	return ERR_RETURN_SUCCESS;

/*
	NGODSessionGroup* group = 0;
	NGODSession::Ptr clientSession = 0;
	NGODClient* client = 0;
	std::string ODSessId = contextKey.getContextProperty(ONDEMANDNAME_NAME);
	if(ODSessId.empty())
		return ERR_RETURN_INVALID_PARAMATER;

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl,"doDestroy session(%s) stream(%s)"), ODSessId.c_str(), streamId.c_str());
	group = NGODSessionGroup::findSessionGroup(contextKey.getContextProperty(SESSION_GROUP));
	if (!group)
		return ERR_RETURN_INVALID_PARAMATER;

	clientSession = group->lookupByOnDemandSessionId(ODSessId.c_str());

	if (!clientSession)
	{
		std::string sessionId = contextKey.getContextProperty(SESSION_ID);
		if(sessionId.empty())
			return	ERR_RETURN_INVALID_PARAMATER;

		std::string controlUri = contextKey.getContextProperty(CONTROL_URI);
		if(controlUri.empty())
			controlUri = clientSession->getBaseURL();

		glog(::ZQ::common::Log::L_DEBUG, "fail to find session [%s, %s], need new one", ODSessId.c_str(), sessionId.c_str());
		std::string dest = contextKey.getContextProperty(DESTINATION_NAME);
		clientSession = new NGODSession(*(ss.env->getMainLogger()), ss.env->getMainThreadPool(), dest.c_str(), NULL, ss.env->getIceVerboseLevel(), pNSSBaseConfig->_videoServer.sessionRenewInterval*1000, ODSessId.c_str());
		clientSession->setSessionId(sessionId);
		clientSession->setControlUri(controlUri);
		group->add(*clientSession);
	}
	*/

}

int32 SsServiceImpl::doLoad(	SsServiceImpl& ss,
							IN SsContext& contextKey,								
							IN const TianShanIce::Streamer::PlaylistItemSetupInfo& itemInfo, 
							IN int64 timeoffset,
							IN float scale,								
							INOUT StreamParams& ctrlParams,
							OUT std::string&	streamId )
{
	streamId = contextKey.getContextProperty(ONDEMANDNAME_NAME);
	if(streamId.empty())
		return ERR_RETURN_INVALID_PARAMATER;
	else
		return ERR_RETURN_SUCCESS;
}

static void adjustPerResponseCode(NGODSession::Ptr& pClientSession)
{
	static char* To503Tbl[] = { "VSTRM_GEN_CONTROL_PORT_SPEED", "VSTRM_GEN_CONTROL_PAUSE", "VSTRM_API_DISABLED",
				NULL };
	
	if (NULL == pClientSession)
		return;
		
	std::string tsNoticeStr = pClientSession->_tianShanNotice;
	std::transform(tsNoticeStr.begin(), tsNoticeStr.end(), tsNoticeStr.begin(), (int(*)(int)) toupper);
		
	switch(pClientSession->_resultCode)
	{
	case RTSPSink::rcInternalError:
		for (int i =0; To503Tbl[i]; i++)
		{
			if (std::string::npos == tsNoticeStr.find(To503Tbl[i]))
				continue;

			pClientSession->_resultCode = RTSPSink::rcServiceUnavail;
			break;
		}

		break;
		
	default:
		break;
	}
}

int32 SsServiceImpl::doPlay(SsServiceImpl& ss,
							SsContext& contextKey,							   
							IN const std::string& streamId,
							IN int64 timeOffset,
							IN float scale,							   
							INOUT StreamParams& ctrlParams )
{	
	
	std::string ODSessId = contextKey.getContextProperty(ONDEMANDNAME_NAME);
	std::string groupName = contextKey.getContextProperty(SESSION_GROUP);
	if (ODSessId.empty() || groupName.empty())
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl,"stream[%s] doPlay() invalid OnDemandSessId[%s] or SessGroup[%s]"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl,"stream[%s] doPlay() sess[%s:%s]: range[%lld] speed[%f]"), streamId.c_str(), ODSessId.c_str(), groupName.c_str(), timeOffset, scale);

	NGODSession::Ptr clientSession = NGODSessionGroup::openSession(ODSessId, groupName);
	if (!clientSession)
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl,"stream[%s] doPlay() session[%s] of sessGroup[%s] not found"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_OBJECT_NOT_FOUND;
	}

	NGODClient* client = clientSession->getC1Client(); 
	if (!client)
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl, "stream[%s] doPlay() session[%s:%s] failed to access C1 connection"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl, "stream[%s] doPlay() session[%s:%s] messaging thru client[%p]"), streamId.c_str(), ODSessId.c_str(), groupName.c_str(), client);
	
	RTSPMessage::AttrMap headers;
	MAPSET(RTSPMessage::AttrMap, headers, "OnDemandSessionId", ODSessId);
//	MAPSET(RTSPMessage::AttrMap, headers, "Require",           C1Require);

	calcScale(scale, contextKey);
	double start = (ctrlParams.mask & MASK_TIMEOFFSET) ? static_cast<double>(timeOffset) / 1000.0f : -1.0f; // if the mask of timeoffset is not set, play from now(-1.0)

	if (timeOffset <1 && abs(scale) >1 && 0 != pNSSBaseConfig->_videoServer.vendor.compare("SeaChange"))
		start =-1.0f;

	int64 stampNow = ZQ::common::now();
	int currentCSeq = client->sendPLAY(*clientSession, start, -1.0f, scale, NULL, headers);
	if (currentCSeq <= 0 || !client->waitForResponse(currentCSeq))
	{
		glog(ZQ::common::Log::L_ERROR,CLOGFMT(NSS,"doPlay() session[%s]cseq(%d) RTSP request failed/timeout [%lld]msec"), ODSessId.c_str(), currentCSeq, ZQ::common::now() - stampNow);
		ZQTianShan::_IceThrow<TianShanIce::ServerError> (glog, "RtspProxying", RTSPSink::rcServiceUnavail, "doPlay() RTSP request failed/timeout ");
	}
	
	adjustPerResponseCode(clientSession);

	if (clientSession->_resultCode == RTSPSink::rcOK) // RTSPOK
	{
		NGODSession::StreamInfos info = clientSession->getInfos();
		ctrlParams.timeoffset = info.timeoffset;
		ctrlParams.duration = info.duration;
		ctrlParams.scale = info.scale;
		ctrlParams.streamState = TianShanIce::Streamer::stsStreaming;

		ctrlParams.mask |= MASK_TIMEOFFSET | MASK_SCALE | MASK_STATE | MASK_CONTENT_DURATION;
	}

	return HandleRtspCode(clientSession, "PLAY");
}


int32 SsServiceImpl::doPause(	SsServiceImpl& ss, SsContext& contextKey, IN const std::string& streamId, INOUT StreamParams& ctrlParams )
{
	std::string ODSessId = contextKey.getContextProperty(ONDEMANDNAME_NAME);
	std::string groupName = contextKey.getContextProperty(SESSION_GROUP);
	if (ODSessId.empty() || groupName.empty())
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl,"stream[%s] doPause() invalid OnDemandSessId[%s] or SessGroup[%s]"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl,"doPause() stream[%s] session[%s]"), streamId.c_str(), ODSessId.c_str());

	NGODSession::Ptr clientSession = NGODSessionGroup::openSession(ODSessId, groupName);
	if (!clientSession)
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl, "stream[%s] doPause() session[%s] of sessGroup[%s] not found"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_OBJECT_NOT_FOUND;
	}

	NGODClient* client = clientSession->getC1Client(); 
	if (!client)
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl,"stream[%s] doPause() session[%s:%s] failed to access C1 connection"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl, "stream[%s] doPause() session[%s:%s] messaging thru client[%p]"), streamId.c_str(), ODSessId.c_str(), groupName.c_str(), client);
	RTSPMessage::AttrMap headers;
	MAPSET(RTSPMessage::AttrMap, headers, "OnDemandSessionId", ODSessId);
	MAPSET(RTSPMessage::AttrMap, headers, "Range",             "npt=now-");
//	MAPSET(RTSPMessage::AttrMap, headers, "Require",           C1Require);

	int64 stampNow = ZQ::common::now();
	int currentCSeq = client->sendPAUSE(*clientSession, NULL, headers);
	if (currentCSeq <= 0 || !client->waitForResponse(currentCSeq))
	{
		glog(ZQ::common::Log::L_ERROR,CLOGFMT(NSS,"doPause() session[%s]cseq(%d) RTSP request failed/timeout [%lld]msec"), ODSessId.c_str(), currentCSeq, ZQ::common::now() -stampNow);
		ZQTianShan::_IceThrow<TianShanIce::ServerError> (glog, "RtspProxying", RTSPSink::rcServiceUnavail, "doPause() RTSP request failed/timeout ");
	}

	adjustPerResponseCode(clientSession);

	if(clientSession->_resultCode == RTSPSink::rcOK) // RTSPOK
	{
		NGODSession::StreamInfos info = clientSession->getInfos();
		ctrlParams.timeoffset = info.timeoffset;
		ctrlParams.duration = info.duration;
		ctrlParams.scale = info.scale;
		ctrlParams.streamState = TianShanIce::Streamer::stsPause;
	}

	return HandleRtspCode(clientSession, "PAUSE");
}


int32 SsServiceImpl::doResume(  SsServiceImpl& ss, SsContext& contextKey, IN const std::string& streamId,INOUT StreamParams& ctrlParams )
{
	std::string ODSessId = contextKey.getContextProperty(ONDEMANDNAME_NAME);
	std::string groupName = contextKey.getContextProperty(SESSION_GROUP);
	if (ODSessId.empty() || groupName.empty())
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl, "stream[%s] doResume() invalid OnDemandSessId[%s] or SessGroup[%s]"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl, "stream[%s] doResume() session[%s]"), streamId.c_str(), ODSessId.c_str());

	NGODSession::Ptr clientSession = NGODSessionGroup::openSession(ODSessId, groupName);
	if (!clientSession)
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl, "stream[%s] doResume() session[%s] of sessGroup[%s] not found"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_OBJECT_NOT_FOUND;
	}

	NGODClient* client = clientSession->getC1Client(); 
	if (!client)
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl,"stream[%s] doResume() session[%s:%s] failed to access C1 connection"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl, "stream[%s] doResume() session[%s:%s] messaging thru client[%p]"), streamId.c_str(), ODSessId.c_str(), groupName.c_str(), client);
	RTSPMessage::AttrMap headers;
	MAPSET(RTSPMessage::AttrMap, headers, "OnDemandSessionId", ODSessId);
//	MAPSET(RTSPMessage::AttrMap, headers, "Require",           C1Require);

	int64 stampNow = ZQ::common::now();
	int currentCSeq = client->sendPLAY(*clientSession, -1.0f, -1.0f, 1.0f, NULL, headers);
	if (currentCSeq <= 0 || !client->waitForResponse(currentCSeq))
	{
		glog(ZQ::common::Log::L_ERROR,CLOGFMT(NSS,"doResume() session[%s]cseq(%d) RTSP request failed/timeout [%lld]msec"), ODSessId.c_str(), currentCSeq, ZQ::common::now() - stampNow);
		ZQTianShan::_IceThrow<TianShanIce::ServerError> (glog, "RtspProxying", RTSPSink::rcServiceUnavail, "doResume() RTSP request failed/timeout ");
	}

	adjustPerResponseCode(clientSession);

	if(clientSession->_resultCode == RTSPSink::rcOK) // RTSPOK
	{
		NGODSession::StreamInfos info = clientSession->getInfos();
		ctrlParams.timeoffset = info.timeoffset;
		ctrlParams.duration = info.duration;
		ctrlParams.scale = info.scale;
		ctrlParams.streamState = TianShanIce::Streamer::stsStreaming;
	}

	return HandleRtspCode(clientSession, "PLAY");
}

int32 SsServiceImpl::doReposition( SsServiceImpl& ss, SsContext& contextKey,IN const std::string& streamId,
								  IN int64 timeOffset, IN const float& scale, INOUT StreamParams& ctrlParams )
{
	std::string ODSessId = contextKey.getContextProperty(ONDEMANDNAME_NAME);
	std::string groupName = contextKey.getContextProperty(SESSION_GROUP);
	if (ODSessId.empty() || groupName.empty())
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl, "stream[%s] doReposition() invalid OnDemandSessId[%s] or SessGroup[%s]"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl, "stream[%s] doReposition() session[%s]: range[%lld] speed[%f]"), streamId.c_str(), ODSessId.c_str(), timeOffset, scale);

	NGODSession::Ptr clientSession = NGODSessionGroup::openSession(ODSessId, groupName);
	if (!clientSession)
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl,"stream[%s] doReposition() session[%s] of sessGroup[%s] not found"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_OBJECT_NOT_FOUND;
	}

	NGODClient* client = clientSession->getC1Client(); 
	if (!client)
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl,"stream[%s] doReposition() session[%s:%s] failed to access C1 connection"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl, "stream[%s] doReposition() session[%s:%s] messaging thru client[%p]"), streamId.c_str(), ODSessId.c_str(), groupName.c_str(), client);
	RTSPMessage::AttrMap headers;
	MAPSET(RTSPMessage::AttrMap, headers, "OnDemandSessionId", ODSessId);
//	MAPSET(RTSPMessage::AttrMap, headers, "Require",           C1Require);

	double start = (ctrlParams.mask & MASK_TIMEOFFSET) ? static_cast<double>(timeOffset) / 1000.0f : -1.0f; // if the mask of timeoffset is not set, play from now(-1.0)
	int64 stampNow = ZQ::common::now();
	int currentCSeq = client->sendPLAY(*clientSession, start, -1.0f, scale, NULL, headers);
	if (currentCSeq <= 0 || !client->waitForResponse(currentCSeq))
	{
		glog(ZQ::common::Log::L_ERROR,CLOGFMT(NSS,"doReposition() session[%s]cseq(%d) RTSP request failed/timeout [%lld]msec"), ODSessId.c_str(), currentCSeq, ZQ::common::now() - stampNow);
		ZQTianShan::_IceThrow<TianShanIce::ServerError> (glog, "RtspProxying", RTSPSink::rcServiceUnavail, "doReposition() RTSP request failed/timeout");
	}

	adjustPerResponseCode(clientSession);

	if(clientSession->_resultCode == RTSPSink::rcOK) // RTSPOK
	{
		NGODSession::StreamInfos info = clientSession->getInfos();
		ctrlParams.timeoffset = info.timeoffset;
		ctrlParams.duration = info.duration;
		ctrlParams.scale = info.scale;
		ctrlParams.streamState = TianShanIce::Streamer::stsStreaming;
		ctrlParams.mask |= MASK_TIMEOFFSET | MASK_SCALE | MASK_STATE | MASK_CONTENT_DURATION;
	}

	return HandleRtspCode(clientSession, "PLAY");
}

int32 SsServiceImpl::doChangeScale(	 SsServiceImpl& ss, SsContext& contextKey, IN const std::string& streamId,								
								   IN float newScale, INOUT StreamParams& ctrlParams )
{
	std::string ODSessId = contextKey.getContextProperty(ONDEMANDNAME_NAME);
	std::string groupName = contextKey.getContextProperty(SESSION_GROUP);
	if (ODSessId.empty() || groupName.empty())
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl,"stream[%s] doChangeScale() invalid OnDemandSessId[%s] or SessGroup[%s]"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl, "stream[%s] doChangeScale() session[%s]: speed[%f]"), streamId.c_str(), ODSessId.c_str(), newScale);

	NGODSession::Ptr clientSession = NGODSessionGroup::openSession(ODSessId, groupName);
	if (!clientSession)
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl, "stream[%s] doChangeScale() session[%s] of sessGroup[%s] not found"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_OBJECT_NOT_FOUND;
	}

	NGODClient* client = clientSession->getC1Client(); 
	if (!client)
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl, "stream[%s] doChangeScale() session[%s:%s] failed to access C1 connection"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl, "stream[%s] doChangeScale() session[%s:%s] messaging thru client[%p]"), streamId.c_str(), ODSessId.c_str(), groupName.c_str(), client);
	RTSPMessage::AttrMap headers;
	MAPSET(RTSPMessage::AttrMap, headers, "OnDemandSessionId", ODSessId);
//	MAPSET(RTSPMessage::AttrMap, headers, "Require",           C1Require);

	calcScale(newScale, contextKey);
	int64 stampNow = ZQ::common::now();
	int currentCSeq = client->sendPLAY(*clientSession, -1.0f, -1.0f, newScale, NULL, headers);
	if (currentCSeq <= 0 || !client->waitForResponse(currentCSeq))
	{
		glog(ZQ::common::Log::L_ERROR,CLOGFMT(NSS, "doChangeScale() session[%s]cseq(%d) RTSP request failed/timeout [%lld]msec"), ODSessId.c_str(), currentCSeq, ZQ::common::now() - stampNow);
		ZQTianShan::_IceThrow<TianShanIce::ServerError> (glog, "RtspProxying", RTSPSink::rcServiceUnavail, "doChangeScale() RTSP request failed/timeout ");
	}

	adjustPerResponseCode(clientSession);

	if(clientSession->_resultCode == RTSPSink::rcOK) // RTSPOK
	{
		NGODSession::StreamInfos info = clientSession->getInfos();
		ctrlParams.timeoffset = info.timeoffset;
		ctrlParams.duration = info.duration;
		ctrlParams.scale = info.scale;
		ctrlParams.streamState = TianShanIce::Streamer::stsStreaming;
		ctrlParams.mask |= MASK_TIMEOFFSET | MASK_SCALE | MASK_STATE | MASK_CONTENT_DURATION;
	}
	return HandleRtspCode(clientSession, "PLAY");
}

int32 SsServiceImpl::doGetStreamAttr(	 SsServiceImpl& ss, SsContext& contextKey, IN	const std::string& streamId,
									 IN  const TianShanIce::Streamer::PlaylistItemSetupInfo& info, OUT StreamParams& ctrlParams )
{
	bool bIsOnRestore = ( 0 != (ctrlParams.mask & MASK_SESSION_RESTORE) );

	std::string ODSessId = contextKey.getContextProperty(ONDEMANDNAME_NAME);
	std::string groupName = contextKey.getContextProperty(SESSION_GROUP);
	if (ODSessId.empty() || groupName.empty())
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl, "stream[%s] doGetStreamAttr() invalid OnDemandSessId[%s] or SessGroup[%s]"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return bIsOnRestore ? ERR_RETURN_OBJECT_NOT_FOUND :ERR_RETURN_INVALID_PARAMATER;
	}

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl, "stream[%s] doGetStreamAttr() session[%s]: OnRestore[%c]"), streamId.c_str(), ODSessId.c_str(), (bIsOnRestore?'T':'F'));

	NGODSession::Ptr clientSession = NGODSessionGroup::openSession(ODSessId, groupName, bIsOnRestore);
	if (!clientSession)
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl, "stream[%s] doGetStreamAttr() session[%s] of sessGroup[%s] not found"), streamId.c_str(), ODSessId.c_str(), groupName.c_str());
		return ERR_RETURN_OBJECT_NOT_FOUND;
	}

	if (bIsOnRestore)
	{
		std::string sessionId = contextKey.getContextProperty(SESSION_ID);
		std::string dest = contextKey.getContextProperty(DESTINATION_NAME);
		std::string controlUri = contextKey.getContextProperty(CONTROL_URI);

		if(controlUri.empty())
			controlUri = clientSession->getBaseURL();

		clientSession->setSessionId(sessionId);
		clientSession->setControlUri(controlUri);
		clientSession->setStreamDestination(dest.c_str());

		return ERR_RETURN_SUCCESS;
	}

	NGODClient* client = clientSession->getC1Client(); 
	if (!client)
	{
		glog(::ZQ::common::Log::L_ERROR, CLOGFMT(SsServiceImpl, "stream[%s] doGetStreamAttr() failed to allocate NGODClient to Server %s"), streamId.c_str(), clientSession->controlUri());
		return ERR_RETURN_INVALID_PARAMATER;
	}

	RTSPRequest::AttrList parameterNames;
	parameterNames.push_back("scale");
	parameterNames.push_back("position");
	parameterNames.push_back("presentation_state");

	glog(::ZQ::common::Log::L_DEBUG, CLOGFMT(SsServiceImpl, "stream[%s] doGetStreamAttr() session[%s:%s] messaging thru client[%p]"), streamId.c_str(), ODSessId.c_str(), groupName.c_str(), client);
	RTSPMessage::AttrMap headers;
	MAPSET(RTSPMessage::AttrMap, headers, "Content-Type",      "text/parameters");
//	MAPSET(RTSPMessage::AttrMap, headers, "Require",           C1Require);
	MAPSET(RTSPMessage::AttrMap, headers, "OnDemandSessionId", ODSessId);

	int64 stampNow = ZQ::common::now();
	int currentCSeq = client->sendGET_PARAMETER(*clientSession, parameterNames, NULL, headers);
	if (currentCSeq <= 0 || !client->waitForResponse(currentCSeq))
	{
		glog(ZQ::common::Log::L_ERROR,CLOGFMT(NSS, "doGetStreamAttr() session[%s]cseq(%d) RTSP request failed/timeout [%lld]msec"), ODSessId.c_str(), currentCSeq, ZQ::common::now() -stampNow);
		ZQTianShan::_IceThrow<TianShanIce::ServerError> (glog, "RtspProxying", RTSPSink::rcServiceUnavail, "doGetStreamAttr() RTSP request failed/timeout ");
	}

	ctrlParams.mask = 0;
	if (clientSession->_resultCode == RTSPSink::rcOK) // RTSPOK
	{
		NGODSession::StreamInfos info = clientSession->getInfos();
		ctrlParams.timeoffset = info.timeoffset;
		ctrlParams.scale = info.scale;
		ctrlParams.streamState = convertState(info.state);
		ctrlParams.mask = MASK_TIMEOFFSET|MASK_SCALE|MASK_CONTENT_DURATION|MASK_STATE|MASK_STREAM_STATE;
	}	

	return HandleRtspCode(clientSession, "GETPARAMETER");
}

}}
