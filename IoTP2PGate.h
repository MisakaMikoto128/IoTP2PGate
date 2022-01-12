#ifndef _IOTP2PGATE_H_
#define _IOTP2PGATE_H_
/*************************************************************************
	> File Name: tcp_sever.c
	> Author: LiuYuanlin 
	> Mail: 
	> Created Time: Thu 26 Aug 2021 12:39:54 AM PDT
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <stdbool.h>
#include <errno.h>
#define FD_LIST_SIZE 2
#define MAX_TCP_CONNECTIONS 2
extern int fd_list[FD_LIST_SIZE];
void init_fd_list();



#define SOCKET_CAN_READ_AND_WRITE 0x01
#define SOCKET_NOT_ACCESSABLE 0x00

#define SOCKET_CAN_READ 0x01
#define SOCKET_CAN_WRITE 0x10
#define SOCKET_NOT_ACCESSABLE 0x00

void *thread_rev(void *arg);
void *thread_rev1(void *arg);
#define isSocketFDValid(sock) ((sock) > 0)
//file descriptor flag
#define INVALID_FD -1
#endif // _IOTP2PGATE_H_

