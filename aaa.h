#ifndef __aaa_h__
#define __aaa_h__
#include "NativeThreadPool.h"

class ThreadPool;
class Serv : public ZQ::common::NativeThread
{
	public:
		Serv();
		virtual ~Serv();
		bool    startService();
		virtual int     run();
	private:
		ZQ::common::NativeThreadPool*  mThreadPool;
		bool   mbQuit;
};
class ThreadRequest
{
	public:
		ThreadRequest(ThreadPool& pool);
		virtual ~ThreadRequest();
		virtual bool    init(){return true;}
		virtual int     run() = 0;
		virtual void    final(int retcode = 0, bool bCancelled = false){};
		void            start();

	private:
		ThreadPool&   mPool;
};

class SlaveThread : public ZQ::common::NativeThread
{
	public:
		SlaveThread(ThreadPool& pool);
		virtual ~SlaveThread();
	public:
		void  comesNewRequest(ThreadRequest* req = NULL);
		int   run();
		void  stop();
	private:
		ThreadPool&            mPool;
		ZQ::common::Semaphore  mSem;
		ThreadRequest*         mRequest;
		bool                   mbQuit;
};

class ThreadPool : public ZQ::common::NativeThreadPool
{
	public:
		ThreadPool(size_t size = 10);
		virtual     ~ThreadPool();
		size_t      size() const;
		size_t      activeCount()const;
		void        stop();

	protected:
		friend class SlaveThread;
		friend class ThreadRequest;
		void              postRequest(ThreadRequest* req);
		size_t            pendingRequestSize()const;
		ThreadRequest*    getRequest(SlaveThread* t);
	private:
		bool                         mbQuit;
		ZQ::common::Mutex            mLocker;
		std::vector<SlaveThread*>    mAllThreads;
		std::list<SlaveThread*>      mIdleThreads;
		std::list<ThreadRequest*>    mRequests;

};

class TaskRunner : public ThreadRequest
{
	public:
		TaskRunner(ThreadPool& pool);
		virtual ~TaskRunner();
	protected:
		int run();
		void final(int retcode = 0, bool bCancelled = false); 

};
#endif
