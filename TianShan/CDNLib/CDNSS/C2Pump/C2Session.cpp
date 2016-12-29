
#include <ZQ_common_conf.h>
#include <stdarg.h>
#include <FileSystemOp.h>
#include <TimeUtil.h>
#include "C2StreamerEnv.h"
#include "C2SessionManager.h"
#include "C2StreamerService.h"
#include "C2EventUpdater.h"
#include "C2Session.h"
#include "C2SessionHelper.h"



#if defined ZQ_OS_MSWIN
	#define	SESSFMT(x,y) 	CLOGFMT(x, "REQUEST[%s]\t"##y), request->requestHint.c_str() 
#elif defined ZQ_OS_LINUX
	#define	SESSFMT(x,y) 	CLOGFMT(x, "REQUEST[%s]\t"y), request->requestHint.c_str() 
#endif	

namespace C2Streamer
{


void C2Session::updateLastError( C2Streamer::RequestParamPtr request, RequestResponseParamPtr response, int errorCode, const char* fmt, ... )
{
	char szLocalBuffer[1024];
	szLocalBuffer[sizeof(szLocalBuffer)-1] = 0;
	va_list args;
	va_start( args, fmt );
	int nCount = vsnprintf( szLocalBuffer, sizeof(szLocalBuffer) - 1,fmt, args );
	if( nCount < 0 )
		szLocalBuffer[sizeof(szLocalBuffer)-1] = 0;
	else
		szLocalBuffer[nCount] = 0;
	va_end(args);
	response->setLastErr(errorCode,szLocalBuffer);
	MLOG(ZQ::common::Log::L_ERROR,SESSFMT(C2Session,"%s"),szLocalBuffer);
}


#undef SESSFMT
#if defined ZQ_OS_MSWIN
	#define	SESSFMT(x,y) 	CLOGFMT(x, "[%s]\t"##y), mSessionId.c_str()
#elif defined ZQ_OS_LINUX
	#define	SESSFMT(x,y) 	CLOGFMT(x, "[%s]\t"y), mSessionId.c_str() 
#endif	

C2Session::C2Session( C2StreamerEnv& env, C2Service& svc,const std::string& sessId)
:mEnv(env),
mSvc(svc),
mSessionId(sessId),
mUdpSessionState(UDPSTATE_NONE),
mTimeoutInterval(500),
mStartTimeInState(0),
mSessionState(SESSION_STATE_NULL),
mCurrentDataRunner(0),
mNextWakeUpTime(0),
mSessionType(SESSION_TYPE_NORMAL),
mbMainFile(false),
mConfWriter(NULL),
mReaderType(-1)
{
	mCurrentDataRunner = new SessionDataRunner( env, svc, this, mSvc.getCacheCenter(), *this, svc.getSessManager().genSubSessionId() );
	MLOG(ZQ::common::Log::L_DEBUG,SESSFMT(C2Session,"session is created"));
}

C2Session::~C2Session(void)
{
	MLOG(ZQ::common::Log::L_DEBUG,SESSFMT(C2Session,"session is deleted"));
	clearAllRunners();
}

void C2Session::clearAllRunners() {
	ZQ::common::MutexGuard gd(*this);
	//FIXME: not implemented
}

void C2Session::markAsConnBroken() {
	mCurrentDataRunner->markAsConnBroken();
}

void C2Session::postDestroy() {
	ZQ::common::MutexGuard gd(*this);
	changeState( SESSION_STATE_DELETED, false );
	mSvc.unwatchSession(this);
	mCurrentDataRunner = NULL;
	mDataReadCb = NULL;
	mReachFileEndCb = NULL;
	mWritableCb = NULL;
	mAsyncTimer = NULL;
	mAsyncStopRunner = NULL;
}

void C2Session::destroy()
{
	ZQ::common::MutexGuard gd(*this);
	cancelTimer();

	if( mSessionState == SESSION_STATE_DELETED )
	{
		MLOG(ZQ::common::Log::L_INFO,SESSFMT(C2Session,"session was already destroyed, free it"));
		return;
	}
	unregisterSession();
	if(!mCurrentDataRunner) {
		return;
	}
	if( mAsyncStopRunner ) {
		mAsyncStopRunner->queueWork();
		return;
	} else {
		MLOG.debug(SESSFMT(destroy, "stop current data runner"));
		mCurrentDataRunner->stopRunner();
		postDestroy();
	}
}

void C2Session::changeState(const SessionState& targetState, bool bUpdateTimer )
{
	ZQ::common::MutexGuard gd(*this);
	if( mSessionState == targetState )
		return;
	MLOG(ZQ::common::Log::L_INFO, SESSFMT(C2Session, "changeState from [%s] to [%s], timeout interval[%d]"),
		 convertSessionStateToString(mSessionState),
		 convertSessionStateToString(targetState),
		 mTimeoutInterval );
		 
	mSessionState = targetState;
	mStartTimeInState = ZQ::common::now();
	
	if( bUpdateTimer )
		updateTimer( mTimeoutInterval );
	
	
	TransferStateUpdateEvent* e = new TransferStateUpdateEvent();
	e->clientTransfer 	= mClientTransferAddress;
	e->transferId		= constructResponseSessId( mSessionId );
	e->sessionState		= mSessionState;
	e->eventmethod			= METHOD_SESS_UPDATE;
	mSvc.getEventPublisher().post(e);
}

void C2Session::reportUdpSessionScaleChange( int64 subSessId, float oldScale, float newScale, int64 timeOffset ) {
	MLOG.info( SESSFMT(C2Session, "udp session[%ld], scale change from[%f] to [%f], timeOffset[%ld] "), subSessId, oldScale, newScale, timeOffset );
	C2UdpSessionEventPtr e = new C2UdpSessionEvent( );
	e->event = C2UdpSessionEvent::UDPEVENT_SCALE_CHANGE;
	e->subSessId = subSessId;
	e->oldStatus.scale = oldScale;
	e->newStatus.scale = newScale;
	mSvc.getEventPublisher().post(e);
}


void C2Session::reportUdpSessionStateChange( int64 subSessId, UdpSessionState oldState, UdpSessionState newState, int64 timeOffset ) {
	MLOG.info( SESSFMT(C2Session, "udp session[%ld], state change from[%s] to[%s], timeOffset[%ld]"), subSessId, UdpSessionStateToString(oldState), UdpSessionStateToString(newState), timeOffset );
	C2UdpSessionEventPtr e = new C2UdpSessionEvent( );
	e->event = C2UdpSessionEvent::UDPEVENT_STATE_CHANGE;
	e->subSessId = subSessId;
	e->oldStatus.state= oldState;
	e->newStatus.state = newState;
	mSvc.getEventPublisher().post(e);
}

void C2Session::reportUdpSessionDone( int64 subSessId ) {
	MLOG.info( SESSFMT(C2Session, "udp session[%ld] done"), subSessId );
	C2UdpSessionEventPtr e = new C2UdpSessionEvent( );
	e->event = C2UdpSessionEvent::UDPEVENT_SESSION_DONE;
	e->subSessId = subSessId;
	mSvc.getEventPublisher().post(e);
}

void C2Session::setRequestType( int32 type )
{
	mSessionType = type;
}

void C2Session::cancelTimer( ) 
{
	mSvc.unwatchSession(this);
}

void C2Session::updateTimer( int64 timeInterval )
{
	mNextWakeUpTime = ZQ::common::now() + timeInterval;
	mSvc.watchSession( this, timeInterval );
}

void C2Session::unregisterSession()
{
	if( !mClientTransferAddress.empty() )
	{
		mSvc.getClientManager().unregisterSession( mClientTransferAddress, mSessionId, mSessionTransferRate );
		mClientTransferAddress = "";
	}
	
	if( !mServerTransferAddress.empty() )
	{
		mSvc.getPortManager().unregisterSession( mServerTransferAddress, mSessionId, mSessionTransferRate);
		mServerTransferAddress = "";
	}
	mSvc.getSessManager().removeSession( mSessionId );
}

#ifdef ABS
#	undef ABS
#endif

#define ABS(x) (x>0?x:-x)

void C2Session::onTimer()
{

	switch( mSessionState )
	{
	case SESSION_STATE_NULL:		
	case SESSION_STATE_DELETED:		
	case SESSION_STATE_IDLE:
		{
			MLOG(ZQ::common::Log::L_INFO, SESSFMT(C2Session,"state[%s] onTimer()"),
				convertSessionStateToString(mSessionState));
			destroy();
		}
		break;

	case SESSION_STATE_ACTIVE:
		{
			return;// ignore this time if session is active
			/*
			int64 cur = ZQ::common::now();
			int64 delta = cur - (int64)mNextWakeUpTime;			
			if( delta > mEnv.getConfig().mTimerThreadHold )
			{
				MLOG(ZQ::common::Log::L_DEBUG, SESSFMT(C2Session,"onTimer() target wakeup time[%lu] now[%ld] delta[%ld]"),
				 mNextWakeUpTime, cur, delta );
			}
			runSession( delta );
			*/
		}
		break;
	
	default:
		{
			assert(false);
		}
		break;
	}
}

const std::string& C2Session::getSessId( ) const
{
	return mSessionId;
}
	
int64 C2Session::getReservedBandwidth( ) const
{
	ZQ::common::MutexGuard gd(*this);
	return mCurrentDataRunner->getReservedBandwidth();
}

SessionState C2Session::getState( ) const
{
	return mSessionState;
}

std::string C2Session::getFileName( ) const
{
	ZQ::common::MutexGuard gd(*this);
	if(!mCurrentDataRunner) {
		return std::string("");
	}
	return mCurrentDataRunner->getFileName();
}

int64 C2Session::getBytesTransfered( ) const
{
	ZQ::common::MutexGuard gd(*this);
	return mCurrentDataRunner->getBytesTransfered();
}

std::string C2Session::getTransferServerAddress( ) const
{
	return mServerTransferAddress;
}

std::string C2Session::getTransferClientAddress( ) const
{
	return mClientTransferAddress;
}

std::string C2Session::getTransferPortName( ) const
{
	return mServerTransferPortName;
}

int64 C2Session::getTimeInState( ) const
{
	int64 cur = ZQ::common::now();
	return (cur - mStartTimeInState);
}

int64 C2Session::getTransferRate( ) const
{
	ZQ::common::MutexGuard gd(*this);
	return mCurrentDataRunner->getTransferRate();
}

void fixupRequestFilePathname(const ConfUrlRule* rule, std::string& fileName)
{
	if( !rule )
		return;
	fileName = fsConcatPath( rule->fsPath, fileName );
}
/*
void fixupRequestFilePathname( TransferInitRequestParamPtr request ) {
	const ConfUrlRule* rule = request->getConfUrlRule();
	if(!rule)
		return;
	request->fileName = fsConcatPath( rule->fsPath, request->fileName );
}
*/
int32 C2Session::processRequest( RequestParamPtr request, RequestResponseParamPtr response )
{
	//fixup file pathname if available
	if( mSessionState == SESSION_STATE_DELETED )
	{
		MLOG(ZQ::common::Log::L_ERROR,SESSFMT(C2Session,"processRequest() session is destroyed"));
		return errorCodeSessionGone;
	}

	int32 retCode = errorCodeNotImplemented;
	switch( request->method )
	{
	case METHOD_TRANSFER_INIT:
	{
		TransferInitRequestParamPtr t 	= TransferInitRequestParamPtr::dynamicCast(request);
		TransferInitResponseParamPtr s	= TransferInitResponseParamPtr::dynamicCast(response);
		assert(t);assert(s);
		fixupRequestFilePathname( t->getConfUrlRule(), t->fileName );
		retCode = processTransferInit(t,s);
		changeState( SESSION_STATE_IDLE );
	}
	break;
	case METHOD_TRANSFER_TERM:
	{
		TransferTermRequestParamPtr t = TransferTermRequestParamPtr::dynamicCast( request );
		TransferTermResponseParamPtr s = TransferTermResponseParamPtr::dynamicCast( response );
		assert(t);assert(s);
		retCode = processTransferTerm( t, s );
	}
	break;
	case METHOD_TRANSFER_RUN:
	{
		cancelTimer();
		SessionTransferParamPtr t 	= SessionTransferParamPtr::dynamicCast(request);
		SessionTransferResponseParamPtr s	= SessionTransferResponseParamPtr::dynamicCast(response);
		assert(t);assert(s);
		retCode = processTransferSession(t,s);
		if( isSuccessCode(retCode) || retCode == errorWorkingInProcess) {
			cancelTimer();
		} else {
			updateTimer(mTimeoutInterval);
		}

	}
	break;
	case METHOD_UDP_INIT:
	{
		UdpStreamInitRequestParamPtr t 	= UdpStreamInitRequestParamPtr::dynamicCast(request);
		UdpStreamInitResponseParamPtr s	= UdpStreamInitResponseParamPtr::dynamicCast(response);
		assert(t);assert(s);
		fixupRequestFilePathname( t->getConfUrlRule(), t->fileName );
		retCode = processUdpInit(t,s);

	//	retCode = processTransferInit(t,s);
		changeState( SESSION_STATE_IDLE );
		break;
	}
	case METHOD_UDP_RUN:
	{
		cancelTimer();
		SessionUdpControlRequestParamPtr t  = SessionUdpControlRequestParamPtr::dynamicCast(request);
		SessionUdpControlResponseParamPtr s = SessionUdpControlResponseParamPtr::dynamicCast(response);
		assert(t);assert(s);
		retCode = processSessionUdpControl(t,s);
		if( isSuccessCode(retCode) || retCode == errorWorkingInProcess) {
			cancelTimer();
		} else {
			updateTimer(mTimeoutInterval);
		}
	}
	case METHOD_SESSION_STATUS:
	{
	}
	break;	
	case METHOD_RESOURCE_STATUS:
	{
	}
	break;	
	default:	
		return errorCodeBadRequest;
	
	}
	return retCode;
}

void C2Session::onRunnerDataGotten( bool bCheckFileEnd) {
	if(!mCurrentDataRunner)
		return;
	mCurrentDataRunner->onDataGotten( bCheckFileEnd );
}

void C2Session::onRunnerWritable() {
	if(!mCurrentDataRunner)
		return;
	mCurrentDataRunner->onWritable();
}

void C2Session::onAsyncTimer() {
	if(!mCurrentDataRunner || mSessionState == SESSION_STATE_DELETED) 
		return;
	mCurrentDataRunner->onAsyncTimer();
}

void C2Session::onAsyncStopRunner( bool bDestroyed ) {
	MLOG.debug(SESSFMT(onAsyncStopRunner, "stop current runner"));
	if(mCurrentDataRunner) {
		mCurrentDataRunner->stopRunner( bDestroyed );
	}
	postDestroy();
}

void C2Session::updateAsyncTimer( int64 interval ) {
	if(mAsyncTimer) {
		mAsyncTimer->updateTimer( interval );
	}
}

void C2Session::cancelAsyncTimer( ) {
	if(mAsyncTimer)
		mAsyncTimer->cancelTimer();
}

int64 C2Session::asyncTimerTarget() const {
	if(!mAsyncTimer)
		return 0;
	return mAsyncTimer->target();
}

void C2Session::postReachFileEnd( AssetAttribute::Ptr attr) {
	mCurrentDataRunner->postReachFileEnd( attr, false );
}

/////////////////////
DataReadCallback::DataReadCallback( C2SessionPtr sess, LibAsync::EventLoop* loop , bool bCheckFileEnd)
	:LibAsync::AsyncWork(*loop),
	mC2Session(sess),
 	mbCheckFileEnd(bCheckFileEnd){
}

DataReadCallback::~DataReadCallback() {
}

void DataReadCallback::onNotified() {
	queueWork();
}

void DataReadCallback::onAsyncWork() {
	mC2Session->onRunnerDataGotten( mbCheckFileEnd );
}
/////////////
HttpWritableCallback::HttpWritableCallback( C2SessionPtr sess )
:mC2Session(sess){
}

HttpWritableCallback::~HttpWritableCallback() {
}

void HttpWritableCallback::onWritable() {
	mC2Session->onRunnerWritable();
}

//////////////
C2SessionAsyncTimer::C2SessionAsyncTimer( C2SessionPtr sess, LibAsync::EventLoop* loop ):
LibAsync::Timer(*loop),
mC2Session(sess){
}

C2SessionAsyncTimer::~C2SessionAsyncTimer() {
}

void C2SessionAsyncTimer::onTimer() {
	mC2Session->onAsyncTimer();
}

//class TransferInitCallbackForLoop
TransferInitCallbackForLoop::TransferInitCallbackForLoop(C2StreamerEnv&	 env, C2Session::Ptr sess, LibAsync::EventLoop* loop, TransferInitResponseParamPtr response, AssetAttribute::Ptr attr)
:LibAsync::AsyncWork( *loop ),
mEnv(env),
mC2Session(sess),
mResponse(response), 
mAttr(attr)
{

}

TransferInitCallbackForLoop::~TransferInitCallbackForLoop()
{

}

void TransferInitCallbackForLoop::onNotified()
{
	  queueWork();
}

void TransferInitCallbackForLoop::onAsyncWork()
{
	 MLOG(ZQ::common::Log::L_DEBUG,CLOGFMT(TransferInitCallbackForLoop, "onAsyncWork() sess[%s] wait for attr reqID[%ld] with lasterror[%d] successful."), mC2Session->getSessId().c_str(), mAttr->reqId(), mAttr->lastError());
	  if( mAttr->lastError() == 0 ) {
			mResponse->baseinfo = mAttr->assetBaseInfo();
			mResponse->memberinfo = mAttr->assetMemberInfo();
			mResponse->openForWrite = mAttr->pwe();
	  }
	  mResponse->response();
}

//class TransferInitCallbackForOther
TransferInitCallbackForOther::TransferInitCallbackForOther(C2StreamerEnv& env,  C2Session::Ptr sess, AssetAttribute::Ptr attr)
:mEnv(env),
mC2Session(sess),
mAttr(attr)
{
}

TransferInitCallbackForOther::~TransferInitCallbackForOther()
{
}

void TransferInitCallbackForOther::onNotified()
{
	  mSemWait.post();
	  MLOG(ZQ::common::Log::L_DEBUG,CLOGFMT(TransferSessionCallbackForBuf,"onAsyncWork() sess[%s] wait for attr reqID[%ld] with successful."), mC2Session->getSessId().c_str(), mAttr->reqId());
}

//class TransferSessionCallbackForBuf
TransferSessionCallbackForBuf::TransferSessionCallbackForBuf(C2StreamerEnv&	 env, C2Session::Ptr sess, LibAsync::EventLoop* loop, RequestParamPtr request, RequestResponseParamPtr response, BufferUser us)
:LibAsync::AsyncWork(*loop),
mEnv(env),
mC2Session(sess), 
mResponse(response), 
mRequest(request),
mBufUser(us)
{
}

TransferSessionCallbackForBuf::~TransferSessionCallbackForBuf()
{
}

void TransferSessionCallbackForBuf::onNotified()
{	 
	  queueWork();
}
void TransferSessionCallbackForBuf::onAsyncWork()
{
	if( mC2Session->getState() == SESSION_STATE_DELETED) {
		MLOG.info( CLOGFMT(TransferSessionCallbackForBuf, "onAsyncWork() sess[%s] buff reqID[%ld] signalled, but session is in deleted state"),
				mC2Session->getSessId().c_str(), mBufUser.bufReqId());
		return;
	}
	int lastError = mBufUser.lastError();
	MLOG(ZQ::common::Log::L_DEBUG,CLOGFMT(TransferSessionCallbackForBuf,"onAsyncWork() sess[%s] wait for buff reqID[%ld] with lasterror[%d] successful."), mC2Session->getSessId().c_str(), mBufUser.bufReqId(), lastError);
	if ( lastError != 0 )
	{
		int category = lastError >> 28;
		lastError = lastError & 0x0FFFFFFF;
		switch( category ) {
			case Buffer::ECATE_FILEIO:
				lastError = errorCodeInternalError;
				break;
			case Buffer::ECATE_HTTP:
				break;
			case Buffer::ECATE_TIMEOUT:
				//FIXME: should check asset attribute first                      
				lastError = errorCodeGatewayTimeout;
				goto CHECK_ATTR;
				break;
			default:
				lastError = errorCodeInternalError;
				break;
		}
		mC2Session->updateLastError( mRequest, mResponse, lastError,"processSessionTransfer() failed to get file data");
		mResponse->response();
		return;
	}
CHECK_ATTR:
	bool cacheAble;
	int errCode = mC2Session->checkFileAttr(mRequest, cacheAble, mResponse, mBufUser);
	if (errCode != errorWorkingInProcess)
		mC2Session->setResponse(errCode, mResponse, mRequest, cacheAble);
}

//class TransferSessionCallbackForAtt
TransferSessionCallbackForAtt::TransferSessionCallbackForAtt(C2StreamerEnv&	 env, C2Session::Ptr sess, LibAsync::EventLoop* loop, RequestParamPtr request, RequestResponseParamPtr response, AssetAttribute::Ptr attr)
:LibAsync::AsyncWork(*loop),
mEnv(env),
mC2Session(sess), 
mResponse(response), 
mRequest(request),
mAttr(attr)
{

}

TransferSessionCallbackForAtt::~TransferSessionCallbackForAtt()
{
}

void TransferSessionCallbackForAtt::onNotified()
{
	  queueWork();
}

void TransferSessionCallbackForAtt::onAsyncWork()
{
	  int lastError = mAttr->lastError();
	 MLOG(ZQ::common::Log::L_DEBUG,CLOGFMT(TransferSessionCallbackForAtt, "onAsyncWork() sess[%s] wait for attr reqID[%ld] with lasterror[%d] successful."), mC2Session->getSessId().c_str(), mAttr->reqId(), lastError);
	 mC2Session->setResponse(lastError, mResponse, mRequest, !mAttr->pwe());
}

//class SessionStopRunnerAsyncWork
SessionStopRunnerAsyncWork::SessionStopRunnerAsyncWork( C2SessionPtr sess, LibAsync::EventLoop* loop )
:LibAsync::AsyncWork(*loop),
mC2Session(sess){
}

SessionStopRunnerAsyncWork::~SessionStopRunnerAsyncWork() {
}

void SessionStopRunnerAsyncWork::onAsyncWork() {
	mC2Session->onAsyncStopRunner( true );
}


}//namespace C2Streamer
