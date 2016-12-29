#include "HammerSession.h"
#include "Hammer.h"
#include "ScriptParser.h"

HammerSession::HammerSession(Hammer& hammer, uint seqIdx, 
							 ZQ::common::Log& log, ZQ::common::NativeThreadPool& pool, 
							 const char* streamURL, const char* filePath, int timeout, const char* id, SessionCtx& ctx) 
:RTSPSession(log, pool, streamURL, filePath, ZQ::common::Log::L_DEBUG, timeout, id), 
_hammer(hammer), _seqIdx(seqIdx), _cseq(0), _ctx(ctx) {
}

HammerSession::~HammerSession() {
}

void HammerSession::OnResponse_GET_PARAMETER(
	ZQ::common::RTSPClient& rtspClient, 
	ZQ::common::RTSPRequest::Ptr& req, 
	ZQ::common::RTSPMessage::Ptr& resp, 
	uint resultCode, 
	const char* resultString) {

	_hammer.removeWatch(_seqIdx);
	Hammer::SessSeq& seq = _hammer.getSessSeq(_seqIdx);

	_log(ZQ::common::Log::L_DEBUG, CLOGFMT(HammerSession, 
				"[%d-%d-%d] OnResponse_GET_PARAMETER(%d) return [%d,%s]"), 
				_seqIdx, seq.clientIdx, seq.numLoop, resp->cSeq, resultCode, resultString);

	_hammer.countResponse("GET_PARAMETER", resultCode);

	if(resultCode == ZQ::common::RTSPSink::rcOK) {
		_hammer.OnSessionEvent(ConsoleWriter::SUCCEEDED, ConsoleWriter::RESP);
	}
	else {
		_log(ZQ::common::Log::L_ERROR, CLOGFMT(HammerSession, 
				"[%d-%d-%d] [%s(%d)] failed [%s]"), 
				_seqIdx, seq.clientIdx, seq.numLoop, req->_commandName.c_str(), 
				resp->cSeq, resultString);

//		_hammer.OnSessionEvent(ConsoleWriter::FAILED, ConsoleWriter::RESP);
	
		/* this command can't be skipped, mark the session as failed */
		if(!_hammer.skipCommand(req->_commandName)) {
			_hammer.OnSessionEvent(ConsoleWriter::FAILED, ConsoleWriter::SESS, _seqIdx);
			return;
		}
	}
	
	ZQ::common::Action::Context ctx;
	ctx.metaData = resp->headers;	
	ctx.metaData[SEQ_IDX] = ScriptParser::to_string(_seqIdx);
	_hammer.triggerEvent(Hammer::EVT_RESP, ctx.metaData);
}

void HammerSession::OnResponse_SETUP(
	ZQ::common::RTSPClient& client, 
	ZQ::common::RTSPRequest::Ptr& req, 
	ZQ::common::RTSPMessage::Ptr& resp, 
	uint32 resultCode, 
	const char* resultString) {

	_hammer.removeWatch(_seqIdx);
	Hammer::SessSeq& seq = _hammer.getSessSeq(_seqIdx);

	_log(ZQ::common::Log::L_DEBUG, CLOGFMT(HammerSession, 
				"[%d-%d-%d] OnResponse_SETUP(%d) return [%d,%s]"), 
				_seqIdx, seq.clientIdx, seq.numLoop, resp->cSeq, resultCode, resultString);

	_hammer.countResponse("SETUP", resultCode);

	if(resultCode == ZQ::common::RTSPSink::rcOK) {
		_hammer.OnSessionEvent(ConsoleWriter::SUCCEEDED, ConsoleWriter::RESP);
	}
	else {
		_log(ZQ::common::Log::L_ERROR, CLOGFMT(HammerSession, 
				"[%d-%d-%d] [%s(%d)] failed [%s]"), 
				_seqIdx, seq.clientIdx, seq.numLoop, req->_commandName.c_str(), 
				resp->cSeq, resultString);

//		_hammer.OnSessionEvent(ConsoleWriter::FAILED, ConsoleWriter::RESP);
	
		/* this command can't be skipped, mark the session as failed */
		if(!_hammer.skipCommand(req->_commandName)) {
			_hammer.OnSessionEvent(ConsoleWriter::FAILED, ConsoleWriter::SESS, _seqIdx);
			return;
		}
	}
	
	ZQ::common::RTSPMessage::AttrMap::iterator iter = resp->headers.find("Session");
	if(iter != resp->headers.end()) {
		_sessionId = resp->headers["Session"];	
	}

	ZQ::common::Action::Context ctx;
	ctx.metaData = resp->headers;	
	ctx.metaData[SEQ_IDX] = ScriptParser::to_string(_seqIdx);
	_hammer.triggerEvent(Hammer::EVT_RESP, ctx.metaData);
}

void HammerSession::OnResponse_PLAY(ZQ::common::RTSPClient& rtspClient, 
							  ZQ::common::RTSPRequest::Ptr& req, 
							  ZQ::common::RTSPMessage::Ptr& resp, 
							  uint resultCode, const char* resultString) {
	_hammer.removeWatch(_seqIdx);
	Hammer::SessSeq& seq = _hammer.getSessSeq(_seqIdx);

	_log(ZQ::common::Log::L_DEBUG, CLOGFMT(HammerSession, 
				"[%d-%d-%d] OnResponse_PLAY(%d) return [%d,%s]"), 
				_seqIdx, seq.clientIdx, seq.numLoop, resp->cSeq, resultCode, resultString);

	_hammer.countResponse("PLAY", resultCode);
	if(resultCode == ZQ::common::RTSPSink::rcOK) {
		_hammer.OnSessionEvent(ConsoleWriter::SUCCEEDED, ConsoleWriter::RESP);
	}
	else {
		_log(ZQ::common::Log::L_ERROR, CLOGFMT(HammerSession, 
				"[%d-%d-%d] [%s(%d)] failed [%s]"), 
				_seqIdx, seq.clientIdx, seq.numLoop, req->_commandName.c_str(), 
				resp->cSeq, resultString);

//		_hammer.OnSessionEvent(ConsoleWriter::FAILED, ConsoleWriter::RESP);

		/* this command can't be skipped, mark the session as failed */
		if(!_hammer.skipCommand(req->_commandName)) {
			_hammer.OnSessionEvent(ConsoleWriter::FAILED, ConsoleWriter::SESS, _seqIdx);
			return;
		}
	}

	ZQ::common::Action::Context ctx;
	ctx.metaData = resp->headers;
	ctx.metaData[SEQ_IDX] = ScriptParser::to_string(_seqIdx);
	_hammer.triggerEvent(Hammer::EVT_RESP, ctx.metaData);
}
	
void HammerSession::OnResponse_TEARDOWN(ZQ::common::RTSPClient& rtspClient, 
							  ZQ::common::RTSPRequest::Ptr& req, 
							  ZQ::common::RTSPMessage::Ptr& resp, 
							  uint resultCode, const char* resultString) {

  	_hammer.removeWatch(_seqIdx);
	Hammer::SessSeq& seq = _hammer.getSessSeq(_seqIdx);

	_log(ZQ::common::Log::L_DEBUG, CLOGFMT(HammerSession, 
				"[%d-%d-%d] OnResponse_TEARDOWN(%d) return [%d,%s]"), 
				_seqIdx, seq.clientIdx, seq.numLoop, resp->cSeq, resultCode, resultString);

	_hammer.countResponse("TEARDOWN", resultCode);
	if(resultCode == ZQ::common::RTSPSink::rcOK) {
		_hammer.OnSessionEvent(ConsoleWriter::SUCCEEDED, ConsoleWriter::RESP);
	}
	else {
		_log(ZQ::common::Log::L_ERROR, CLOGFMT(HammerSession, 
				"[%d-%d-%d] [%s(%d)] failed [%s]"), 
				_seqIdx, seq.clientIdx, seq.numLoop, req->_commandName.c_str(), 
				resp->cSeq, resultString);

//		_hammer.OnSessionEvent(ConsoleWriter::FAILED, ConsoleWriter::RESP);
		
		/* this command can't be skipped, mark the session as failed */
		if(!_hammer.skipCommand(req->_commandName)) {
			_hammer.OnSessionEvent(ConsoleWriter::FAILED, ConsoleWriter::SESS, _seqIdx);
			return;
		}
	}

	ZQ::common::Action::Context ctx;
	ctx.metaData = resp->headers;
	ctx.metaData[SEQ_IDX] = ScriptParser::to_string(_seqIdx);
	_hammer.triggerEvent(Hammer::EVT_RESP, ctx.metaData);
}

void HammerSession::OnRequestError(ZQ::common::RTSPClient& rtspClient, 
							ZQ::common::RTSPRequest::Ptr& req, 
							ZQ::common::RTSPSink::RequestError errCode, 
							const char* errDesc) {

  	_hammer.removeWatch(_seqIdx);
	Hammer::SessSeq& seq = _hammer.getSessSeq(_seqIdx);

	_log(ZQ::common::Log::L_ERROR, CLOGFMT(HammerSession, 
				"[%d-%d-%d] [%s(%d)] failed [%s]"), 
				_seqIdx, seq.clientIdx, seq.numLoop, req->_commandName.c_str(), 
				req->cSeq, ZQ::common::RTSPSink::requestErrToStr(errCode));

	_hammer.OnSessionEvent(ConsoleWriter::FAILED, ConsoleWriter::REQ);
	
	if(_hammer.skipCommand(req->_commandName)) {
		ZQ::common::Action::Context ctx;
		ctx.metaData[SEQ_IDX] = ScriptParser::to_string(_seqIdx);
		_hammer.triggerEvent(Hammer::EVT_RESP, ctx.metaData);
	}
	else {
		_hammer.OnSessionEvent(ConsoleWriter::FAILED, ConsoleWriter::SESS, _seqIdx);
	}
}

// vim: ts=4 sw=4 nu bg=dark

