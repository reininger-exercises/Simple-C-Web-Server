// A simple http server.

#include <sys/socket.h>

int main(int argc, char[] *args) {
	// Open TCP socket to listen for connections

	// for protocol argument, 0 means default (tcp for SOCK_STREAM)
	int connectionFd = socket(PF_INET, SOCK_STREAM, 0);
	if (connectionFd == -1) {
		exit(1);
	}

	// Once a connection is made:

		// read from the socket

		// handle the message

		// close the socket
}

