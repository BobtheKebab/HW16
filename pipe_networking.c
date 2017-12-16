#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  printf("boi\n");
  if(mkfifo("WKP", 0600)<0) printf("%s\n", strerror(errno));
  printf("opening WKP\n");
  int srv_pipe = open("WKP", O_RDONLY, 0);
  char name[HANDSHAKE_BUFFER_SIZE];
  printf("About to read\n");
  read(srv_pipe, name, sizeof(name));
  printf("%s\n", name);
  close(srv_pipe);
  remove("WKP");
  int clt_pipe = open(name, O_WRONLY, 0);
  write(clt_pipe, name, sizeof(name));
  *to_client = clt_pipe;
  return clt_pipe;
}


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server)  {

  char name[HANDSHAKE_BUFFER_SIZE];
  sprintf(name, "%d", getpid());
  mkfifo(name, 0600);

  int srv_pipe = open("WKP", O_WRONLY, 0);
  write(srv_pipe, name, sizeof(name));

  int clt_pipe = open(name, O_RDONLY , 0);
  
  char temp[HANDSHAKE_BUFFER_SIZE];
  read(clt_pipe, temp, sizeof(temp));
  if (!strcmp(name, temp)) {
	*to_server = srv_pipe;
	return clt_pipe;
  }

}
