#include "http.h"

int listensock(int port)    
{
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0)
    {
        perror("socket error");
        return 2;
    }
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(port);

    if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
    {
        perror("bind error");
        return 3;
    }

    if(listen(sock,5) < 0)
    {
        printf("listen error");
        return 4;
    }
    return sock;
}
