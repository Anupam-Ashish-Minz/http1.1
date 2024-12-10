#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#define THREAD_COUNT 8

typedef struct ThreadPool {
	pthread_mutex_t lock;
	thread_task_queue_t *queue;
	pthread_t thread_ids[THREAD_COUNT];
} thread_pool_t;

void *thread_pool_add_job(thread_pool_t *pool, void *(*callback) (void *args), void *args);
thread_pool_t *thread_pool_init(int thread_count);
void *thread_pool_process_jobs(thread_pool_t *pool);

#endif
