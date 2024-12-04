#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "char_array.h"
#include "http_parser.h"

#define PORT 6262
#define MSBUF_MXLEN 1048576
#define MAX_THREADS 16

pthread_mutex_t resource;

void *do_task() {
	pthread_mutex_lock(&resource);
	printf("doing something...\n");
	sleep(3);
	printf("done\n");
	pthread_mutex_unlock(&resource);
	return NULL;
}


void *process_req(void *args) {
	int *server_fd = (int *)args;
	int client;
	if ((client = accept(*server_fd, NULL, NULL)) < 0) {
		perror("accept");
	}

	const char *res = "HTTP/1.1 200 OK\r\n\
Content-Length: 3\r\n\r\n\
hey";

	write(client, res, strlen(res));

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

	pthread_t threads[MAX_THREADS];
	pthread_mutex_init(&resource, NULL);
	pthread_create(&threads[0], NULL, &do_task, NULL);
	pthread_create(&threads[1], NULL, &do_task, NULL);


	while (1) {
		process_req((void *)&server);
	}

	close(client);
	close(server);
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);

	return 0;
}
