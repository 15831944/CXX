#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <iostream>
#include <signal.h>
#include <netdb.h>
#include <sys/utsname.h>
using namespace std;
int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option);
    return old_option;
}
void addfd(int epollfd, int fd, bool enable_et)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if (enable_et)
    {
        event.events |= EPOLLET;
    }
    epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
    setnonblocking(fd);
}
void et(epoll_event* events, int number, int epollfd,int listenfd)
{
    char buf[10];
    for (int i = 0;i<number;i++)
    {
        int sockfd = events[i].data.fd;
        if (sockfd == listenfd)
        {
            sockaddr_in clieaddr;
            socklen_t clielen = sizeof(clieaddr);
            int connfd = accept(listenfd,(sockaddr*)&clieaddr,&clielen);
            addfd(epollfd,connfd,false);
        }
        else if (events[i].events & EPOLLIN)
        {
            printf("event trigger once\n");
            while (true)
            {
                memset(buf,0,10);
                int ret = recv(sockfd,buf,9,0);
                if (ret<0)
                {
                    if (errno == EAGAIN || errno ==EWOULDBLOCK)
                    {
                        printf("read later\n");
                        break;
                    }
                    close(sockfd);
                    break;
                }
                else if (ret == 0)
                {
                    close(sockfd);
                }
                else
                {
                    printf("get %d bytes: %s\n",ret,buf);
                }
            }
        }
    }
}
void lt(epoll_event* events, int number,int epollfd, int listenfd)
{
    char buf[10];
    for (int i = 0;i<number;i++)
    {
        int sockfd = events[i].data.fd;
        if (sockfd == listenfd)
        {
            sockaddr_in clieaddr;
            socklen_t clielen = sizeof(clieaddr);
            int connfd = accept(listenfd,(sockaddr*)&clieaddr,&clielen);
            addfd(epollfd,connfd,false);
        }
        else if (events[i].events & EPOLLIN)
        {
            printf("event trigger once!\n");
            int ret = -1;
            memset(buf,0,10);
            ret = recv(sockfd,buf,9,0);
            if (ret <=0)
            {
                close(sockfd);
                continue;
            }
            printf("get %d bytes: %s\n",ret,buf);
        }
        else
        {
            printf("sth else happened\n");
        }
    }
}
static int count =0;
void recvfrom_int(int signo)
{
    printf("\nreceived %d datagrams\n",count);
}
void dg_echo(int sockfd,sockaddr*pcliaddr, socklen_t clilen)
{
    int n, l;
    socklen_t len;
    char msg[1024];
    signal(SIGINT,recvfrom_int);
    for (;;)
    {
        len = clilen;
        recvfrom(sockfd,msg,1024,0,pcliaddr,&len);
        count++;
     //   n = recvfrom(sockfd, msg,1024,0,pcliaddr,&len);
     //   string str = "you input is: ";
     //   l = str.length();
     //   str += msg;
     //   sendto(sockfd,str.c_str(),l+n,0,pcliaddr,len);
    }
}
void str_echo(int sockfd)
{
    int  n;
    char line[1024];
    for (;;)
    {
        if ( (n=read(sockfd, line, 1024)) == 0 )
            return ;
       write(sockfd, line, n); 
    }
}
int main(int argc, char* argv[])
{
    int listenfd, connfd, maxi, maxfd, sockfd;
    int nready, client[FD_SETSIZE];
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    fd_set rset, allset;
    pid_t  childpid;
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
   // servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(12345);
    bind(listenfd,(sockaddr*)&servaddr, sizeof(servaddr));
    listen(listenfd,5);
    maxfd = listenfd ;
    int i = -1;
    maxi = -1;
    for (i = 0;i<FD_SETSIZE;i++)
        client[i] = -1;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);
    int nChar= -1; 
    char line[128];
    for (;;)
    {
        rset = allset;
        nready = select(maxfd+1, &rset,NULL,NULL,NULL);
        if ( FD_ISSET(listenfd, &rset) ){
            clilen = sizeof(cliaddr);
            connfd = accept(listenfd, (sockaddr*)&cliaddr, &clilen);
            for (i = 0;i< FD_SETSIZE;i++)
            {
                if (client[i] < 0)
                {
                    client[i] = connfd;
                    break;
                }
            }
            if ( i == FD_SETSIZE)
            {
                printf("too many clients\n");
            }
            FD_SET(connfd, &allset);
            if (i > maxi) maxi = i;
            if ( --nready <= 0) continue;
   
       for (i = 0;i<maxi;i++)
       {
          if ( (sockfd = client[i]) < 0)
             continue;
          if (FD_ISSET(sockfd,&rset))
          {
           
             if ( nChar = read(sockfd,line,128) == 0 )
             {
                close(sockfd);
                FD_CLR(sockfd,&allset);
                client[i] = -1;
             }
             else { write(sockfd, line, nChar);}
             if (--nready <= 0)
                 break;
           }
        }
     }
  //  for (;;)
  //  {
  //      clilen = sizeof(cliaddr);
  //      connfd = accept(listenfd, (sockaddr*)&cliaddr,&clilen);
  //      if ( childpid == fork() == 0)
  //      {
  //          close(listenfd);
  //          str_echo(connfd);
  //          exit(1);
  //      }
  //  }
  //  close(connfd);
    return 0;
}
}
