#include "pipe_networking.h"


int main() {

	int to_server;
	int from_server;
	char buffer[BUFFER_SIZE];

	from_server = client_handshake( &to_server );

	while(1){
		printf("Type something in: ");
		fgets(buffer, BUFFER_SIZE, stdin);
		*strchr(buffer, '\n') = '\0';
		write(to_server, buffer, BUFFER_SIZE);
		printf("[client] sent: %s\n", buffer);
		if(!strcmp(buffer, "exit")) exit(0);

		read(from_server, buffer, BUFFER_SIZE);
		printf("[client] received: %s\n", buffer);
	}
}
