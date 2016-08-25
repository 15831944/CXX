#include <iostream>
#include <string>
//#include <aaa.h>
#include <vector>
#include <libaio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <aio.h>
#include <errno.h>
#include <algorithm>
//#include <config.h>
using namespace std;
//static void wr_done(io_context_t ctx,struct iocb* iocb, long res, long res2)
//{
//	if (res2 != 0 ){printf("aio write error \n");}
//	if (res != iocb->u.c.nbytes)
//	{
//		printf("write missed bytes expect %d got %d \n", iocb->u.c.nbytes, res);
//		exit(1);
//	}
//	free(iocb->u.c.buf);
//	free(iocb);
//}
//static void rd_done(io_context_t ctx, struct iocb* iocb, long res, long res2)
//{
//	printf("enter rd_done, res: %d res2: %d\n",res, res2);
//	int iosize = iocb->u.c.nbytes;
//	char* buf = (char*)iocb->u.c.buf;
//	//	printf("buf length %d\n",strlen(buf));
//	off_t offset = iocb->u.c.offset;
//	int tmp;
//	char* wrbuff = NULL;
//	if (res2 != 0 ){printf("aio read: %d\n",res2);}
//	if (res != iosize){printf("read missing bytes expect %d got %d",iocb->u.c.nbytes,res);exit(1);}
//	tmp = posix_memalign((void**)&wrbuff,getpagesize(),AIO_BLKSIZE);
//	if (tmp < 0){printf("posix_memalign failed\n");exit(1);}
//	snprintf(wrbuff,iosize+1,"%s",buf);
//	printf("wrbuff - len = %d:%s n", strlen(wrbuff), wrbuff);
//	printf("wrbuff_len = %d n", strlen(wrbuff));
//	free(buf);
//	io_prep_pwrite(iocb,odsfd,wrbuff,iosize,offset);
//	io_set_callback(iocb,wr_done);
//	int ret = io_submit(ctx,1,&iocb);
//}
//char* addr = (char*)memalign(bufsize,bufsize*5);
int main()
{
	//	Center cen(5,1024*2);
	//	cen.start();
	//	cen.aiosubmit();


	//	cen.testBuffer();
	//	std::vector<struct iocb> iocbArray;
	//	iocbArray.reserve(32);
	//	std::vector<struct iocb*> iocbs;
	//	iocbs.reserve(32);
		int srcfd,dstfd,rc;
		io_context_t ctx;
		memset(&ctx,0,sizeof(ctx));
		const char* filename = "hello.txt";
		struct io_event eve;
		struct timespec timeout;
		rc = io_setup(10,&ctx);
		if (rc!=0){
			cout<<"io_setup: "<<strerror(errno)<<endl;
			return -1;
		}
		srcfd = ::open(filename,O_RDONLY,0777);
		if (srcfd<0) {perror("open error");io_destroy(ctx);}
		size_t nread = -1;
		size_t id = 0;
		char* addr = (char*)memalign( 1024, 1024*5 );
		char* buff = new char[1024*10];
		std::vector<struct iocb>iocbArray;
		iocbArray.reserve(32);
		std::vector<struct iocb*>iocbs;
		iocbs.reserve(32);
		struct iocb* cb = &iocbArray[0];
		io_prep_pread(cb,srcfd,buff,1024*5,0);
		cb->data = buff;//reinterpret_cast<void*>((*it)->ptr); ??????
		iocbs[0] = cb;
	
		rc = io_submit(ctx, 1, &iocbs[0]); 
		if (rc != 1)
		{
			cout<<"msg: "<<strerror(errno)<<endl;
		}
		struct io_event events[ 1024];
		rc = io_getevents( ctx, 1,1024, events, NULL );
		cout<<"finish io_getevents"<<endl;
		for  (int i = 0;i<rc;i++)
		{

		//	char* ptr = reinterpret_cast<char*>(events[i].data);
			cout<<reinterpret_cast<char*>(events[i].data)<<endl;
		}
	//first step
	//while (nread)
	//{
	//	memset(buf,0,256);
	//	nread =  ::read(srcfd,buf,blocklen);
	//	if (-1 == nread){
	//		close(srcfd);
	//		printf("read file error\n");
	//		return -1;
	//	}
	//	else if (nread > 0){
	//		buf[nread] = '\0';
	//	//		Buffer* pBuf = new Buffer(nread,id,srcfd,buf);
	//	//		if (pBuf)
	//	//		{
	//	//			vecBuf.push_back(pBuf);
	//	//			//printf("%d: %s",nread,buf);
	//	//		}
	//		id ++;
	//		if (id>=5){break;} //max 5 buffer block
	//	}
	//}




	//	//second step
	////	int pos = 0;
	////	std::vector<struct iocb>iocbArray;
	////	iocbArray.reserve(32);
	////	std::vector<struct iocb*>iocbs;
	////	iocbs.reserve(32);
	////	std::vector<Buffer*>::iterator it = vecBuf.begin();
	////	for (;it!=vecBuf.end();++it)
	////	{
	////		struct iocb* cb = &iocbArray[pos];
	////		io_prep_pread(cb,(*it)->fd,(*it)->ptr,(*it)->buffsize,0);
	////		cb->data = (*it)->ptr;//reinterpret_cast<void*>((*it)->ptr);
	////		pos ++;
	////		iocbs[pos] = cb;
	////		printf("%s",cb->data);
	////	}
	////		struct iocb io, *p = &io;
	////		char* content = "hello world";
	////	//	ret = posix_memalign((void**)&buff,getpagesize(),)
	////		//io_prep_pread(&io,srcfd,space,strlen(content),0);
	////	//	io_prep_pread(&io,(*it)->fd,(*it)->ptr,(*it)->buffsize,0);
	////		io.data = content;
	////	//	io.data = (*it)->ptr;
	////		dstfd = ::open("hello11.txt",O_CREAT|O_WRONLY,0777);
	////	int rc;
	////	if ((rc =io_submit(ctx,3,&iocbs[0])) <0)
	////	{
	////		printf("rc: %d %s\n",rc,strerror(rc));
	////	}
	////	//if ((rc =io_submit(ctx,1,&iocbs[0])) <0)
	////	//{
	////	//	printf("rc: %d %s\n",rc,strerror(rc));
	////	//}
	////	//read file block in loop
	////
	////	//step 3 reap
	////	struct timespec ts;
	////	ts.tv_sec = 1;
	////	ts.tv_nsec = 0;
	////	struct io_event events[1024];
	////	rc = io_getevents(ctx, 1,1024,events,NULL);
	////	printf("rc: %d\n",rc);
	////	for (size_t i = 0;i < rc ;i++)
	////	{
	////		char* buf = reinterpret_cast<char*>(events[i].data);
	////		printf("%s",buf);
	////	}



	///int length = sizeof("abcdefg");	
	///char* content = (char*)malloc(length);
	///io_context_t myctx;
	///int rc;
	///char* buff = NULL;
	///int offset = 0, num, i, tmp;
	///if ( (srcfd = open("hello.txt",O_RDWR)) <0)
	///{
	///	printf("open srcfile error\n");
	///	exit(1);
	///}
	///printf("srcfd = %d\n", srcfd);
	///lseek(srcfd,0,SEEK_SET);
	///write(srcfd,content,length);
	///if ( (odsfd = open("test2.txt",O_RDWR)) <0)
	///{
	///	close(srcfd);
	///	printf("open odsfile error\n");
	///	exit(1);
	///}
	///memset(&myctx, 0, sizeof(myctx));
	///io_setup(AIO_MAXIO, &myctx);
	///struct iocb* io = (struct iocb*)malloc(sizeof(struct iocb));
	///int iosize = AIO_BLKSIZE;
	///tmp = posix_memalign((void**)&buff,getpagesize(),AIO_BLKSIZE);	
	///if (tmp < 0){printf("posix_memalign error\n");exit(1);}
	///if (io == NULL) {printf("io out of memory\n");exit(1);}
	///io_prep_pread(io,srcfd,buff,iosize,offset);

	///io_set_callback(io,rd_done);
	///printf("START...\n");
	///rc = io_submit(myctx,1,&io);
	///if (rc < 0){printf("io_submit read error\n");}
	///printf("nsubmit %d read request \n", rc);
	///struct io_event events[AIO_MAXIO];
	///io_callback_t cb;
	///num = io_getevents(myctx,1,AIO_MAXIO,events,NULL);
	///printf("%d io_request completed \n",num);
	///for (i = 0;i<num;i++)
	///{
	///	cb = (io_callback_t)events[i].data;
	///	struct iocb* io = events[i].obj;
	///	printf("events[%d].data = %x,res = %d, res2 = %d\n",i,cb,events[i].res, events[i].res2);
	///	cb(myctx,io,events[i].res,events[i].res2);
	///}



	//int infd,outfd;
	//io_context_t ctx;
	//struct iocb io;
	//struct timespec timeout;
	//memset(&ctx, 0, sizeof(ctx));
	//if(io_setup(10,&ctx)!=0){printf("io_setup error\n");exit(1);}
	//infile = ::open("hello.txt",O_RDONLY);
	//vector<Buffer*>
////	io_context_t ctx;
////	int rc;
////	memset(&ctx,0,sizeof(ctx));
////	rc = io_setup(10,&ctx);
////	if (rc != 0){
////		cout<<"io_setup: "<<strerror(errno)<< rc<<endl;
////		return -1;
////	}

	return 0;
}
