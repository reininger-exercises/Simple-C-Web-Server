// A simple http server.

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>

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
	//int port = 
	//sockaddr_in address = { .sin_family = AF_INET, .sin_port = DEFAULT_PORT, .

	// listen


	// Once a connection is made:

		// read from the socket

		// handle the message

		// close the socket
}

