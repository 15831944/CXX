#ifndef __HAMMER_SESSION__
#define __HAMMER_SESSION__

#include "RTSPClient.h"

class Hammer;
class HammerSession : public ZQ::common::RTSPSession {

public:

	typedef ZQ::common::Pointer<HammerSession> Ptr;
	typedef std::map<std::string, std::string> SessionCtx;

	SessionCtx& ctx() {
		return _ctx;
	}

public:

	HammerSession(Hammer& hammer, uint seqIdx, 
				  ZQ::common::Log&, ZQ::common::NativeThreadPool& pool, 
				  const char* streamURL, const char* filePath, int timeout, const char* id, SessionCtx& ctx);

	virtual ~HammerSession();

public: 

	virtual void OnResponse_GET_PARAMETER(ZQ::common::RTSPClient& rtspClient, 
									ZQ::common::RTSPRequest::Ptr& pReq, 
									ZQ::common::RTSPMessage::Ptr& pResp, 
									uint resultCode, 
									const char* resultString);

	virtual void OnResponse_SETUP(ZQ::common::RTSPClient& rtspClient, 
								  ZQ::common::RTSPRequest::Ptr& pReq, 
								  ZQ::common::RTSPMessage::Ptr& pResp, 
								  uint resultCode, const char* resultString); 

	virtual void OnResponse_PLAY(ZQ::common::RTSPClient& rtspClient, 
								  ZQ::common::RTSPRequest::Ptr& pReq, 
								  ZQ::common::RTSPMessage::Ptr& pResp, 
								  uint resultCode, const char* resultString);
	
	virtual void OnResponse_TEARDOWN(ZQ::common::RTSPClient& rtspClient, 
								  ZQ::common::RTSPRequest::Ptr& pReq, 
								  ZQ::common::RTSPMessage::Ptr& pResp, 
								  uint resultCode, const char* resultString);

public:

	virtual void OnRequestError(ZQ::common::RTSPClient& rtspClient, 
								ZQ::common::RTSPRequest::Ptr& pReq, 
								RequestError errCode, 
								const char* errDesc=0);


private:

	Hammer& _hammer;
	uint _seqIdx;
	uint _cseq;

	SessionCtx _ctx;
};


#endif

// vim: nu ts=4 sw=4 bg=dark

