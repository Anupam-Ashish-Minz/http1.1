#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "char_array.h"
#include "http_parser.h"
#include "thread_task_queue.h"

#define PORT 6262
#define MSBUF_MXLEN 1048576
#define MAX_THREADS 16

void *process_req(void *args) {
	int client_fd = *(int *)args;
	const char *res = "HTTP/1.1 200 OK\r\n\
Content-Length: 4\r\n\r\n\
hey\n";

	write(client_fd, res, strlen(res));

	return NULL;
}

int main() {
	int server, client;
	struct sockaddr_in addr;
	socklen_t addrlen;
	int opt = 1;

	if ((server = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		return -1;
	}

	if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) != 0) {
		perror("socket option");
	}

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);

	addrlen = sizeof(addr);

	if (bind(server, (struct sockaddr *)&addr, addrlen) < 0) {
		perror("bind");
		return -1;
	}
	printf("Listering http://localhost:%d\n", PORT);

	if (listen(server, 3) < 0) {
		perror("listen");
		return -1;
	}

	const char *res = "HTTP/1.1 200 OK\r\n\
Content-Length: 3\r\n\r\n\
hey";

	while (1) {
		if ((client = accept(server, NULL, NULL)) < 0) {
			perror("accept");
		}
		process_req((void *)&client);
	}

	close(client);
	close(server);

	return 0;
}
