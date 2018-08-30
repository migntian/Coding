#include "http.h"

typedef struct Arg{
    int fd1;
    int fd2;
}Arg;
int getline(int sock,char *line,int size)
{
    int c = 'a';
    int i = 0;
    while(i < size-1 && c != '\n')
    {
        s = recv(sock,&c,1,0);
        if(s > 0)
        {
            if(c == '\r')
            {
                recv(sock,&c,1,MSG_PEEK);
                if(c != '\n')
                {
                    c = '\n';
                }
                else
                {
                    recv(sock,&c,1,0);
                }
            }
            line[i++] = c;
        }
        else
        {
            break;
        }
    }
    line[i] = '\n';
    return i;
}
void clear_header(int sock)
{
    char line[MAX];
    do{
        getline(sock,line,sizeof(line));
    }while(strcmp(line,"\n") != 0);
}
void echo_www(int sock,char *path,int size,int *err)
{
    clear_header(sock);
    int fd = open(path,O_RDONLY);
    if(fd < 0)
    {
        *err = 404;
        return;
    }
    char line[MAX];
    sprintf(line,"HTTP/1.0 200 OK\r\n");
    send()
}
void *handler_request(void *arg)
{
    Arg* sock = (Arg *)arg;
    int web_sock = sock->fd1;
    char line[MAX];
    char method[MAX/32];
    char url[MAX];
    char path[MAX];
    int errcode = 200;
    int cgi = 0;
    char *query_string = NULL;
    if(getline(web_sock,line.sizeof(line)) < 0)
    {
        errcode = 404;
        goto end;
    }
    int i = 0;
    int j = 0;
    while(i < sizeof(method)-1 && j < sizeof(line) && !isspace(line[j]))
    {
        method[i++] = line[j++];
    }
    method[i] = '\0';
    i = 0;
    while(i < sizeof(url)-1 && j < sizeof(line) && !isspace(line[j]))
    {
        url[i++] = line[j++];
    }
    url[i] = '\0';
    
    if(strcasecmp(method,"get") == 0)
    {
        query_string = url;
        while(*query_string)
        {
            if(*query_string == '?')
            {
                *query_string = '\0';
                query_string++;
                cgi = 1;
                break;
            }
            query_string++;
        }
    }
    else if(strcasecmp(method,"post") == 0)
    {
        cgi = 1;
    }
    else
    {
        errcode = 404;
        goto end;
    }
    
    sprintf(path,"wwwroot%s",url);
    if(path[strlen(path)-1] == '/')
    {
        strcat(path,HOME_PAGE);
    }
    struct stat st;
    if(stat(path,&st) < 0)
    {
        errcode = 404;
        goto end;
    }
    else
    {
        if(S_ISDIR(st.st_mode))
        {
            strcat(path,HOME_PAGE);
        }
        else
        {
            if((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) ||(st.st_mode & S_IXOTH))
            {
                cgi = 1;
            }
        }
        if(cgi = 1)
        {
            errcode = echo_cgi(sock,path,method,query_string);
        }
        else
        {
            echo_www(web_sock,path,st.st_size,&errcode);
        }
    }
}

void SetNoBlock(int sock)
{
    int f1 = fcntl(sock,F_GETFL);
    if(f1 < 0)
    {
        perror("fcntl");
        return;
    }
    fcntl(sock,F_SETFL,f1 | O_NONBLOCK);
}

void request_listensock(int listensock,int epoll_fd)
{
    struct sockaddr_in client1;
    int len1 = sizeof(client1);
    int connect_fd = accept(listensock,(struct sockaddr*)&client1,&len1);
    if(connect_fd < 0)
    {
        perror("accept error");
        continue;
    }
    printf("client %s:%d connect\n",inet_ntoa(client1.sin_addr),ntohs(client1.sin_port));
    SetNoBlock(connect_fd);
    struct epoll_event s;
    s.data.fd = connect_fd;
    s.events = EPOLLIN | EPOLLET;

    if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,connect_fd,&s) < 0)
    {
        perror("epoll_ctl");
        return;
    }
    return;
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
    
    int epoll_fd = epoll_create1(0);
    if(epoll_fd < 0)
    {
        perror("epoll_create");
        return 1;
    }
    SetNoBlock(sock1);
    struct epoll_event event;
    event.events = EPOLLIN | EPOLLET;
    event.data.fa = sock1;
    if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,sock1,&event) < 0)
    {
        perror("epoll_ctl");
        return 1;
    }

    for(;;)
    {
        struct epoll_event events[10];
        int size = epoll_wait(epoll_fd,events,sizeof(events)/sizeof(events[0]),-1);
        if(size < 0)
        {
            perror("epoll_wait");
            continue;
        }
        if(size == 0)
        {
            printf("epoll timeout\n");
            continue;
        }
        int i = 0;
        for(;i < size;i++)
        {
            if (events[i].events != EPOLLIN)
            {
                continue;
            }
            if(events[i].data.fd == sock1)
            {
                request_listensock(sock1,epoll_fd);
            }
            else
            {
                pthread_t id;
                Arg *arg = (Arg*)malloc(sizeof(Arg));
                arg->fd1 = client_sock1;
                arg->fd2 = client_sock2;
                pthread_create(&id,NULL,handler_request,(void *)arg);
                pthread_detach(id);
            }
        }
    }
    return 0;
}

    //for(;;)
    //{
    //    struct sockaddr_in client1;
    //    int len1 = sizeof(client1);
    //    int client_sock1 = accept(sock1,(struct sockaddr*)&client1,&len1);
    //    if(client_sock1 < 0)
    //    {
    //        perror("accept error");
    //        continue;
    //    }
    //    printf("accept success..\n");
    //    pthread_t id;
    //    Arg *arg = (Arg*)malloc(sizeof(Arg));
    //    arg->fd1 = client_sock1;
    //    arg->fd2 = client_sock2;
    //    pthread_create(&id,NULL,handler_request,(void *)arg);
    //    pthread_detach(id);
    //}
