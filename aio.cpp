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
		for (int i =0; i<mBufferCount;i++)
		{
			Buffer* buf = new Buffer(&addr[i*bufsize],bufsize,i+1);
			modifyReq(buf,i);
			//			addBuffer(buf);
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
	//	size_t len = strlen(bufstr[2*i]);
	//	strcpy(buf->mBuf,bufstr[2*i]);
	//	strcpy(buf->mBuf+len,bufstr[2*i+1]);
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
	cout<<mList.size()<<endl;
	BufferList bufs;
	bufs.swap(mList);
	vector<struct iocb>iocbArray;
	vector<struct iocb*>iocbs;
	iocbArray.reserve(bufs.size());
	iocbs.reserve(bufs.size());
	iocbArray.clear();
	iocbs.clear();
	BufferList::iterator it = bufs.begin();
	int fd = open("TianShanBuild.sln",O_RDONLY);
	size_t pos = 0;
	for (;it != bufs.end();++it)
	{
		struct iocb* cb = &iocbArray[pos];
		io_prep_pread( cb, fd, (it->mBuf)->mBuf, bufsize-1, (bufsize-1)*pos );
		cb->data = (it->mBuf)->mBuf;
		iocbs[pos] = cb;
		pos++;
	}
	int rc = io_submit(mIoCtx,bufs.size(), &iocbs[0]);
	if (rc != 1)
	{
		cout<<"msg: "<<strerror(errno)<<endl;
	}
//	struct io_event events[1024];
//	rc = io_getevents(mIoCtx,1,1024,events,NULL);
//	printf("finish %d io_events\n",rc);
////	cout<<reinterpret_cast<char*>(events[0].data)<<endl;
//	for (int i = 0;i<rc;i++)
//	{
//		printf("this is [%d] block, size[%d]\n",i+1, strlen(reinterpret_cast<char*>(events[i].data)));
//		cout<<reinterpret_cast<char*>(events[i].data)<<endl;
//	}
}

void Center::aioreap()
{
	struct timespec ts;
	ts.tv_sec = 1;
	ts.tv_nsec = 0;
	const size_t MAX_EVENT_COUNT = 1204;
	struct io_event events[ MAX_EVENT_COUNT ];
	int rc = io_getevents( mIoCtx, 1, MAX_EVENT_COUNT, events, &ts );
	printf("finish %d io_events\n",rc);
	for(int i = 0;i<rc;i++)
	{
		 printf("this is block [%d], size[%d]\n",i+1, strlen(reinterpret_cast<char*>(events[i].data)));
		 cout<<reinterpret_cast<char*>(events[i].data)<<endl;
	}

}
