#ifndef __AIO_H__
#define __AIO_H__
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <list>
#include <vector>
#include <libaio.h>
class Center;
class Buffer
{
	public:
		Buffer(char*addr, size_t size, size_t id);
//		Buffer(char* addr,size_t size,size_t id):buffsize(size),reqId(id),fd(filefd)
//	{
//		ptr = &addr[id*1024];
//		strcpy(ptr,p);
//		//printf("idx: %d %s\n",idx,ptr);
//		idx++;
//	}
		~Buffer();
	private:
		friend class Center;
		char*     mBuf;
		size_t    mBufSize;
		int       reqId;
		int       mFileSize;
		int       mOrigOffset;
		int       mFd;
		size_t    mId;
		Buffer*   mNext;
};

class BufferUser
{
	public:
		BufferUser();
		BufferUser(Buffer* buf);
		BufferUser(const BufferUser&);
		BufferUser& operator=(const BufferUser&);
		~BufferUser();
		bool valid()const
		{return mBuf!= NULL;}
	private:
		friend class Center;
		Buffer* mBuf;
		size_t mOffset;
};

class Center
{
	public:
		Center(size_t bufcount,size_t bufsize);
		int start();
		void stop();
		void addBuffer(Buffer*);
		void modifyReq(Buffer* buf,int i);
		void testBuffer();
		void aiosubmit();
		void aioreap();
	private:
		typedef std::list<BufferUser> BufferList;
		BufferList   mList;
		bool     mbRunning;
		Buffer*  mHead;   
		Buffer*  mTail;
		size_t   mBufferCount;
		size_t   mBufferSize;
		io_context_t        mIoCtx;
};

#endif
