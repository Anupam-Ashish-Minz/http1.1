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
		queue->front = 0;
		queue->back = 0;
		queue->tasks[queue->back] = task;
		++queue->back;
		return 0;
	}
	if (queue->front == ((queue->back) % queue->size)) {
		fprintf(stderr, "Task Queue Error: Failed to add new values to queue, queue is full\n"
			"Queue front: %d, Queue back: %d, Queue size: %d\n",
			queue->front, queue->back, queue->size);
		return -1;
	}
	if (queue->front <= queue->back) {
		queue->tasks[queue->back] = task;
		++queue->back;
		if (queue->back >= queue->size) {
			queue->back = queue->back % queue->size;
		}
		return 0;
	}
	if (queue->front > queue->back) {
		queue->tasks[queue->back] = task;
		++queue->back;
		if (queue->front == ((queue->back - 1) % queue->size)) {
			fprintf(stderr, "Task Queue Error: Failed to add new values to queue, queue is full\n"
				"Queue front: %d, Queue back: %d, Queue size: %d\n",
				queue->front, queue->back, queue->size);
			return -1;
		}
		return 0;
	}
	return -1;
}

thread_task_t *thread_task_queue_pull(thread_task_queue_t *queue) {
	if (queue->front >= queue->size) {
		queue->front = 0;
	}
	if (queue->front == queue->back) {
		++queue->back;
		return NULL;
	}
	thread_task_t *task = queue->tasks[queue->front];
	++queue->front;
	return task;
}

