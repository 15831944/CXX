
#include <ZQ_common_conf.h>
#include <TianShanIceHelper.h>
#include "SelectionCommand.h"
#include "ClientRequest.h"
#include "NgodSession.h"
#include "NgodEnv.h"
#include "NgodConfig.h"
#include "SOPConfig.h"

#if defined ZQ_OS_MSWIN
	#define	SESSFMT(x,y) 	"[%s]%s/%s/%s/%08X/REQUEST[%s]\t"##y, request->sessionId.c_str() ,  request->cseq.c_str(), request->verbstr.c_str(), request->ondemandId.c_str() , GetCurrentThreadId(),#x	
#elif defined ZQ_OS_LINUX
	#define	SESSFMT(x,y) 	"[%s]%s/%s/%s/%08X/REQUEST[%s]\t"y, request->sessionId.c_str() ,  request->cseq.c_str(), request->verbstr.c_str(), request->ondemandId.c_str() , pthread_self(),#x	
#endif	

namespace NGOD
{

int NgodSessionI::processGetParam( const NgodRequestGetParameterPtr& request )
{
	bool bStreamerUnvail = false;
	if( ( sopConfig.sopRestrict.execMask & PENALTY_ENABLE_MASK_GETPAR ) ) {
		int penalty = 0;
		bStreamerUnvail = !mEnv.getSelResManager().isStreamHealthy(mStreamerNetId, &penalty) ;
	}

	ServerResponseGetParameterPtr response = ServerResponseGetParameterPtr::dynamicCast( request->getResponse() );
	assert( response != NULL );

	updateConnectionAndVerCode( request );

	int32 errorCode = errorcodeInternalError;
	std::string	errMsg ;

	try
	{
		GetParamResponseInfo respInfo;
		const GetInfoParam& para = request->getParam();	

		MLOG(ZQ::common::Log::L_INFO,SESSFMT(NgodSessionI,"processGetParam() get parameter with mask[%s]"),convertGetInfoParamMask( para.mask ).c_str() );
		if( ( para.mask & GetInfoParam::MASK_SCALE ) || (para.mask & GetInfoParam::MASK_POSITION) )
		{
			StreamSessionInfo ssInfo;
			if( bStreamerUnvail ) {
				MLOG(ZQ::common::Log::L_INFO, SESSFMT(NgodSessionI,"processGetParam(), streamer is not available, use cached stream session info"));
				if(!getCachedSsInfo(ssInfo)) {
					MLOG(ZQ::common::Log::L_ERROR, SESSFMT(NgodSessionI,"processGetParam(), failed to get cache stream session info"));
					return errorcodeServiceUnavail;
				}
			}
			else {
				int ret = getStreamSessionInfo( request , ssInfo);
				if( ret != errorcodeOK ) {
					return ret;
				}
			}

			respInfo.rangeStart = convertIntToNptString( ssInfo.npt );
			if( ssInfo.playTime >= ssInfo.npt && ssInfo.playTime != 0)
				respInfo.rangeEnd	= convertIntToNptString( ssInfo.playTime );
			respInfo.scale = ssInfo.scale;
		}

		if( para.mask & GetInfoParam::MASK_STATE )
		{
			TianShanIce::Streamer::StreamState state = TianShanIce::Streamer::stsStreaming;
			if( bStreamerUnvail) {
				Ice::Int iState = 0;
				{					
					RLock sync(*this);
					ZQTianShan::Util::getPropertyDataWithDefault(mProps,"streamsession_cache_state",0,iState);
				}
				state = (TianShanIce::Streamer::StreamState)iState;
			}
			else {
				state =  mStream->getCurrentState();
				switch( state )
				{
				case TianShanIce::Streamer::stsSetup:			{	respInfo.state = "init";	}
																break;
				case TianShanIce::Streamer::stsStreaming:		{	respInfo.state = "play";	}
																break;
				case TianShanIce::Streamer::stsPause:			{	respInfo.state = "pause";	}
																break;
				case TianShanIce::Streamer::stsStop:			{	respInfo.state = "ready";	 }
																break;
				default:
					{
						respInfo.state	= "unknown";
						assert( false );
					}
					break;
				}
				{
					WLock sync(*this);
					ZQTianShan::Util::updatePropertyData(mProps,"streamsession_cache_state", (int)state);
				}
			}			
		}
		MLOG(ZQ::common::Log::L_INFO,SESSFMT(NgodSessionI,"get stream info npt[%s-%s] scale[%s]"),
					respInfo.rangeStart.c_str() , respInfo.rangeEnd.c_str() , respInfo.scale.c_str() );
		response->setInfo( respInfo );

		if(ngodConfig.publishLogs.enabled)
		{
			ELOG(ZQ::common::Log::L_INFO, EVENTLOGFMT(NgodSessionI,"state(%s)"), errorCodeTransformer(errorcodeOK) );
		}

		return errorcodeOK;
	}
	catch( const Ice::ObjectNotExistException& ex)
	{
		errorCode	= errorcodeObjNotFound;
		errMsg		= ex.ice_name();
		MLOG(ZQ::common::Log::L_WARNING,CLOGFMT(NgodSessionI,"processGetParam() session[%s] failed to get stream instance, destroy current session"), mIdent.name.c_str() );
		if(ngodConfig.publishLogs.enabled)
		{
			ELOG(ZQ::common::Log::L_WARNING,EVENTLOGFMT(NgodSessionI,"session[%s] failed to get stream instance, destroy current session"), mIdent.name.c_str() );
		}
		destroy(NULL);
	}
	catch( const Ice::SocketException& ex)
	{
		errorCode	= errorcodeServiceUnavail;
		errMsg		= ex.ice_name();
		if(sopConfig.sopRestrict.penaltyEnableMask & PENALTY_ENABLE_MASK_GETPAR )
			mEnv.mSelManager.applyPenalty(  mSessId,  mStreamerNetId, sopConfig.sopRestrict.maxPenaltyValue);
	}	
	catch( const Ice::TimeoutException& ex)
	{
		//TODO: add penalty to streamer
		errorCode	= errorcodeServiceUnavail;
		errMsg		= ex.ice_name();
		if(sopConfig.sopRestrict.penaltyEnableMask & PENALTY_ENABLE_MASK_GETPAR )
			mEnv.mSelManager.applyIncreasablePenalty( mSessId, mStreamerNetId, sopConfig.sopRestrict.timeoutPenalty,sopConfig.sopRestrict.maxPenaltyValue);
	}	
	catch( const TianShanIce::BaseException& ex)
	{
		errorCode	= errorcodeInternalError;
		errMsg		=ex.message;
	}
	catch( const Ice::Exception& ex)
	{
		errorCode	= errorcodeInternalError;
		errMsg		= ex.ice_name();
	}

	errlog( request , errorCode , "processGetParam() failed to execute pause command due to [%s]",errMsg.c_str() );

	return errorCode;

}

}

