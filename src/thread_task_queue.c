#include "thread_task_queue.h"
#include <stdio.h>
#include <stdlib.h>

thread_task_queue_t *thread_task_queue_init(int size) {
	thread_task_queue_t *queue = (thread_task_queue_t *)malloc(sizeof(thread_task_queue_t));
	queue->size = size;
	queue->tasks = (thread_task_t **)malloc(sizeof(thread_task_t) * queue->size);
	queue->front = -1;
	queue->back = -1;
	return queue;
}

int thread_task_queue_add(thread_task_queue_t *queue, void *(*callback)(void *args), void *args) {
	thread_task_t *task = (thread_task_t *)malloc(sizeof(thread_task_t));
	task->callback = callback;
	task->args = args;
	if (queue->front == -1 && queue->back == -1) {
		queue->back = 0;
		queue->front = 0;
		queue->tasks[queue->back] = task;
		return 0;
	}
	if ((queue->back + 1) % queue->size == queue->front) {
		fprintf(stderr, "Queue is Full\n");
		return -1;
	} else {
		queue->back = (queue->back + 1) % queue->size;
		queue->tasks[queue->back] = task;
		return 0;
	}
}

thread_task_t *thread_task_queue_pull(thread_task_queue_t *queue) {
	if (queue->front == -1 && queue->back == -1) {
		return NULL;
	}
	if (queue->front == queue->back) {
		thread_task_t *task = queue->tasks[queue->front];
		queue->front = -1;
		queue->back = -1;
		return task;
	} else {
		thread_task_t *task = queue->tasks[queue->front];
		queue->front = (queue->front + 1) % queue->size;
		return task;
	}
}
