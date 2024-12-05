#include "thread_task_queue.h"
#include <stdio.h>
#include <stdlib.h>

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
		fprintf(stderr, "Task Queue Error: Failed to add new values to queue, queue is full\n"
	  "Queue front: %d, Queue back: %d, Queue size: %d\n", queue->front, queue->back, THREAD_TASK_QUEUE_SIZE_MAX
	  );
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

