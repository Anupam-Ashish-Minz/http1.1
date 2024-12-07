#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#define THREAD_COUNT 8

typedef struct ThreadPool {
	pthread_mutex_t lock;
	thread_task_queue_t *queue;
} thread_pool_t;

void *thread_pool_process_job(void *args);
void *thread_pool_add_job(thread_pool_t *pool, void *args);
thread_pool_t *thread_pool_init(int thread_count);

#endif
