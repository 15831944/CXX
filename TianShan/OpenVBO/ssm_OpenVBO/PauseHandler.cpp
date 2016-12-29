// File Name : PauseHandler.cpp

#include "PauseHandler.h"

#include "SelectionResourceManager.h"

#include "Environment.h"

#include "RtspRelevant.h"

#include "TianShanDefines.h"

#include <TianShanIceHelper.h>

#define HANDLERLOGEX _pHandler->_fileLog
#define HANDLERLOGFMTEX(_X, _T) CLOGFMT(_X, "Sess(%s)Seq(%s)Req(%p)Mtd(%s) " _T),_pHandler->_session.c_str(), _pHandler->_sequence.c_str(), _pHandler->_request, _pHandler->_method.c_str()

namespace EventISVODI5
{
class PauseHandlerAsync : public TianShanIce::Streamer::AMI_Stream_pauseEx
{
public:
	PauseHandlerAsync(PauseHandler::Ptr pHandler)
	{
		_pHandler = pHandler;
		assert( _pHandler != NULL );
		_pHandler->_request->addRef();
		_pHandler->_request->setContext(CLIENT_REQUEST_DISABLE_AUTO_DELETE, "1");
	}

	~PauseHandlerAsync()
	{
		_pHandler->_request->release();
	}

	virtual void ice_response(const ::TianShanIce::Streamer::StreamInfo& infoRet) 
	{
		char localBuffer[1024];
		HANDLERLOGEX(ZQ::common::Log::L_INFO, HANDLERLOGFMTEX(PauseHandlerAsync, "performed pauseEx() on stream[%s] successfully: [%s]"), (_pHandler->_streamId).c_str(), ZQTianShan::Util::dumpStreamInfo(infoRet, localBuffer, sizeof(localBuffer) - 1));

		//get result information
		std::string strTimeOffset;
		std::string	strCurrentSpeed;
		::TianShanIce::Properties::const_iterator itRet = infoRet.props.find("CURRENTPOS");
		if(itRet != infoRet.props.end())
		{
			int iOffset = atoi( itRet->second.c_str() );
			char szTemp[256];
			snprintf(szTemp,sizeof(szTemp)-1,"%d.%d",iOffset/1000,iOffset%1000);
			strTimeOffset = "npt=" ;
			strTimeOffset = strTimeOffset + szTemp ;
			strTimeOffset = strTimeOffset + "-";
		}
		else
		{
			strTimeOffset = "npt=0-";
		}

		itRet = infoRet.props.find("TOTALPOS");
		if(itRet != infoRet.props.end())
		{
			if(itRet->second.length() > 0)
			{
				int iOffset = atoi(itRet->second.c_str());
				if(iOffset > 0)
				{
					char szTemp[256];
					snprintf(szTemp,sizeof(szTemp)-1,"%d.%d",iOffset/1000,iOffset%1000);
					strTimeOffset = strTimeOffset + szTemp;
				}
			}
		}


		itRet = infoRet.props.find("SPEED");
		if (itRet != infoRet.props.end())
		{
			strCurrentSpeed = itRet->second;
		}
		else
		{
			strCurrentSpeed = "0.0";
		}

		IServerResponse* pResponse = _pHandler->_response;
		pResponse->setHeader(HeaderScale, strCurrentSpeed.c_str());
		pResponse->setHeader(HeaderRange, strTimeOffset.c_str());
		_pHandler->_statusCode = 200;
		_pHandler->composeResponse();

		Ice::Long cur = ZQTianShan::now();
		Ice::Long timeUsed = cur - _pHandler->_startTime;
		HANDLERLOGEX(ZQ::common::Log::L_INFO,CLOGFMT(PauseHandlerAsync, "Sess(%s)Seq(%s)[success]process request, used [%lld]ms"), _pHandler->_session.c_str(), _pHandler->_sequence.c_str(), timeUsed);
	}
	virtual void ice_exception(const ::Ice::Exception& ex) 
	{
		try
		{
			ex.ice_throw();
		}
		catch(const Ice::TimeoutException& ex)
		{
			// add penalty
			_pHandler->addPenalty();
			_pHandler->_statusCode = 503;
			snprintf(_pHandler->_szBuf, sizeof(_pHandler->_szBuf) - 1, "caught [%s] during pauseEx on stream[%s]", ex.ice_name().c_str(), (_pHandler->_streamId).c_str());
			HANDLERLOGEX(ZQ::common::Log::L_WARNING, HANDLERLOGFMTEX(PlayResponseAsync, "%s"), _pHandler->_szBuf);
		}
		catch(const Ice::ConnectionRefusedException& ex)
		{
			// add penalty
			_pHandler->addPenalty();

			_pHandler->_statusCode = 503;
			snprintf(_pHandler->_szBuf, sizeof(_pHandler->_szBuf) - 1, "caught [%s] during pauseEx on stream[%s]", ex.ice_name().c_str(), (_pHandler->_streamId).c_str());
			HANDLERLOGEX(ZQ::common::Log::L_WARNING, HANDLERLOGFMTEX(PlayResponseAsync, "%s"), _pHandler->_szBuf);
		}
		catch( const TianShanIce::InvalidStateOfArt& bEx )
		{
			_pHandler->_statusCode = 405;//bugs:18671
			snprintf(_pHandler->_szBuf, sizeof(_pHandler->_szBuf) - 1, "caught exception[%s]:%d %s during pauseEx() on stream[%s]", bEx.ice_name().c_str(), bEx.errorCode, bEx.message.c_str(), (_pHandler->_streamId).c_str());
			HANDLERLOGEX(ZQ::common::Log::L_WARNING, HANDLERLOGFMTEX(PlayResponseAsync, "%s"), _pHandler->_szBuf);
		}
		catch( const TianShanIce::BaseException& bEx)
		{
			_pHandler->_statusCode = 500;
			snprintf(_pHandler->_szBuf, sizeof(_pHandler->_szBuf) - 1, "caught exception[%s]:%d %s during pauseEx() on stream[%s]", bEx.ice_name().c_str(), bEx.errorCode, bEx.message.c_str(), (_pHandler->_streamId).c_str());
			HANDLERLOGEX(ZQ::common::Log::L_WARNING, HANDLERLOGFMTEX(PlayResponseAsync, "%s"), _pHandler->_szBuf);

		}
		catch( const Ice::Exception& ex )
		{
			_pHandler->_statusCode = 500;
			snprintf(_pHandler->_szBuf, sizeof(_pHandler->_szBuf) - 1, "caught [%s] during pauseEx() on stream[%s]", ex.ice_name().c_str(), (_pHandler->_streamId).c_str());
			HANDLERLOGEX(ZQ::common::Log::L_WARNING, HANDLERLOGFMTEX(PlayResponseAsync, "%s"), _pHandler->_szBuf);
		}		

		Ice::Long cur = ZQTianShan::now();
		Ice::Long timeUsed = cur - _pHandler->_startTime;
		_pHandler->composeResponse();
		HANDLERLOGEX(ZQ::common::Log::L_INFO, CLOGFMT(PauseHandlerAsync, "Sess(%s)Seq(%s)[failed]process request, used [%lld]ms"),  _pHandler->_session.c_str(), _pHandler->_sequence.c_str(), timeUsed);
	}

private:
	PauseHandler::Ptr _pHandler;

};

PauseHandler::PauseHandler(ZQ::common::Log& fileLog, Environment& env, 
	IStreamSmithSite* pSite, IClientRequestWriter* pReq)
:RequestHandler(fileLog, env, pSite, pReq)
{
	_method = "PAUSE";
}

PauseHandler::~PauseHandler()
{

}

RequestProcessResult PauseHandler::doContentHandler()
{
	HANDLERLOG(ZQ::common::Log::L_INFO, HANDLERLOGFMT(PauseHandler, "start processing"));
	if (!renewSession())
	{
		return RequestError;
	}

	if (!findPlaylist())
	{
		return RequestError;
	}

	// update STB Connection ID
	::std::string strSTBConnectionID = getRequestHeader("SYS#ConnID");
	if (!updateSessionMetaData(SESSION_META_DATA_STB_CONNECTION_ID, strSTBConnectionID))
	{
		return RequestError;
	}

	TianShanIce::StrValues expectValues;
	expectValues.push_back("ITEM_CURRENTPOS");
	expectValues.push_back("CURRENTPOS");
	expectValues.push_back("TOTALPOS");
	expectValues.push_back("SPEED");
	expectValues.push_back("STATE");
	expectValues.push_back("USERCTRLNUM");

	try
	{
		_playlistPrx->pauseEx_async( (new PauseHandlerAsync(this)), expectValues);		
		HANDLERLOG(ZQ::common::Log::L_DEBUG, HANDLERLOGFMT(PauseHandler, "calling pauseEx() on stream: [%s]"), _streamId.c_str());

	}
	catch(const ::TianShanIce::BaseException& ex)
	{
		_statusCode = 500;
		snprintf(_szBuf, sizeof(_szBuf) - 1,"pauseEx() on stream[%s] caught [%s]:[%s]", _streamId.c_str(), ex.ice_name().c_str(), ex.message.c_str());
		HANDLERLOG(ZQ::common::Log::L_ERROR, HANDLERLOGFMT(PauseHandler, "%s"), _szBuf);
		//HANDLEREVENTLOG(ZQ::common::Log::L_ERROR, HANDLERLOGFMT(PauseHandler, "%s"), _szBuf);
		return RequestError;
	}
	catch(const ::Ice::Exception& ex)
	{
		_statusCode = 500;
		snprintf(_szBuf, sizeof(_szBuf) - 1,"pauseEx() on stream[%s] caught [%s]", _streamId.c_str(), ex.ice_name().c_str());
		HANDLERLOG(ZQ::common::Log::L_ERROR, HANDLERLOGFMT(PauseHandler, "%s"), _szBuf);
	    //HANDLEREVENTLOG(ZQ::common::Log::L_ERROR, HANDLERLOGFMT(PauseHandler, "%s"), _szBuf);
		return RequestError;
	}

	_returnType = RETURN_ASYNC;
	return RequestProcessed;
}

} // end EventISVODI5
