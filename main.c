// A simple http server.

#include <sys/socket.h>

#define TCP 6

int main(int argc, char[] *args) {
	// Open TCP socket to listen for connections
	int connectionFd = socket(PF_INET, SOCK_STREAM, TCP);

	// Once a connection is made:

		// read from the socket

		// handle the message

		// close the socket
}

