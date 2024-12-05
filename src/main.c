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

#define THREAD_TASK_QUEUE_SIZE_MAX 1024

typedef struct ThreadTask {
	void (*callback) (void *args);
	void *args;
} thread_task_t;

typedef struct ThreadTaskQueue {
	thread_task_t *tasks;
	int front;
	int back;
} thread_task_queue_t;

thread_task_queue_t *thread_task_queue_init() {
	thread_task_queue_t *queue = (thread_task_queue_t *)malloc(sizeof(thread_task_queue_t));
	queue->tasks = (thread_task_t *)malloc(sizeof(thread_task_t) * THREAD_TASK_QUEUE_SIZE_MAX);
	queue->front = -1;
	queue->back = -1;
	return queue;
}

int thread_task_queue_add(thread_task_queue_t *queue, thread_task_t *task) {
	if (queue->front == -1 && queue->back == -1) {
		queue->front = 0;
		queue->back = 0;
		if (THREAD_TASK_QUEUE_SIZE_MAX <= queue->back) {
			queue->front = -1;
			queue->back = -1;
			return -1;
		}
		queue->tasks[queue->back] = *task;
		++queue->back;
		return 0;
	}
	if (queue->front < queue->back && queue->back < THREAD_TASK_QUEUE_SIZE_MAX) {
		queue->tasks[queue->back] = *task;
		++queue->back;
		return 0;
	}
	if (queue->front < queue->back && queue->back >= THREAD_TASK_QUEUE_SIZE_MAX) {
		queue->back = 0;
	}
	if (queue->front == queue->back) {
		fprintf(stderr, "Task Queue Error: Failed to add new values to queue, queue is full");
		return -1;
	}
	if (queue->front > queue->back) {
		queue->tasks[queue->back] = *task;
		++queue->back;
	}
	return 0;
}

thread_task_t *thread_task_queue_pull(thread_task_queue_t *queue) {
	if (queue->front >= THREAD_TASK_QUEUE_SIZE_MAX) {
		queue->front = 0;
	}
	if (queue->front == queue->back) {
		++queue->back;
		return NULL;
	}
	thread_task_t *task = &queue->tasks[queue->front];
	++queue->front;
	return task;
}

void *process_req(void *args) {
	int *server_fd = (int *)args;
	int client;
	if ((client = accept(*server_fd, NULL, NULL)) < 0) {
		perror("accept");
	}

	const char *res = "HTTP/1.1 200 OK\r\n\
Content-Length: 4\r\n\r\n\
hey\n";

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


	while (1) {
		process_req((void *)&server);
	}

	close(client);
	close(server);

	return 0;
}
