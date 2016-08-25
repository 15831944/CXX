#include <aio.h>
#include <string.h>
#include <config.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
using namespace std;
Buffer::Buffer(char*addr, size_t size, size_t id)
	:mBuf(addr),mBufSize(size),mId(id)
{
	mFd = 0;
	mOrigOffset = 0;
	mNext = NULL;
	mBuf = addr;
}

Buffer::~Buffer()
{
}
	
BufferUser::BufferUser()
{

}

BufferUser::BufferUser(Buffer* buf)
	:mBuf(buf),mOffset(0)
{

}

BufferUser::BufferUser(const BufferUser& b)
{
	mBuf = NULL;
	if (mBuf != b.mBuf){
		mBuf = b.mBuf;

	}
}

BufferUser::~BufferUser()
{
	//to delete buffer
}

Center::Center(size_t bufcount, size_t bufsize):mBufferCount(bufcount),mBufferSize(bufsize)
{
	mHead = new Buffer(new char[100],0,0);
	mTail = mHead;
	memset( &mIoCtx, 0, sizeof(mIoCtx) );
	int rc = io_setup( 6,&mIoCtx);
}

int Center::start()
{
	char* addr = (char*)memalign( bufsize,bufsize*mBufferCount);
	if (addr != NULL){
	//cout<<"memalign len: "<<strlen(addr)<<endl;
	for (int i =0; i<mBufferCount;i++)
	{
		Buffer* buf = new Buffer(&addr[i*bufsize],bufsize,i+1);
		modifyReq(buf,i);
		addBuffer(buf);
	}
	}
}

void Center::stop()
{
	io_destroy(mIoCtx);
}

void Center::addBuffer(Buffer* buf)
{
	if (buf)
	{
		//insert into tail
		mTail->mNext = buf;
		mTail = buf;
		buf->mNext = NULL;
	}
}

void Center::modifyReq(Buffer* buf, int i)
{
	size_t len = strlen(bufstr[2*i]);
	strcpy(buf->mBuf,bufstr[2*i]);
	strcpy(buf->mBuf+len,bufstr[2*i+1]);
	buf->reqId = i+1;
	BufferUser bu(buf);
	mList.push_back(bu);
}
void Center::testBuffer()
{
	Buffer* p = mHead->mNext;
	while (p)
	{
		cout<<"len: "<<strlen(p->mBuf)<<endl;
		cout<<"str: "<<p->mBuf<<endl;
		p = p->mNext;
	}
	cout<<mList.size()<<endl;
}

void Center::aiosubmit()
{
	BufferList bufs;
	bufs.swap(mList);
	vector<struct iocb>iocbArray;
	vector<struct iocb*>iocbs;
	iocbArray.reserve(bufs.size());
	iocbs.reserve(bufs.size());
	iocbArray.clear();
	iocbs.clear();
	BufferList::iterator it = bufs.begin();
	size_t pos = 0;
	int fd = open("file",O_RDONLY);
	cout<<"fd: "<<fd<<endl;
	struct iocb* cb = &iocbArray[pos];
	io_prep_pread( cb, fd, it->mBuf, bufsize, 0 );
	cb->data = it->mBuf;
	iocbs[pos] = cb;
	int rc = io_submit(mIoCtx, 1, &iocbs[0]);
	if (rc != 1)
	{
		cout<<"msg: "<<strerror(errno)<<endl;
	}
//	cb->data = reinterpret_cast<void*>(buf.getInner());
//	iocbs[pos] = cb;
//	pos ++;
//	for (;it != bufs.end(); ++ it)
//	{
//		BufferUser& buf = *it;
//		struct iocb* cb = &iocbArray[pos];
//		io_prep_pread(cb, buf);
//	}
}

void Center::aioreap()
{

}
