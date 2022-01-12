
#include "IoTP2PGate.h"
#include "debug.h"
/*
return : 
  0 : success
  other number : error
*/
int tcp_socket_sever_init(const char *ip, int port, int *psock)
{
  //1.create socket
  int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  *psock = sock;
  if (sock < 0)
  {
    perror("Create socket error!\n");
    return 1;
  }
  debug_print("Create socket success\n");

  struct sockaddr_in local;
  local.sin_family = AF_INET;
  local.sin_port = htons(port);
  local.sin_addr.s_addr = inet_addr(ip);
  int allow_reuse_port = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (const void *)&allow_reuse_port, sizeof(allow_reuse_port));
  //2.bind
  if (bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0)
  {
    debug_print("Bind error\n");
    close(sock);
    return 2;
  }
  debug_print("Bind success\n");
  //3.listen
  if (listen(sock, 10) < 0)
  {
    debug_print("Listen error\n");
    close(sock);
    return 3;
  }
  debug_print("Listen success\n");

  return 0;
}

int tcp_sever_loop(int sock)
{
  //listen and accept client loop
  //4.accept
  struct sockaddr_in peer;
  socklen_t len = sizeof(peer);
  while (true)
  {
    //block wait for client
    int fd = accept(sock, (struct sockaddr *)&peer, &len);
    if (fd < 0)
    {
      perror("accept error\n");
      close(sock);
      return 4;
    }
    debug_print("get connect,client ip is %s port is %d\n", inet_ntoa(peer.sin_addr), ntohs(peer.sin_port));

    if (fd_list[0] == INVALID_FD)
    {
      fd_list[0] = fd;
      debug_print("fd_list[0] = %d\n", fd_list[0]);
    }
    else if (fd_list[1] == INVALID_FD)
    {
      fd_list[1] = fd;
      debug_print("fd_list[1] = %d\n", fd_list[1]);
    }
    else
    {
      debug_print("fd_list is full\n");
      close(fd);
    }
  }
  close(sock);
}

int main(int argc, char **argv)
{

//if have no any argument input,them warnning
  if (argc == 1)
  {
    printf("Please input the port number\n");
    //show the usage in command line
    printf("1. The first argument is the port number,it is necessary\n");
    printf("2. The second argument is the ip address,it is optional\n");
    printf("3. You can use it like this:\"p2pgate 8888\",in this case "
           "progame will have no debugging information to display,"
           "and if you set the second like this:\"p2pgate 8888 debug\","
           "then you will see the debugging information\n");
    return 0;
  }
  //get port from command line
  int port = atoi(argv[1]);

  //check argc contains "debug" or not
  if (argc == 3 && strcmp(argv[2], "debug") == 0)
  {
    printf("debug mode\n");
    set_debug_on();
  }
  else
  {
    printf("release mode\n");
    set_debug_off();
  }
  printf("Press Ctrl+C to exit\n");

  //初始化fd_list
  init_fd_list();

  //5.when accept a client,create a new thread to handle it
  pthread_t id0, id1;
  int fd_list_idx0 = 0;
  int fd_list_idx1 = 1;
  pthread_create(&id0, NULL, thread_rev, (void *)&fd_list_idx0);
  pthread_create(&id1, NULL, thread_rev, (void *)&fd_list_idx1);
  pthread_detach(id0);
  pthread_detach(id1);
  debug_print("create thread success\n");
  

  int sock = INVALID_FD;
  int init_flag = tcp_socket_sever_init("0.0.0.0", port, &sock);
  if (init_flag != 0)
  {
    debug_print("tcp_sever_loop error.\n");
    debug_print("Please check whether the port is used.\n");
    return init_flag;
  }

  return tcp_sever_loop(sock);
  ;
}
