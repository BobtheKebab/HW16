#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  return 0;
}


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server)  {

  char name[25];
  sprintf(name, "%d", getpid());
  mkfifo(name, 0644);
  int clt_pipe = open(name, O_RDONLY);

  int srv_pipe = open("WKP", O_WRONLY);
  write(srv_pipe, name, sizeof(name));

  char temp[25];
  read(clt_pipe, temp, sizeof(temp));
  if (!strcmp(name, temp)) {
    close(srv_pipe);
  }
  
  return 0;
  
}
