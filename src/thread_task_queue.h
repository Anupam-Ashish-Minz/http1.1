#ifndef _THREAD_TASK_QUEUE_H
#define _THREAD_TASK_QUEUE_H

typedef struct ThreadTask {
	void *(*callback) (void *args);
	void *args;
} thread_task_t;

typedef struct ThreadTaskQueue {
	thread_task_t **tasks;
	int front;
	int back;
	int size;
} thread_task_queue_t;

thread_task_queue_t *thread_task_queue_init(int size);

int thread_task_queue_add(thread_task_queue_t *queue, void *(*callback)(void *args), void *args);

thread_task_t *thread_task_queue_pull(thread_task_queue_t *queue);

#endif
