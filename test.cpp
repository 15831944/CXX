#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
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
using namespace std;
//int a()
//{
//    sleep(2);
//    return 0;
//}
//int b()
//{
//    a();
//    return 0;
//}
//int c()
//{
//    b();
//    return 0;
//}
//void* myThread1(void*)
//{
//    int i = 9;
//    while (i>0)
//    {
//        printf("Our 1st pthread,create\n");
//        sleep(2);
//        i--;
//        c();
//    }
//    return NULL;
//}
//void* myThread2(void*)
//{
//    int i = 5;
//    while (i>5)
//    {
//        printf("our 2nd pthread create\n");
//        sleep(2);
//        i--;
//    }
//    return NULL;
//}
void dummy_func(void)
{
    char* ptr = 0x00;
    *ptr ='a';
}
int main()
{
//    printf("linux c++\n");
//    int ret = 0;
//    pthread_t tid1,tid2;
//    ret = pthread_create(&tid1,NULL,myThread1,NULL);
//    if (ret)
//    {
//        printf("create pthread error\n");
//        return 1;
//    }
//    
//    ret = pthread_create(&tid2,NULL,myThread2,NULL);;
//    if (ret)
//    {
//        printf("create pthread error\n");
//        return 1;
//    }
//    pthread_join(tid1,NULL);
//    pthread_join(tid2,NULL);
    dummy_func();
    return 0;
}



