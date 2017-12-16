#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  if(mkfifo("WKP", 0600)<0) printf("%s\n", strerror(errno));

  PRINT("Opening WKP");
  int from_client = open("WKP", O_RDONLY, 0);

  char name[HANDSHAKE_BUFFER_SIZE];
  PRINT("About to read");
  read(from_client, name, sizeof(name));
  printf("[server] received: %s\n", name);

  remove("WKP");

  *to_client = open(name, O_WRONLY, 0);
  write(*to_client, ACK, sizeof(ACK));
  printf("[server] sent: %s\n", ACK);

  read(from_client, name, sizeof(name));
  if (!strcmp(ACK, name)) {
    return from_client;
  }
  return -1;
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
  PRINT("Creating private FIFO");
  mkfifo(name, 0600);

  PRINT("Connecting to server");
  *to_server = open("WKP", O_WRONLY, 0);
  write(*to_server, name, sizeof(name));
  printf("[client] sent: %s\n", name);

  int from_server = open(name, O_RDONLY , 0);

  char temp[HANDSHAKE_BUFFER_SIZE];
  read(from_server, temp, sizeof(temp));
  printf("[client] received: %s\n", temp);

  if (!strcmp(ACK, temp)) {
	remove(name);
	write(*to_server, ACK, sizeof(ACK));
	return from_server;
  }
  return -1;
}
