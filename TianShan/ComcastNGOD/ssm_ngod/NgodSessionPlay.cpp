
#include <ZQ_common_conf.h>
#include <TianShanIceHelper.h>
#include "ngod.h"
#include "NgodSession.h"
#include "NgodEnv.h"
#include "NgodSessionManager.h"
#include "SelectionCommand.h"
#include "NgodConfig.h"
#include "SOPConfig.h"

namespace NGOD
{


#if defined ZQ_OS_MSWIN
#define	SESSFMT(x,y) 	"[%s]%s/%s/%s/%08X/REQUEST[%s]\t"##y, request->sessionId.c_str() ,  request->cseq.c_str(), request->verbstr.c_str(), request->ondemandId.c_str() , GetCurrentThreadId(),#x	
#elif defined ZQ_OS_LINUX
#define	SESSFMT(x,y) 	"[%s]%s/%s/%s/%08X/REQUEST[%s]\t"y, request->sessionId.c_str() ,  request->cseq.c_str(), request->verbstr.c_str(), request->ondemandId.c_str() , pthread_self(),#x	
#endif	

class AsyncPlayResponse
{
public:
	AsyncPlayResponse( NGOD::NgodSessionIPtr sess ,NGOD::NgodClientRequestPtr request,  NgodEnv& env, NgodSessionManager& manager , const std::string& streamerNetId )
		:mSess(sess),
		request(request),
		mEnv(env),
		mSessManager(manager),
		mStreamerNetId(streamerNetId)
	{
	}
	virtual ~AsyncPlayResponse(){}

protected:
	
	void		aResponse( const ::TianShanIce::Streamer::StreamInfo& info );
	void		aException( const ::Ice::Exception& ex );
protected:
	NgodSessionIPtr					mSess;
	NGOD::NgodClientRequestPtr		request;
	NgodEnv&						mEnv;
	NgodSessionManager&				mSessManager;
	std::string						mStreamerNetId;
};

class AsyncPlayStreamResponse : public AsyncPlayResponse , public TianShanIce::Streamer::AMI_Stream_playEx
{
public:
	AsyncPlayStreamResponse( NGOD::NgodSessionIPtr sess ,NGOD::NgodClientRequestPtr request,  NgodEnv& env, NgodSessionManager& manager , const std::string& streamerNetId )
		:AsyncPlayResponse( sess , request , env, manager , streamerNetId )
	{

	}
	virtual ~AsyncPlayStreamResponse(){}
public:
	virtual void ice_response(const ::TianShanIce::Streamer::StreamInfo& info )
	{
		aResponse(info);
	}
	virtual void ice_exception(const ::Ice::Exception& ex)
	{
		aException( ex );
	}
};
class AsyncPlayItemResponse  : public AsyncPlayResponse , public TianShanIce::Streamer::AMI_Playlist_playItem
{
public:
	AsyncPlayItemResponse( NGOD::NgodSessionIPtr sess ,NGOD::NgodClientRequestPtr request,  NgodEnv& env, NgodSessionManager& manager , const std::string& streamerNetId )
		:AsyncPlayResponse( sess , request , env, manager , streamerNetId )
	{
	}
	virtual ~AsyncPlayItemResponse(){}
public:
	virtual void ice_response(const ::TianShanIce::Streamer::StreamInfo& info )
	{
		aResponse(info);
	}
	virtual void ice_exception(const ::Ice::Exception& ex)
	{
		aException( ex );
	}
};

void AsyncPlayResponse::aResponse( const ::TianShanIce::Streamer::StreamInfo& info )
{
	NGOD::NgodClientRequestIPtr requesti	= NGOD::NgodClientRequestIPtr::dynamicCast( request );
	ServerResponsePlayPtr response			= ServerResponsePlayPtr::dynamicCast( requesti->getResponse() );
	assert( response != NULL );

	NGOD::NgodRequestPlayPtr playRequest = NGOD::NgodRequestPlayPtr::dynamicCast(requesti);
	const PlayParam& para = playRequest->getPlayParam();

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
	response->setScale( szBufScale );
	
	MLOG( ZQ::common::Log::L_INFO,SESSFMT(AsyncPlayResponse,"got stream info: scale [%s] npt[%s-%s]"), szBufScale , szBufStart , szBufEnd );
	if(ngodConfig.publishLogs.enabled)
	{
		ELOG(ZQ::common::Log::L_INFO, EVENTLOGFMT(AsyncPlayResponse,"state(%s)"), errorCodeTransformer(errorcodeOK) );
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
	MLOG(ZQ::common::Log::L_INFO,SESSFMT(AsyncPlayResponse,"add session record: item npt[%s] scale[%s] resourceId[%d]"),szBufItemNpt , szBufScale , iCtrlNum );
	if ( ngodConfig.sessionHistory.enablePlayEvent )
	{
		std::string     strUserTime;
		ZQTianShan::Util::getPropertyDataWithDefault( info.props , "echo.Time" , getISOTimeString() , strUserTime );
		mSess->addSCEventRecord( "PLAY" , strNewState , szBufItemNpt , szBufScale , ossCtrlNum.str() , strUserTime , errorcodeOK , para.reqRange , para.reqScale );
	}

	// This is a trick on accessing NgodSession::mStreamSessId directly, DO nottrying to modify this value	
	mEnv.getStatCache().statChanged( mSess->mStreamSessId,llItemNpt,scale,TianShanIce::Streamer::stsStreaming);
}
void AsyncPlayResponse::aException( const ::Ice::Exception& ex )
{
	NGOD::NgodClientRequestIPtr requesti = NGOD::NgodClientRequestIPtr::dynamicCast( request );
	assert( requesti != NULL );

	NGOD::NgodRequestPlayPtr playRequest = NGOD::NgodRequestPlayPtr::dynamicCast(requesti);
	const PlayParam& para = playRequest->getPlayParam();

	int32 errCode	= errorcodeInternalError;
	std::string errMsg;
	
	bool bSockTransmitError = false;

	try
	{
		ex.ice_throw();
	}
	catch( const Ice::ObjectNotExistException& ex )
	{
		errCode	= errorcodeObjNotFound;
		errMsg	= ex.ice_name();
		MLOG(ZQ::common::Log::L_WARNING,SESSFMT(AsyncPlayResponse,"caugh [%s], destroy current session"), ex.ice_name().c_str() );
		mSess->destroy(NULL);
	}
	catch( const Ice::TimeoutException& ex )
	{
		bSockTransmitError = true;
		errMsg	= ex.ice_name();
		errCode	= errorcodeServiceUnavail;
		if(sopConfig.sopRestrict.penaltyEnableMask & PENALTY_ENABLE_MASK_PLAY )
			mEnv.mSelManager.applyIncreasablePenalty( mSess->getSessionId(), mStreamerNetId, sopConfig.sopRestrict.timeoutPenalty,sopConfig.sopRestrict.maxPenaltyValue);
	}
	catch( const Ice::SocketException& ex)
	{
		bSockTransmitError = true;
		errCode	= errorcodeServiceUnavail;
		errMsg		= ex.ice_name();
		if(sopConfig.sopRestrict.penaltyEnableMask & PENALTY_ENABLE_MASK_PLAY )
			mEnv.mSelManager.applyPenalty( mSess->getSessionId(),  mStreamerNetId, sopConfig.sopRestrict.maxPenaltyValue);
	}	
	catch( const TianShanIce::InvalidStateOfArt& ex)
	{
		errMsg	= ex.message;
		errCode = errorcodeTrickRestriction;
	}
	catch( const TianShanIce::InvalidParameter& ex)
	{
		switch(ex.errorCode )
		{
		case EXT_ERRCODE_INVALID_RANGE:			{	errCode = errorcodeInvalidRange;	}
			break;
		case EXT_ERRCODE_BANDWIDTH_EXCEEDED:	{	errCode = errorcodeNotEnoughBandwidth;		}
			break;
		default:								{	errCode = errorcodeBadParameter;	}
			break;
		}
		errMsg = ex.message;
	}
	catch( const TianShanIce::ServerError& ex )
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
	catch( const TianShanIce::BaseException& ex)
	{
		errCode	= errorcodeInternalError;
		errMsg	= ex.message;
	}
	catch( const Ice::Exception& ex )
	{
		errCode = errorcodeInternalError;
		errMsg	= ex.ice_name();
	}
	MLOG(ZQ::common::Log::L_DEBUG,CLOGFMT(AsyncPlayResponse,"got exception[%s]"),errMsg.c_str() );
	std::string		strAssetNpt;
	std::string		strStreamScale;
	std::string		strAssetCtrlNum;
	std::string     strNewState;
	if( !bSockTransmitError )
	{
		mSess->getPlayListInfo(strStreamScale, strAssetNpt, strAssetCtrlNum, strNewState);
	}
	else
	{
		MLOG(ZQ::common::Log::L_WARNING,SESSFMT(AsyncPlayResponse,"data transimission failed, skip getting playlist information"));
	}

	if ( ngodConfig.sessionHistory.enablePlayEvent )
	{
		mSess->addSCEventRecord( "PLAY" , strNewState , strAssetNpt , strStreamScale , strAssetCtrlNum, getISOTimeString() , errCode , para.reqRange , para.reqScale );
	}
	mSess->errlog( requesti , errCode , "failed to execute playStream/PlayItem due to [%s]",errMsg.c_str() );
}

int NgodSessionI::processPlay( const NgodRequestPlayPtr& request )
{
	if( ( sopConfig.sopRestrict.execMask & PENALTY_ENABLE_MASK_PLAY ) ) {
		int penalty = 0;
		if( !mEnv.getSelResManager().isStreamHealthy(mStreamerNetId, &penalty) ) {
			errlog(request, errorcodeServiceUnavail, "streamer[%s] has penalty[%d], reject play request on it",
				mStreamerNetId.c_str(),penalty);
			return errorcodeServiceUnavail;
		}
	}

	ServerResponsePlayPtr response = ServerResponsePlayPtr::dynamicCast( request->getResponse() );
	assert( response != NULL );
	
	updateConnectionAndVerCode( request );

	const PlayParam& para = request->getPlayParam();

	TianShanIce::StrValues expectValues;
	expectValues.push_back("ITEM_CURRENTPOS");
	expectValues.push_back("ITEM_TOTALPOS");	
	expectValues.push_back("CURRENTPOS");
	expectValues.push_back("TOTALPOS");
	expectValues.push_back("SPEED");
	expectValues.push_back("STATE");
	expectValues.push_back("USERCTRLNUM");

	try
	{

		::Ice::Context ctx;
		ctx["echo.Time"] = getISOTimeString();
	
	if( !para.bFromNow )
	{
		MLOG(ZQ::common::Log::L_INFO,SESSFMT(NgodSessionI,"play from: now[%s] npt[%lld] scale[%f]"),para.bFromNow ? "true":"false", para.nptStart , para.scale );		
		mStream->playEx_async( new AsyncPlayStreamResponse(this,request,mEnv,mSessManager,mStreamerNetId) , para.scale ,  para.nptStart , 1 , expectValues , ctx );
	}
	else
	{
		Ice::Int	spIndex = -1;
		Ice::Long	spOffset = 0;
		
		if( getSetupStartPoint(spIndex,spOffset) )
		{
			if( isSessionStreaming() )
			{
				MLOG(ZQ::common::Log::L_INFO,SESSFMT(NgodSessionI,"play from now, current stream is running, startPoint[%d %lld] is available") , spIndex , spOffset );
				mStream->playEx_async( new AsyncPlayStreamResponse(this,request,mEnv,mSessManager,mStreamerNetId) ,
					para.scale ,  0 , 0 , expectValues , ctx);
			}
			else
			{
				MLOG(ZQ::common::Log::L_INFO,SESSFMT(NgodSessionI,"play from: startPoint[%d %lld]"), spIndex , spOffset );		
				mStream->playItem_async( (new AsyncPlayItemResponse(this,request,mEnv,mSessManager,mStreamerNetId) ) , spIndex ,  (Ice::Int)spOffset , 1 , para.scale, expectValues , ctx );
			}
		}
		else
		{
			MLOG(ZQ::common::Log::L_INFO,SESSFMT(NgodSessionI,"play from now, scale[%f]"),para.scale );		
			mStream->playEx_async( new AsyncPlayStreamResponse(this,request,mEnv,mSessManager,mStreamerNetId) ,para.scale ,  0 , 0 , expectValues , ctx );
		}		
	}
	}
	catch( const Ice::Exception& ex)
	{
		errlog(request,errorcodeInternalError,"failed to perform play command due to[%s]",ex.ice_name().c_str() );
		return errorcodeInternalError;
	}
	return errorcodeOK;
}

}//namespace NGOD
