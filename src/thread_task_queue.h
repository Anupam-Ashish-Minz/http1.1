#ifndef _THREAD_TASK_QUEUE_H
#define _THREAD_TASK_QUEUE_H

#define THREAD_TASK_QUEUE_SIZE_MAX 4

typedef struct ThreadTask {
	void (*callback) (void *args);
	void *args;
} thread_task_t;

typedef struct ThreadTaskQueue {
	thread_task_t **tasks;
	int front;
	int back;
	int size;
} thread_task_queue_t;

thread_task_queue_t *thread_task_queue_init(int size);

int thread_task_queue_add(thread_task_queue_t *queue, thread_task_t *task);

thread_task_t *thread_task_queue_pull(thread_task_queue_t *queue);

#endif
