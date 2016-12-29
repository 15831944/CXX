
#include <ZQ_common_conf.h>
#include <TianShanIceHelper.h>
#include "NgodEnv.h"
#include "SelectionCommand.h"
#include "NgodSession.h"
#include "ClientRequest.h"
#include "NgodConfig.h"
#include "SOPConfig.h"


#if defined ZQ_OS_MSWIN
#define	SESSFMT(x,y) 	"[%s]%s/%s/%s/%08X/REQUEST[%s]\t"##y, request->sessionId.c_str() ,  request->cseq.c_str(), request->verbstr.c_str(), request->ondemandId.c_str() , GetCurrentThreadId(),#x	
#elif defined ZQ_OS_LINUX
#define	SESSFMT(x,y) 	"[%s]%s/%s/%s/%08X/REQUEST[%s]\t"y, request->sessionId.c_str() ,  request->cseq.c_str(), request->verbstr.c_str(), request->ondemandId.c_str() , pthread_self(),#x	
#endif	

namespace NGOD
{

class AsyncPauseResponse : public TianShanIce::Streamer::AMI_Stream_pauseEx
{
public:
	AsyncPauseResponse( NGOD::NgodSessionIPtr sess ,NGOD::NgodClientRequestPtr request,  NgodEnv& env, NgodSessionManager& manager , const std::string& streamerNetId )
		:mSess(sess),
		request(request),
		mEnv(env),
		mSessManager(manager),
		mStreamerNetId(streamerNetId)
	{
	}
	virtual ~AsyncPauseResponse(){}

	virtual void ice_response(const ::TianShanIce::Streamer::StreamInfo& info);
	virtual void ice_exception(const ::Ice::Exception& ex ) ;

protected:
	NgodSessionIPtr					mSess;
	NGOD::NgodClientRequestPtr		request;
	NgodEnv&						mEnv;
	NgodSessionManager&				mSessManager;
	std::string						mStreamerNetId;
};

void AsyncPauseResponse::ice_response(const TianShanIce::Streamer::StreamInfo &info)
{
	NGOD::NgodClientRequestIPtr requesti	= NGOD::NgodClientRequestIPtr::dynamicCast( request );
	ServerResponsePausePtr response			= ServerResponsePausePtr::dynamicCast( requesti->getResponse() );
	assert( response != NULL );

	Ice::Long llStreamNpt = 0 , llStreamEnd = 0;
	Ice::Float scale = ZQTianShan::Util::getSpeedFromStreamInfo(info);
	char szBufScale[64];
	sprintf( szBufScale , "%f" , scale );

	llStreamNpt	= ZQTianShan::Util::getStreamTimeOffset( info );
	llStreamEnd	= ZQTianShan::Util::getStreamTotalDuration( info );

	char szBufStart[64]	= {'\0'};
	char szBufEnd[64]	= {'\0'};

	sprintf(szBufStart,"%lld.%03lld",llStreamNpt/1000,llStreamNpt%1000);
	if( llStreamEnd > 0 )
	{
		sprintf(szBufEnd,"%lld.%03lld",llStreamEnd/1000,llStreamEnd%1000);
	}	
	response->setRange( szBufStart , szBufEnd );
	//response->setScale( szBufScale );

	MLOG( ZQ::common::Log::L_INFO,SESSFMT(AsyncPauseResponse,"got stream info: scale [%s] npt[%s-%s]"), szBufScale , szBufStart , szBufEnd );
	if(ngodConfig.publishLogs.enabled)
	{
		ELOG(ZQ::common::Log::L_INFO, EVENTLOGFMT(AsyncPauseResponse,"state(%s)"), errorCodeTransformer(errorcodeOK) );
	}

	Ice::Int iCtrlNum = ZQTianShan::Util::getUserCtrlNumFromStreamInfo(info);
	std::ostringstream ossCtrlNum;ossCtrlNum<<iCtrlNum;

	Ice::Long llItemNpt = ZQTianShan::Util::getItemTimeOffset( info );
	//llItemNpt = mSess->adjustNptToAssetBased( iCtrlNum - 1 , llItemNpt ); // ctrl num is 1 based
	char szBufItemNpt[64];
	sprintf(szBufItemNpt,"%lld.%03lld",llItemNpt/1000,llItemNpt%1000);

	std::string strNewState;
	switch(info.state)
	{
	case TianShanIce::Streamer::stsSetup:
		{
			strNewState = "INIT";
		}
		break;
	case TianShanIce::Streamer::stsStreaming: 
		{
			strNewState = "PLAY";
		}
		break;
	case TianShanIce::Streamer::stsPause: 
		{
			strNewState = "PAUSE";
		}
		break;
	case TianShanIce::Streamer::stsStop:
		{
			strNewState = "READY";
		}
		break;
	default: 
		{
			strNewState = "UNKNOWN";
		}
		break;
	}			
	MLOG(ZQ::common::Log::L_INFO,SESSFMT(AsyncPauseResponse,"add session record: item npt[%s] scale[%s] resourceId[%d]"),szBufItemNpt , szBufScale , iCtrlNum );
	if ( ngodConfig.sessionHistory.enablePauseEvent )
	{
		std::string     strUserTime;
		ZQTianShan::Util::getPropertyDataWithDefault( info.props , "echo.Time" , getISOTimeString() , strUserTime );
		mSess->addSCEventRecord( "PAUSE" , strNewState , szBufItemNpt , szBufScale , ossCtrlNum.str(), strUserTime );
	}
	mEnv.getStatCache().statChanged( mSess->mStreamSessId, llStreamNpt, scale, TianShanIce::Streamer::stsPause);
}
void AsyncPauseResponse::ice_exception(const ::Ice::Exception& ex )
{
	NGOD::NgodClientRequestIPtr requesti = NGOD::NgodClientRequestIPtr::dynamicCast( request );
	assert( requesti != NULL );

	bool bSockTransmitError = false;
	int32 errCode	= errorcodeInternalError;
	std::string errMsg;
	try
	{
		ex.ice_throw();
	}
	catch( const Ice::ObjectNotExistException& ex )
	{
		errCode	= errorcodeObjNotFound;
		errMsg	= ex.ice_name();
		MLOG(ZQ::common::Log::L_WARNING,SESSFMT(AsyncPauseResponse,"caugh [%s], destroy current session"), ex.ice_name().c_str() );
		mSess->destroy(NULL);
	}	
	catch( const Ice::TimeoutException& ex )
	{
		bSockTransmitError = true;
		errMsg	= ex.ice_name();
		errCode	= errorcodeServiceUnavail;
		if(sopConfig.sopRestrict.penaltyEnableMask & PENALTY_ENABLE_MASK_PAUSE )
			mEnv.mSelManager.applyIncreasablePenalty( mSess->getSessionId(), mStreamerNetId, sopConfig.sopRestrict.timeoutPenalty,sopConfig.sopRestrict.maxPenaltyValue);
	}
	catch( const Ice::SocketException& ex)
	{
		bSockTransmitError = true;
		errCode	= errorcodeServiceUnavail;
		errMsg	= ex.ice_name();
		if(sopConfig.sopRestrict.penaltyEnableMask & PENALTY_ENABLE_MASK_PAUSE )
			mEnv.mSelManager.applyPenalty( mSess->getSessionId(),  mStreamerNetId, sopConfig.sopRestrict.maxPenaltyValue);
	}	
	catch( const TianShanIce::InvalidStateOfArt& ex)
	{
		errMsg	= ex.ice_name();
		errCode = errorcodeTrickRestriction;
	}		
	catch( const TianShanIce::BaseException& ex)
	{
		switch(ex.errorCode )
		{
		case EXT_ERRCODE_INVALID_RANGE:			{	errCode = errorcodeInvalidRange;	}
												break;
		case EXT_ERRCODE_BANDWIDTH_EXCEEDED:	{	errCode = errorcodeNotEnoughBandwidth;		}
												break;
		case EXT_ERRCODE_SERVICEUNAVAIL:		{	errCode = errorcodeServiceUnavail; }
												break;
		default:								{	errCode = errorcodeInternalError;	}
												break;
		}
		errMsg = ex.message;
	}
	catch( const Ice::Exception& ex )
	{
		errCode = errorcodeInternalError;
		errMsg	= ex.ice_name();
	}

	std::string		strAssetNpt;
	std::string		strStreamScale;
	std::string		strAssetCtrlNum;
	std::string     strNewState;

	if(!bSockTransmitError)
	{
		mSess->getPlayListInfo(strStreamScale, strAssetNpt, strAssetCtrlNum, strNewState);
	}
	else
	{
		MLOG(ZQ::common::Log::L_WARNING,SESSFMT(AsyncPauseResponse,"data transimission failed, skip getting playlist information"));
	}

	if ( ngodConfig.sessionHistory.enablePauseEvent )
	{
		mSess->addSCEventRecord( "PAUSE" , strNewState , strAssetNpt , strStreamScale , strAssetCtrlNum , getISOTimeString() , errCode , "" , "" );
	}
	mSess->errlog( requesti , errCode , "failed to execute pause command due to [%s]",errMsg.c_str() );
}


int NgodSessionI::processPause( const NgodRequestPausePtr& request )
{
	if( ( sopConfig.sopRestrict.execMask & PENALTY_ENABLE_MASK_PAUSE ) ) {
		int penalty = 0;
		if( !mEnv.getSelResManager().isStreamHealthy(mStreamerNetId, &penalty) ) {
			errlog(request, errorcodeServiceUnavail, "streamer[%s] has penalty[%d], reject pause request on it",
				mStreamerNetId.c_str(),penalty);
			return errorcodeServiceUnavail;
		}
	}

	ServerResponsePausePtr response = ServerResponsePausePtr::dynamicCast( request->getResponse() );
	assert( response != NULL );

	updateConnectionAndVerCode( request );
	
	TianShanIce::StrValues expectValues;
	expectValues.push_back("ITEM_CURRENTPOS");
	expectValues.push_back("CURRENTPOS");
	expectValues.push_back("TOTALPOS");
	expectValues.push_back("SPEED");
	expectValues.push_back("STATE");
	expectValues.push_back("USERCTRLNUM");

	MLOG(ZQ::common::Log::L_INFO,SESSFMT(NgodSessionI,"pause the session"));
	try
	{
		mStream->pauseEx_async( new AsyncPauseResponse( this , request , mEnv , mSessManager , mStreamerNetId ) , expectValues );
	}
	catch( const Ice::Exception& ex)
	{
		errlog(request,errorcodeInternalError,"failed to perform pause command due to[%s]",ex.ice_name().c_str() );
		return errorcodeInternalError;
	}
	return errorcodeOK;
}

}//namespace NGOD

