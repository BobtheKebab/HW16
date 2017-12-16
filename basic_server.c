#include "pipe_networking.h"


int main() {

	int to_client;
	int from_client;
	char buffer[BUFFER_SIZE];

	while(1){
		from_client = server_handshake( &to_client );
		while(1){
			read(from_client, buffer, BUFFER_SIZE);
			printf("[server] received: %s\n", buffer);

			if(!strcmp(buffer, "exit")){
				PRINT("[server] client disconnected");
				close(to_client);
				close(from_client);
				break;
			}

			int i;
			for(i = 0; i < strlen(buffer); i++)
				buffer[i] = (buffer[i] - 20) % 47 + 33;

			write(to_client, buffer, BUFFER_SIZE);
			printf("[server] sent: %s\n", buffer);
		}
	}
}
