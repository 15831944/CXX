#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define NDG   2000
#define DGLEN 1400
void dg_cli(int sockfd, sockaddr*pservaddr, socklen_t serlen)
{
    int n,i;
    char sendline[1024],recvline[1024];
    for (i=0;i<NDG;i++)
    {
        sendto(sockfd,sendline,DGLEN,0,pservaddr,serlen);
    }
 //   while (cin.getline(sendline,1024))
 //   {
 ////       write(sockfd,sendline,strlen(sendline));
 ////       n = read(sockfd,recvline,1024);
 //       sendto(sockfd,sendline,strlen(sendline),0,pservaddr,serlen);
 //       n = recvfrom(sockfd,recvline,1024,0,NULL,NULL);
 //       recvline[n]='\0';
 //       cout<<recvline<<endl;
 //   }
}
void str_cli(int sockfd)
{
    int maxfd;
    fd_set rset;
    char sendline[1024], recvline[1024];
    FD_ZERO(&rset);
    for (;;)
    {
        FD_SET(STDIN_FILENO, &rset);
        FD_SET(sockfd, &rset);
        maxfd = max(STDIN_FILENO, sockfd) + 1;
        select(maxfd,&rset,NULL,NULL,NULL);
        if (FD_ISSET(sockfd, &rset))//sockfd is readable
        {
            if ( read(sockfd, recvline, 1024) == 0)
            {
              printf("str_cli read error\n");
            }
            printf("read: %s\n", recvline);
        }
        if ( FD_ISSET(STDIN_FILENO, &rset) ) // input is readable
        {
            cin.getline(recvline,1024);
            write(sockfd, sendline,strlen(sendline));
        }
    }
  //  while ( cin.getline(sendline,1024) )
  //  {
  //      write(sockfd,sendline,strlen(sendline));
  //      memset(recvline,0,1024);
  //      if ( read(sockfd, recvline, 1024) == 0)
  //      {
  //          printf("str_cli read error\n");
  //      }
  //      printf("read: %s\n",recvline);
  //  }
}
int main(int argc, char* argv[])
{
    int sockfd;
    sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(12345);
    inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
    connect(sockfd,(sockaddr*)&servaddr,sizeof(sockaddr));
    str_cli(sockfd);
    exit(0);
//    dg_cli(sockfd,(sockaddr*)&servaddr,sizeof(servaddr));



    return 0;
}
