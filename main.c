// A simple http server.

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFSIZE 8 * 1024
#define DEFAULT_PORT 5005
#define ERRBUFSIZE 1024

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;
typedef unsigned int uint;

void terminate(char* msg) {
	printf("Error: %s: program will terminate.", msg);
	exit(1);
}

int main(int argc, char *args[]) {
	int connectionSocket;
	int commSocket;
	int bufSize = BUFSIZE;

	if ((connectionSocket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		terminate("Unable to create connection socket");

	printf("connection socket fd: %d\n", connectionSocket);

	ushort port = DEFAULT_PORT;
	sockaddr_in address = {
		.sin_family = AF_INET,
		.sin_port = htons(port),
		.sin_addr.s_addr = htonl(INADDR_ANY)
	};

	sockaddr* connectionAddress = (sockaddr*) &address;
	if (bind(connectionSocket, connectionAddress, sizeof(address)) < 0)
		terminate("Unable to bind connection socket");
	
	if(listen(connectionSocket, 0) < 0)
		terminate("Unable to listen on connection socket");

	while (true) {
		sockaddr clientAddr;
		uint clientAddrSize = sizeof(clientAddr);
		int recvMsgSize;
		char buf[bufSize];
		char errBuf[ERRBUFSIZE];
		char *path = "msg.html";
		FILE *file;

		if ((commSocket = accept(connectionSocket, &clientAddr, &clientAddrSize)) < 0)
			terminate("Unable to accept connection");

		memset(buf, 0, bufSize);
		if ((recvMsgSize = recv(commSocket, buf, bufSize, 0)) < 0)
			terminate("Failed to read from socket");

		printf("Message received from client:\n\n%s", buf);

		if ((file = fopen(path, "r")) == 0) {
			sprintf(errBuf, "Could not open %s", path);
			terminate(errBuf);
		}

		// load file into buf
		memset(buf, 0, bufSize);
		fseek(file, 0, SEEK_END);
		long fsize = ftell(file);
		fseek(file, 0, SEEK_SET);
		fread(buf, fsize, 1, file);
		fclose(file);
		buf[fsize] = 0;

		int msgSize = 0;
		char msg[bufSize];

		memset(msg, 0, bufSize);
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
}

