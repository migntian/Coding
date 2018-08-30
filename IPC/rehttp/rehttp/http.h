#pragma once
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "listensock.h"
#include "echo_www.h"

int listensock(int port);
void echo_www(int sock,char *path,int size,int *err);

