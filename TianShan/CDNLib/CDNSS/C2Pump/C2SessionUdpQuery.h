#ifndef _tianshan_cdnss_c2streamer_c2sessionudpquery_header_file_h__
#define _tianshan_cdnss_c2streamer_c2sessionudpquery_header_file_h__

#include <boost/thread.hpp>
#include <LRUMap.h>
#include <Locks.h>
#include "../IdxFileParserEnvironment.h"
#include "../IndexFileParser.h"
#include "AioFile.h"
#include <libasync/eventloop.h>

namespace C2Streamer
{
class C2StreamerEnv;
class C2Service;

class IndexDataReader : public LibAsync::AsyncWork {
public:
	typedef ZQ::common::Pointer<IndexDataReader>	Ptr;

	IndexDataReader( C2StreamerEnv& env, C2Service& svc );
	virtual ~IndexDataReader();

	int32           parse( const std::string& assetName, int readertype );

	bool            findSubfileInfo( INOUT float& scale, OUT std::string& subFileExt, OUT int64& playTime );

	int64           findDataOffset( INOUT int64& timeOffset, float scale);

	void            rewriteRecords(const IdxRecPtr& ptr);

	int64 			getDataBitrate() const;

	void signal(){
		boost::mutex::scoped_lock gd(mboostLocker);
		mbParsed = true;
		mCond.notify_all();
	}
	void wait(){
		boost::mutex::scoped_lock gd(mboostLocker);
		if (!mbParsed){
			mCond.wait(gd);
		}
	}
	bool IsParsed(){
		boost::mutex::scoped_lock gd(mboostLocker);
		return mbParsed;
	}
	void SetUnParsed(){
		boost::mutex::scoped_lock gd(mboostLocker);
		mbParsed = false;
	}
	void postAsyncWork() {
		queueWork();
	}


private:

	int32           parseIndex( );
	virtual void 	onAsyncWork();
	void 			readNext();

private:
	C2StreamerEnv&              mEnv;
	C2Service&                  mSvc;
	IdxRecPtr                   mIdxRecPtr;
	ZQ::IdxParser::IdxParserEnv mIdxParserEnv;
	ZQ::common::Semaphore       mSema;
	int64                       mOffset;
	size_t 						mOffsetInBuffer;
	char*                       mIndexData;
	boost::condition_variable   mCond;
	boost::mutex                mboostLocker;
	bool                        mbParsed;
	bool						mbFirstTry;
	LibAsync::EventLoop*		mLoop;
	AioFile*					mAioFile;
	int32 						mLastErrorCode;
	std::string					mAssetName;
	BufferUser 					mBu;
};

typedef ZQ::common::Pointer<IndexDataReader> IdxReaderPtr;

class C2UdpInfoQuery : public ZQ::common::SharedObject
{
public:
	typedef ZQ::common::Pointer<C2UdpInfoQuery> Ptr;
	C2UdpInfoQuery(C2StreamerEnv& env, C2Service& svc);
	virtual ~C2UdpInfoQuery();
	int32   UdpInfoQuery(const SessionUdpControlRequestParamPtr request, SessionUdpControlResponseParamPtr response);
	IdxReaderPtr	findReaderByLRUMap(const std::string& assetname, bool& bNew);
	IdxReaderPtr	getIdxReaderByAssetName(const std::string& assetname, bool& bNew);
	IdxReaderPtr	parse(const std::string& assetName, int32 readerType);
private:
	C2Service&       mSvc;
	C2StreamerEnv&   mEnv;
	ZQ::common::Mutex  mLocker;
	IdxReaderPtr       mIdxReader;
	ZQ::common::LRUMap<std::string, IdxReaderPtr> IdxReaderMap;
};

}
#endif

