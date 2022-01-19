
#include "IoTP2PGate.h"
#include "debug.h"

int fd_list[FD_LIST_SIZE];

void init_fd_list()
{
    for (int i = 0; i < FD_LIST_SIZE; i++)
    {
        fd_list[i] = INVALID_FD;
    }
}

static void usage(const char *proc)
{
    printf("Please use %s [ip] [port]\n", proc);
}

/*
建立TCP连接后的接收线程
*/
void *thread_rev(void *arg)
{
    debug_print("create a new receiving thread,%d\n", *(int *)arg);
    int fd_id = *(int *)arg;
    int another_id = (fd_id + 1) % 2;
    char buf[1024];
    while (true)
    {
        if (isSocketFDValid(fd_list[fd_id]))
        {
            debug_print("check_client_accessable success,mfd:[%d],another_fd:[%d]\n", fd_list[fd_id], fd_list[another_id]);
            memset(buf, '\0', sizeof(buf));
            //read data from client

            ssize_t len = read(fd_list[fd_id], buf, sizeof(buf) - 1);
            if (len > 0)
            {

                buf[len] = '\0';
                debug_print("client say : %s\n", &buf[0]);
                fflush(stdout);
                //write data to another client
                if (isSocketFDValid(fd_list[another_id]))
                {
                    int ret = write(fd_list[another_id], buf, strlen(buf));
                    if (ret == -1)
                    {
                        debug_print("write error\n");
                    }
                }
            }
            else if (len == 0 && errno != EINTR)
            {
                debug_print("Client has been closed!\n");
                close(fd_list[fd_id]);
                fd_list[fd_id] = INVALID_FD;
                printf("fd_list[%d] = %d\n", fd_id, fd_list[fd_id]);
                debug_print("check_client_accessable success,mfd:[%d],another_fd:[%d]\n", fd_list[fd_id], fd_list[another_id]);
            }
        }
    }
}
