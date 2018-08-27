#include "http.h"

typedef struct Arg{
    int fd1;
    int fd2;
}Arg;
void *handler_request(void *arg)
{
    Arg* sock = (Arg *)arg;
    int fd1 = sock->fd1;
    int fd2 = sock->fd2;
    char buf[1024] = {0};
    for(;;)
    {
        ssize_t size = read(fd1,buf,sizeof(buf));
        if(size < 0)
        {
            perror("read error");
            continue;
        }
        if(read == 0)
        {
            printf("client say bye,i will say bye too");
            close(fd1);
            break;
        }
        buf[size-1] = '\0';
        printf("client1 #%s\n",buf);
        write(fd2,buf,sizeof(buf));
        read(fd2,buf,sizeof(buf));
        printf("client2 #%s\n",buf);
        write(fd1,buf,sizeof(buf));
    }
    close(fd1);
    close(fd2);
    return 0;
}
int main(int argc,char *argv[])
{
    if(argc != 3)
    {
        printf("./server [port1] [port2]\n");
        return 1;
    }
    int sock1 = listensock(atoi(argv[1]));
    int sock2 = listensock(atoi(argv[2]));

    struct sockaddr_in client2;
    int len2 = sizeof(client2);
    int client_sock2 = accept(sock2,(struct sockaddr*)&client2,&len2);

    for(;;)
    {
        struct sockaddr_in client1;
        int len1 = sizeof(client1);
        int client_sock1 = accept(sock1,(struct sockaddr*)&client1,&len1);
        if(client_sock1 < 0)
        {
            perror("accept error");
            continue;
        }
        printf("accept success..\n");
        pthread_t id = 0;
        Arg *arg = (Arg*)malloc(sizeof(Arg));
        arg->fd1 = client_sock1;
        arg->fd2 = client_sock2;
        pthread_create(&id,NULL,handler_request,(void *)arg);
        pthread_detach(id);

    }
    return 0;
    
}
