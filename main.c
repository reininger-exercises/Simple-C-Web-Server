// A simple http server.

#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

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

	// connect
	while (1) {
		struct sockaddr clientAddr;

		if (status == -1) {
			puts("Unable to connect, program will terminate.");
			exit(1);
		}

		unsigned int clientAddrSize = sizeof(clientAddr);
		int commSocket = accept(connectionFd, &clientAddr, &clientAddrSize);
		if (commSocket == -1) {
			puts("Unable to accept connection, program will terminate.");
			exit(1);
		}

		char buf[1024 * 8];
		memset(buf, 0, 1024 * 8);
		int recvMsgSize = recv(commSocket, buf, 1024 * 8, 0);
		if (recvMsgSize < 0) {
			puts("Failed to read from socket. Connection will terminate.");
			continue;
		}
		puts("Message received from client:");
		printf("%s", buf);

		char *path = "msg.html";
		FILE *file = fopen(path, "r");
		if (!file) {
			printf("Could not open %s. Connection will terminate.\n", path);
			continue;
		}

		memset(buf, 0, 1024 * 8);
		fseek(file, 0, SEEK_END);
		long fsize = ftell(file);
		fseek(file, 0, SEEK_SET);
		fread(buf, fsize, 1, file);
		fclose(file);
		buf[fsize] = 0;

		int msgSize = 0;

		char msg[1024 * 8];
		memset(msg, 0, 1024 * 8);
		msgSize += sprintf(msg + msgSize, "HTTP/1.1 200 OK\r\n");
		msgSize += sprintf(msg + msgSize, "content-length: %ld\r\n", fsize);
		msgSize += sprintf(msg + msgSize, "\r\n");
		msgSize += sprintf(msg + msgSize, "%s", buf);
		msg[msgSize] = 0;

		printf("Message to send:\n%s", msg);
		
		int sent = send(commSocket, msg, msgSize, 0);
		printf("Number of bytes sent: %d\n", sent);
		close(commSocket);
	}

	// Once a connection is made:

		// read from the socket

		// handle the message

		// close the socket
}

