#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("./client [IP] [PORT]\n");
        return 1;
    }
    int sock = socket(AF_INET,SOCK_STREAM,0);

    if(sock < 0)
    {
        perror("socket error");
        return 2;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(atoi(argv[2]));

    int sock_client = connect(sock,(struct sockaddr*)&server,sizeof(server));
    if(sock_client < 0)
    {
        perror("connect error");
        return 3;
    }

    while(1)
    {
        char buf[1024] = {0};
        read(sock,buf,sizeof(buf));
        printf("client1:%s",buf);
        fgets(buf,sizeof(buf),stdin);
        write(sock,buf,sizeof(buf));
        printf("please wait...\n");
    }

    close(sock);
    return 0;
}

