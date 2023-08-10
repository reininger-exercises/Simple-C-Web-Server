// A simple http server.

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>

#define DEFAULT_PORT 5005

int main(int argc, char *args[]) {
	// Open TCP socket to listen for connections

	// create socket
	// for protocol argument, 0 means default (tcp for SOCK_STREAM)
	int connectionFd = socket(PF_INET, SOCK_STREAM, 0);
	if (connectionFd == -1) {
		puts("Unable to create connection socket, program will terminate.");
		exit(1);
	}

	printf("connection socket fd: %d\n", connectionFd);
	// bind socket
	ushort port = DEFAULT_PORT;
	struct sockaddr_in address = {
		.sin_family = AF_INET,
		.sin_port = htons(port),
		.sin_addr.s_addr = htonl(INADDR_ANY)
	};

	struct sockaddr* sockAddress = (struct sockaddr*)&address;
	int status = bind(connectionFd, sockAddress, sizeof(address));
	if (status == -1) {
		puts("Unable to bind connection socket, program will terminate.");
		exit(1);
	}
	
	// listen
	status = listen(connectionFd, 0);
	if (status == -1) {
		puts("Unable to listen on connection socket, program will terminate.");
		exit(1);
	}


	// Once a connection is made:

		// read from the socket

		// handle the message

		// close the socket
}

