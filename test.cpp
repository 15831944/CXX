#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <initializer_list>
//#include <tr1/unordered_map>
#include <stdio.h>
#include "test.h"
#include <signal.h>
#include <errno.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <fcntl.h>
#include <fstream>
#include <sys/socket.h>
#include <sstream>
#include <string.h>
#include <arpa/inet.h>
#include <list>
#include <memory>
#include <thread>
#include <map>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <functional>
//using namespace std::tr1;
using namespace std;
//struct my_struct_t
//{
//    pthread_mutex_t  mutex;
//    pthread_cond_t   cond;
//    int              val;
//};
//my_struct_t data = {
//    PTHREAD_MUTEX_INITIALIZER,
//    PTHREAD_COND_INITIALIZER,
//    0
//};
//int hibernation = 1;
//void* wait_thread(void*arg)
//{
//    int status ;
//    sleep(hibernation);
//    status = pthread_mutex_lock(&data.mutex);
//    data.val = 1;
//    status = pthread_cond_signal(&data.cond);
//    status = pthread_mutex_unlock(&data.mutex);
//    printf("wait_thread finish\n");
//    return NULL;
//}
pthread_cond_t g_cond;
pthread_mutex_t g_mutex;
int count = 0;
void* func(void* arg)
{
    pthread_mutex_lock(&g_mutex);
    pthread_cond_wait(&g_cond,&g_mutex);
    for (int i = 0;i<2;i++)
    {
        printf("thread func!\n");
    }
    sleep(1);
    pthread_mutex_unlock(&g_mutex);
    printf("func finish\n");
    return NULL;
}
void* increase(void* arg)
{
    sleep(1);
    while (1)
    {
        pthread_mutex_lock(&g_mutex);
       // count++;
       // if (count >0)
       // {
       //     printf("count=%d,change cond state\n", count);
       //     pthread_cond_signal(&g_cond);
       // }
       // pthread_mutex_unlock(&g_mutex);
       // if (count == 10)
       // {
       //     printf("count=10,increase over");
       //     return NULL;
       // }
        
    }
    return NULL;
}
void* decrease(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&g_mutex);
       // while(count<=0)
       // {
       //     printf("cout<=0,decrease is hanging!\n");
       //     pthread_cond_wait(&g_cond,&g_mutex);
       //    // sleep(1);
       //     printf("sleep!\n");
       // }
       // count --;
       // printf("decrease: %d\n", count);
       // pthread_mutex_unlock(&g_mutex);
       // if (count == 9)
       // {
       //     printf("count =9,decrease finish!\n");
       //     return NULL;
       // }
    }
    return NULL;
}
void hello()
{
    std::cout<<"hello concurrent world\n"<<endl;
}
void receivesignal(int sign)
{
    if (sign == SIGINT)
    {
        cout<<"receive sig sigint"<<endl;
//        exit(1);
    }
}
bool predCompare(const string& str);
#define MAX_EVENT_NUMBER 1024
static int pipefd[2];
int setnonblocking(int fd)
{
    int old_option = fcntl(fd,F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd,F_SETFL, new_option);
    return old_option;
}
void addfd(int epollfd, int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
    setnonblocking(fd);
}
void sig_handler(int sig)
{
    int save_errno = errno;
    int msg = sig;
    send(pipefd[1],(char*)&msg,1,0);
    errno = save_errno;
}
void addsig(int sig)
{
    struct sigaction sa;
    memset(&sa,0,sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags |= SA_RESTART;
    sigfillset(&sa.sa_mask);
    sigaction(sig,&sa,NULL);
}
void ouch(int sig)
{
   if (SIGINT == sig)
   {
       printf("receive sigint\n");
//       signal(SIGINT,SIG_DFL);
   }
}
    void process(shared_ptr<int>p)
    {
        //printf("in process count: %d\n",p.use_count());
        //shared_ptr<int>ptr(p);
        //printf("after double: %d\n",p.use_count());
        //ptr =make_shared<int>(); //shared_ptr<int>pp(new int (10));
        //printf("after pp:%d\n",p.use_count());
        int* ptr = p.get();
        shared_ptr<int>jjz(ptr);
    }
void shared_ptr_func()
{
    printf("shared_ptr_func called\n");
}
int add(int x, int y)
{
    return x+y;
}
class Divide
{
    public:
        int operator()(int x, int y)
        {
            return x / y;
        }
};
int mod(int x, int y)
{
    return x % y;
}
class Object
{
    public:
        void operator() ()
        {
            cout<<"delete test"<<endl;
        }
    private:

};
//void test(/*shared_ptr<int>ptr*/Object* p){cout<<"this is a test"<<endl;}
void test(Object*o){cout<<"this is a test"<<endl;}
#define NUM_THREADS 5
class Hello
{
    public:
        static void* say_hello(void* args)
        {
            int* i = (int*)args;
            if (i != NULL)
                cout<<"hello in: "<<*i<<endl;
            int status = 10 + *((int*)args);
          //  pthread_exit((void*)status);
        }
};
void signal_handler_func(int sig)
{
    if (sig == SIGINT)
    {
        printf("catch signal\n");
    }
}
int main(int argc, char*argv[])
{
//    int status;
//    pthread_t tid;
//    struct timespec timeout;
//    if (argc>1) hibernation = atoi(argv[1]);
//    status = pthread_create(&tid,NULL,wait_thread,NULL);
//    timeout.tv_sec = time(NULL)+2;timeout.tv_nsec = 0;
//    sleep(2);
//    status = pthread_mutex_lock(&data.mutex);
// //   while (data.val==0)
// //   {
//        status = pthread_cond_wait(&data.cond,&data.mutex);
//        printf("Invoke!\n");
//       // status = pthread_cond_timedwait(&data.cond,&data.mutex,&timeout);
//       // if (status == ETIMEDOUT)
//       // {
//       //     printf("Condition wait timed out\n");
//       //     break;
//       // }
//       // else
//       // {
//       //     printf("Invoke !\n");
//       // }
// //   }
//    if (data.val != 0)
//    {
//        printf("Condition was signaled.\n");
//    }
//    status = pthread_mutex_unlock(&data.mutex);
//    pthread_t tid;
//    pthread_cond_init(&g_cond,NULL);
//    pthread_mutex_init(&g_mutex,NULL);
//    int ret;
//    ret = pthread_create(&tid,NULL,func,NULL);
//    sleep(2);
//    pthread_mutex_lock(&g_mutex);
//    pthread_cond_signal(&g_cond);
//    pthread_mutex_unlock(&g_mutex);
//    pthread_join(tid,NULL);
//    pthread_cond_destroy(&g_cond);
//    pthread_mutex_destroy(&g_mutex);
 //   pthread_t tid1, tid2;
 //   int status = -1;
 //   pthread_mutex_init(&g_mutex,NULL);
 //   pthread_cond_init(&g_cond,NULL);
 //   status = pthread_create(&tid1,NULL,increase,NULL);if (status == -1){printf("pthread_create error!\n");}
 //   status = pthread_create(&tid2, NULL,decrease,NULL);if (status == -1){printf("pthread_create error!\n");}
 //   pthread_join(tid2,NULL);
 //   pthread_join(tid1,NULL);
 //   pthread_cond_destroy(&g_cond);
 //   pthread_mutex_destroy(&g_mutex);
//    std::thread t(hello);
//    t.join();
//    int sockfd = socket(AF_INET,SOCK_STREAM,0);
//    sockaddr_in servaddr;
//    socklen_t len = sizeof(servaddr);
//    bzero(&servaddr,sizeof(servaddr));
//    servaddr.sin_family = AF_INET;
//    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//    servaddr.sin_port = htons(12345);
//    bind(sockfd,(sockaddr*)&servaddr,sizeof(servaddr));
//    int ret = getsockname(sockfd,(sockaddr*)&servaddr,&len);
//    if (ret == 0) printf("get succ\n");
//    char* ptr = inet_ntoa(servaddr.sin_addr);
//    printf("%s\n",ptr);
//    char* ptr = "aaa";
//    printf("%d\n",sizeof(ptr));
//    uid_t uid = getuid();
//    printf("uid: %d\n",uid);
//    uid_t euid = geteuid();
//    printf("eudi: %d\n",euid);
//    printf("gid: %d\n",getgid());
//    printf("getegid: %d\n",getegid());
//    printf("Pid: %d\n",getpid());
//    printf("pgid: %d\n",getpgid(getpid()));
//    char buff[0];bzero(buff,0);
//    char* ptr = getcwd(buff,128);
//    printf("path: %s\n",ptr);
//      signal(SIGINT, ouch);
//      while (1)
//      {
//          printf("no signal\n");sleep(1);
//      }
//       struct sigaction act;
//       act.sa_handler = ouch;
//       sigemptyset(&act.sa_mask);
//       act.sa_flags = 0;
//       sigaction(SIGINT,&act,0);
////       while (1)
////       {
////           printf("hello world!\n");
////           sleep(1);
////       }
//        unordered_map<string,size_t>word_count;
//        string word;
//        while (cin>>word)
//        {
//            ++word_count[word];
//        }
//        for (const auto &w : word_count)
//        {
//            cout<<w.first<<"occurs"<<w.second
//                <<( (w.second>1)?"times":"time")<<endl;
//        }

       //   string line,word;
       //   vector<PersonInfo>people;
       //   ifstream infile;
       //   stringstream ss;
       //   infile.open("file.txt");
       //   int count = 1;
       //   if (infile)
       //   {
       //       while (getline(infile,line))
       //       {
       //           PersonInfo info;
       //           ss.clear();
       //           ss<<line;
       //           ss>>info.name;
       //           while (ss>>word)
       //           {
       //              info.phones.push_back(word);
       //           }
       //           people.push_back(info);
//     //             printf("this is line %d\n",count++);
       //           cout<<line<<endl;
       //       }
       //      vector<string>::iterator it1;
       //      vector<PersonInfo>::iterator it = people.begin();
       //      for (;it != people.end();++it)
       //      {
       //        cout<<it->name<<" ";
       //        for (it1 = it->phones.begin();it1!= it->phones.end();it1++)
       //        {
       //            cout<<*it1<<" ";
       //        }
       //        cout<<endl;
       //      }
       //   }
     //  unordered_map<string,size_t>word_count;
     //  string word;
     //  while (cin>>word)
     //      ++word_count[word];
     //  unordered_map<string,size_t>::iterator it;
     //  cout<<word_count.bucket_count()<<endl;
//       for (it = word_count.begin();it != word_count.end();++it)
//       {
//           cout<<it->first<<" "<<it->second<<endl;
//       }
       // shared_ptr<string>p1;
       // if (p1->empty() )
       // {
       //     *p1 = "hi";
       //     printf("aa\n");
       // }
     // shared_ptr<string>p1 = make_shared<string>("aaaaa");
     // if (p1)
     // {
     //     cout<<*p1<<endl;
     // }
   // shared_ptr<string>p = make_shared<string>(10,'a'); 
//    char* ptr[] = {"aaa","ffdsa","dfs","rwe22"};
//    vector<string>vec(ptr,ptr+4);
//    for (auto beg = vec.begin(); beg != vec.end();++beg)
//    {
//        cout<<*beg<<" ";
//    }
    
   // char* ptr[] = {"aaa","ffdsa","dfs","rwe22"};
   // vector<char*>vec(ptr, ptr +5);
//    initializer_list<string>lst{"aaa","ffdsa","dfs","rwe22"};   
//    vector<string>vec(lst);
//    for (auto beg = vec.begin();beg != vec.end();++beg)
//    {
//        cout<<*beg<<" ";
//    }cout<<endl;
//    int* pi = new int;
//    cout<<*pi<<endl;
 //   vector<int>* pv = new vector<int>{0,1,2,3,4,5,6,7,8};
  // class PrintString
  // {
  //     public:
  //         PrintString(ostream& o=cout,char c = ' ')
  //             :os(cout),sep(c){}
  //         void func() {}
  //         void operator()(const string& s)const
  //         {
  //             os<<s<<sep;
  //             func();
  //         }
  //     private:
  //          ostream& os;
  //          char     sep;
  // };
  //  PrintString printer(cout,'\n');
  //  string str("afafd");
  //  printer(str);
//struct PersonInfo
//{
//    string name;
//    vector<string>phones;
//};
//  class background_task
//  {
//      public:
//          void do_sth(){printf("do_sth called\n");}
//          void do_sthelse(){printf("do_sthelse called\n");}
//          void operator() () 
//          {
//              do_sth();
//              do_sthelse();
//          }
//  };
//struct func
//{
//    int& i;
//    func(int& i_):i(i_){}
//    void operator() ()
//    {
//        for (unsigned j = 0;j<1000000;++j)
//        {
//            printf("j: %d\n",j);
//        }
//    }
//};
//int val = 0;
//func my_func(val);
//std::thread my_thread(my_func);
//my_thread.join();
//my_thread.detach();
//    background_task f;
//    std::thread my_thread((background_task()));
//    std::thread my_thread{background_task()};//declare a thread object
   // std::thread my_thread(f); //start a thread
//    my_thread.join();
  //  class X
  //  {
  //      public:
  //          void do_lengthy_work(std::string str)
  //          {
  //              printf("do_lengthy_work() called: %s\n",str.c_str());
  //          }
  //  };
  //  X my_x;
  //  std::thread t(&X::do_lengthy_work,&my_x,"hello world");
  //  if (t.joinable())
  //  {
  //      t.join();
  //  }
//  shared_ptr<int>p = make_shared<int>(43);
//  shared_ptr<int>q(p);
//  if (q)
//  {
//    int* ptr = p.get();
//    cout<<*ptr<<endl;
//  }
//  if (p.unique())
//  {
//      cout<<"unique"<<endl;
//  }
//  else
//  {
//      cout<<"use_count: "<<p.use_count()<<endl;
//  }
//    char* word[]={"aaa","bbb","ccc","ddd","eee"};
//    char* p = word;
//    shared_ptr<char*>ptr(word);
//    if (ptr)
//    {
//  //      char* p = *(ptr.get());
//  //      cout<<p<<endl;
//  //      if (p != NULL)
//  //      {
//  //          cout<<p++;
//  //      }
//    }
    //int aa = 100;int* ptr = &aa; 
    //shared_ptr<int>p2(ptr);
    //if (p2){
    //   cout<<*p2<<endl;
 //   shared_ptr<int>ptr = make_shared<int>(100);
 //   process(ptr);
 //   printf("use-count now: %d\n",ptr.use_count());
   // int* ptr(new int(1024));
   // process(shared_ptr<int>(ptr));
   // if (ptr)
   // {
   //     cout<<"memory destroy"<<endl;
   // }
   // else
   // {
   //     cout<<*ptr<<endl;
   // }

 //  int* aa = 
 //   shared_ptr<int>ptr(new int(99));
 //  printf("use-count: %d\n",ptr.use_count());
 //  ptr.reset();
 // // process(ptr);
 //  printf("use-count: %d\n",ptr.use_count());
//   int* q = ptr.get();
//   {
//       shared_ptr<int>aa(q);
//       printf("use-count: %d\n",ptr.use_count());
//   }
//   printf("out of range: %d\n",ptr.use_count());
//   if (q){
//   cout<<*q<<endl;}
   //multimap<string,string>m={{"aa","aaa"},{"bb","bbb"},{"cc","ccc"},
   //                          {"aa","abb"},{"cc","cvc"},{"aa","abc"} }; 
   //pair< map<string,string>::iterator, map<string,string>::iterator >ret;
   // 
   //for(ret = m.equal_range("aa");ret.first != ret.second;++ret.first)
   //{
   //    cout<<ret.first->second<<endl;
   //}
//    unordered_map<string,string>m={{"aa","aaa"},{"bb","bbb"},{"cc","ccc"},
  //                                 {"dd","ddd"},{"aa","abc"},{"aa","ads"}};
//    cout<<m.bucket_count()<<endl;
//    cout<<m.max_bucket_count()<<endl;
  //  cout<<m.bucket("aa")<<endl;
  ///  auto f = [](const string& s1,const string& s2) bool{ return s1.size() < s2.size();};
//    cout<<f("aaa","bbb")<<endl;
//    vector<string>vec={"aaafsa","bdbds3","ccd","dsssssd"};
//    const  size_t sz = 5;
//    sort(vec.begin(),vec.end(),[](const string& a,const string& b){return a.size()<b.size();});
//    vector<string>::iterator it = find_if(vec.begin(),vec.end(),[sz](const string& a){return a.size()>=sz;});
//    for_each(it,vec.end(),[](const string& s){cout<<s<<" ";});
//    size_t v1 = 42;
//    auto f2 = [&v1] {return ++v1;};
//    v1 = 0;
//    cout<<f2()<<endl;
  //  vector<int>vec = {-2,1,3,4,53,23,-4};
  //  transform(vec.begin(),vec.end(),vec.begin(),
  //            [](int i)->int{if (i<0)return -i;else return i;});
 ////   for_each(vec.begin(),vec.end(),[](int i){cout<<i<<" ";});
  //  auto fcn = [](char ch)->char{return ch;};
  //  cout<<fcn('M')<<endl;
    class PrintString{
        public:
            PrintString(ostream& o = cout,char c=' '):
                os(o),sep(c){}
            void operator()(const string& s)const
            {
                os<<s<<sep;
            }
        private:
            ostream &os;
            char sep;
    };
   // PrintString printer;
   // printer("PrintString");
//    PrintString errors(cerr,'\n');
//    errors("PrintString");
  //  vector<string>vec={"aa","bb","cc","dd","ee"};
  //  for_each(vec.begin(),vec.end(),PrintString());
   // plus<int>intAdd;
   // negate<int>intNegate;
   // cout<<intNegate(intAdd(10,30))<<endl;
 //   string aa = "dsa", bb = "afc", cc = "abc", dd = "esa",ee="cay";
 //   string* a = &aa, *b = &bb, *c=&cc, *d = &dd, *e=&ee;     
 //   //  string* a="dsa",*b = "afc";
 //   vector<string*>vec={a,b,c,d,e};
 //   sort(vec.begin(),vec.end(),greater<string*>());
 //   for_each(vec.begin(),vec.end(),[](const string* p){cout<<*p<<endl;});
   // sort(vec.begin(),vec.end(),[](const string& a,const string& b){return a<b;});
 //   sort(vec.begin(),vec.end(),greater<string>());
 //   for_each(vec.begin(),vec.end(),[](const string& s){cout<<s<<endl;});
//   function<int(int,int)> f1 = add;
//   //cout<<f1(2,5)<<endl;
//    function<int(int,int)>f2 = [](int x, int y){return x+y;};
//    cout<<f2(4,6)<<endl;
   // map<string,function<int(int,int)> >binops={ {"+",add},{"/",Divide()},
   //     {"*",[](int i, int j){return i * j;}}                     };
   // binops.insert({"+",add});
   //cout<<binops["+"](3,5)<<endl;
  //  binops.insert(make_pair("%",mod));
  //  map<string,function<int(int,int)>>::iterator it = binops.find("%");
  //  if (it != binops.end())
  //  {
  //     cout<<it->second(10,3)<<endl;
  //  }
  //  binops.insert("%",mod);
 //   cout<<binops["/"](32,4)<<endl;
  //  shared_ptr<int>p1 = make_shared<int>(5);
  //  shared_ptr<string>p2=make_shared<string>(10,'s'); 
  //  auto p = make_shared<string>(5,'a');
  //  cout<<*p<<endl;
//    if (p2)
//    {
//        string* ptr = p2.get();
//        if (ptr)
//        {
//            
//            cout<<*ptr<<endl;
//        }
//
//    }
//        cout<<*p2<<endl;
  //  if(p1->empty())
  //  {
  //      cout<<"p1 empty"<<endl;
  //  }
  //  typedef map<string,int> Map;
  //  Map mapStudent;
  //  mapStudent.insert(make_pair("aaa",11));
  //  mapStudent.insert(make_pair("bbb",22));
  //  Map::iterator it = mapStudent.begin();
  //  while (it != mapStudent.end())
  //  {
  //      cout<<it->first<<" "<<it->second<<endl;
  //      it++;
  //  }
//    vector<int>* p = new vector<int>{0,1,2,3,4,5};
//    shared_ptr<vector<int>*>pv = make_shared<vector<int>*>(p);
//    if (pv)
//    {
       // for_each(p->begin(),p->end(),[](const int& i){cout<<i<<" ";});
     //   vector<int>::iterator it =(pv->get())->begin();                 //pv->begin();
     //   for  (;it!= (pv->get())->end();++it)
     //   {
     //       cout<<*it<<" ";
     //   }
   //     for_each(    [](const int& i){cout<<i<<" ";});
  //  }
 //   shared_ptr<int>p(new int(1024)); 
 //   if (1)
 //   {
 //       shared_ptr<int>ptr=make_shared<int>(50);
 //       //shared_ptr<int>qtr(ptr,Object());
 //   }
   // int* pt(new int(1024));
   // shared_ptr<int>p(pt);
   // test(p);
  //  shared_ptr<int>p = make_shared<int>(9);
  //  shared_ptr<int>q(p);
  //  cout<<q.use_count()<<endl;
  //  if (!p.unique())
  //  {
  //      p.reset(new int(99));Object obj;
  //      shared_ptr<Object>ptr(&obj,test);
  //  }
  //  cout<<*p<<" "<<*q<<endl;
 //   unique_ptr<int>p(new int(1024));
    //unique_ptr<int>q(p);
   // shared_ptr<int>q(p);
//    unique_ptr<int>q(p.release());
//    unique_ptr<int>q->reset(p.release());
   // unique_ptr<int>q(p.release());
   // cout<<*q<<endl;
  //  shared_ptr<int>p = make_shared<int>(1024);
  //  weak_ptr<int>wp(p);
  //  shared_ptr<int>ptr(wp.lock());
  //  if (ptr)
  //      cout<<*ptr<<endl;
//    shared_ptr<int>sp(new int[10],[](int*){cout<<"test"<<endl;});
//    sp.reset();

 //   pthread_attr_t attr;
 //   pthread_attr_init(&attr);
 //   pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
 //   pthread_t tids[NUM_THREADS];
 //   int index[NUM_THREADS];
 //   for (int i = 0;i<NUM_THREADS;i++)
 //   {
 //       index[i] = i;
 //       int ret = pthread_create(&tids[i],NULL,Hello::say_hello,(void*)&index[i]);
 //       if (ret != 0)
 //       {
 //           cout<<"pthread_create error"<<endl;
 //       }
 //   }
 //   pthread_attr_destroy(&attr);
 //   void* status= NULL;
 //   for (int i = 0;i<NUM_THREADS;i++)
 //   {
 //       pthread_join(tids[i],&status);
 //       cout<<"status: "<<(long)status<<endl;
 //   }
  //  class Resource{};
  //  class File
  //  {
  //      public:
  //          File(string name)
  //          {
  //              open(name);
  //          }
  //          FILE* get(){return file_;}
  //          ~File() {fclose(file_);}
  //      private:
  //          void open(string name)
  //          {
  //              file_ = fopen(name.c_str(),"r");
  //          }
  //          FILE* file_;
  //  };
  //  class FileRAII
  //  {
  //      public:
  //          FileRAII(FILE* aFile):file_(aFile){}
  //          ~FileRAII(){fclose(file_);}
  //          FILE* get(){return file_;}
  //      //    FILE* open(string name);
  //      private:
  //              FILE* file_;
  //  };
  //  File file("file.txt");
  //  FILE* pfile = file.get();
  //  char* buff = new char[128];
  //  if (pfile)
  //  {
  //      int bytes = fread(buff,1,128,pfile);
  //      if (bytes>0)
  //          cout<<buff<<endl;
  //  }
//    FILE* fp;
//    string filename = "file.txt";
////    char* filename = "file.txt";
//    if ( (fp = fopen(filename.c_str(),"r")) == NULL)
//    {
//        printf("not open\n");exit(1);
//    }
//    FileRAII fileraii(fp);
   // class RAII
   // {
   //     public:
   //         RAII(Resource* aResource):r_(aResource){}
   //         ~RAII(){delete r_;}
   //         Resource* get(){return r_;}
   //     private:
   //         Resource* r_;
   // };
//   signal(SIGINT,signal_handler_func);
 //  signal(SIGQUIT, SIG_IGN);
 //  struct sigaction act , oact;
 //  act.sa_handler = signal_handler_func;
 //  sigemptyset(&act.sa_mask);
 //  act.sa_flags = 0;
 //  sigaction(SIGINT,&act,&oact);
 //  for (;;)
 //  {
 //      sleep(1);
 //      printf("sleep\n");
 //  }
    int num = 0;
    char buff[128];
    sprintf(buff, "%d",num);
    std::string str = buff;
    if (!str.empty())
    {
        cout<<str<<endl;
    }
    return 0;

}
//bool predCompare(const string& str)
//{
//    return true;
//}


