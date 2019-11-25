//
// Created by liuminxuan on 2019/11/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define MAXSIZE 1024

int main(int argc,char* argv[])
{
    int sockfd,new_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sin_size,portnumber;
    char buf[MAXSIZE];
    if (argc!=2)
    {
        fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
        exit(1);
    }
    if ((portnumber=atoi(argv[1]))<0)
    {
        fprintf(stderr,"Usage:%s portnumber \a\n",argv[0]);
        exit(1);
    }
    if ((sockfd=socket(AF_INET,SOCK_STREAM,0))==1)
    {
        fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
        exit(1);
    }
    bzero(&server_addr,sizeof(struct sockaddr_in));
    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(portnumber);
    if (bind(sockfd,(struct sockaddr*)(&server_addr), sizeof(struct sockaddr))==-1)
    {
        fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
        exit(1);
    }
    if ((listen(sockfd,5))==-1)
    {
        fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
        exit(1);

    }
    while (1)
    {
        sin_size= sizeof(struct sockaddr_in);
        if ((new_fd=accept(sockfd,(struct sockaddr*)(&client_addr),&sin_size))==-1)
        {
            fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
            exit(1);
        }
        fprintf(stderr,"Server get connection form:%s\n",inet_ntoa(client_addr.sin_addr));
        printf ("Connected successful,please input the message[<1024 bytes]:\n");
        if (fgets(buf,sizeof(buf),stdin)!=buf)
        {
            printf("fgets error!\n");
            exit(1);
        }
        if (write(new_fd,buf,strlen(buf))==-1)
        {
            fprintf(stderr,"Write Error:%s\n",strerror(errno));
            exit(1);
        }
        close(new_fd);
    }
    close(sockfd);
    exit(0);
    //return 0;
}
