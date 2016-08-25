#include "aaa.h"
#include <iostream>
using namespace std;


Serv::Serv()
:mbQuit(false)
{}


Serv::~Serv()
{}


bool Serv::startService()
{
//	return start();
	mThreadPool = new ThreadPool(10);
	return ZQ::common::NativeThread::start();
}

int Serv::run()
{
	uint64  defaultInterval = 200;
	uint32  waitInterval;
//	do
	{
//		while (1)
	}
	cout<<"this is run"<<endl;
	return 0;
}

///////////////////////////////////
/////ThreadRequest
ThreadRequest::ThreadRequest(ThreadPool& pool)
	:mPool(pool)
{
}

ThreadRequest::~ThreadRequest()
{
}

void ThreadRequest::start()
{
	mPool.postRequest(this);
}

SlaveThread::SlaveThread(ThreadPool& pool)
	:mPool(pool),
	mRequest(NULL),
	mbQuit(false)
{

}

SlaveThread::~SlaveThread()
{
}

void SlaveThread::stop()
{
	mbQuit = true;
	mSem.post();
	waitHandle(-1);
}

int SlaveThread::run()
{
	while (!mbQuit)
	{
		mSem.wait();
		do
		{
			if (mbQuit) break;
			if (!mRequest) continue;
			{
				if (!mRequest->init())
				{
					mRequest->final(0,true);
				}
				else
				{
					int retCode = mRequest->run();
					mRequest->final(retCode,false);
				}
			}
			mRequest = NULL;
			mRequest = mPool.getRequest(this);
		}while (mRequest != NULL);
	}
	return 0;
}

void SlaveThread::comesNewRequest(ThreadRequest* req)
{
	mRequest = req;
	if (req == NULL)
	{
		mbQuit = true;
	}
	mSem.post();
}
////////////////////////////////////
//////ThreadPool
ThreadPool::ThreadPool(size_t size)
	:ZQ::common::NativeThreadPool(1),
	mbQuit(false)
{
	if (size < 3) size = 3;
	for (int i = 0;i< (int)size; i++)
	{
		SlaveThread* t = new SlaveThread(*this);
		mAllThreads.push_back(t);
		mIdleThreads.push_back(t);
		t->start();
	}
}

ThreadPool::~ThreadPool()
{
	stop();
}

void ThreadPool::stop()
{
	ZQ::common::MutexGuard gd(mLocker);
	mbQuit = true;
	std::vector<SlaveThread*>::iterator it = mAllThreads.begin();
	for (;it != mAllThreads.end();it++)
	{
		SlaveThread* t = *it;
		if (!t) continue;
		t->stop();
		delete t;
	}
	mAllThreads.clear();
	mIdleThreads.clear();
}

size_t ThreadPool::size() const
{
	ZQ::common::MutexGuard gd(mLocker);
	return mAllThreads.size();
}

size_t ThreadPool::pendingRequestSize() const
{
	ZQ::common::MutexGuard gd(mLocker);
	return mRequests.size();
}

size_t ThreadPool::activeCount() const
{
	ZQ::common::MutexGuard gd(mLocker);
	return mAllThreads.size() - mIdleThreads.size();
}

ThreadRequest* ThreadPool::getRequest(SlaveThread* t)
{
	ThreadRequest* r = NULL;
	{
		ZQ::common::MutexGuard gd(mLocker);
		if (mRequests.size() > 0)
		{
			r = mRequests.front();
			mRequests.pop_front();
		}
		else
		{
			mIdleThreads.push_back(t);
		}
	}
	return r;
}

void ThreadPool::postRequest(ThreadRequest* req)
{
	ZQ::common::MutexGuard gd(mLocker);
	if (mbQuit) return ;
	mRequests.push_back(req);
	ThreadRequest* r = mRequests.front();
	if (mIdleThreads.size() > 0)
	{
		SlaveThread* t = mIdleThreads.front();
		mIdleThreads.pop_front();
		mRequests.pop_front();
		t->comesNewRequest(r);
	}

}

TaskRunner::TaskRunner(ThreadPool& pool)
	:ThreadRequest(pool)
{
}

TaskRunner::~TaskRunner()
{
}

int TaskRunner::run()
{
	return 0;
}

void TaskRunner::final(int retcode, bool bCancelled)
{
	delete this;
}





