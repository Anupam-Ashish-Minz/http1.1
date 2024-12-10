#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "thread_task_queue.h"
#include "thread_pool.h"

void *thread_process_job(void *args) {
	thread_pool_t *pool = (thread_pool_t *)args;
	while(true) {
		pthread_mutex_lock(&pool->lock);
		thread_task_t *task = thread_task_queue_pull(pool->queue);
		pthread_mutex_unlock(&pool->lock);
		if (task == NULL) {
			return NULL;
		}
		task->callback(task->args);
	}
}

void *thread_pool_add_job(thread_pool_t *pool, void *(*callback) (void *args), void *args) {
	pthread_mutex_lock(&pool->lock);
	thread_task_queue_add(pool->queue, callback, args);
	pthread_mutex_unlock(&pool->lock);
	return NULL;
}

thread_pool_t *thread_pool_init(int thread_count) {
	thread_pool_t *pool = (thread_pool_t *)malloc(sizeof(thread_pool_t));
	pool->queue = thread_task_queue_init(128);
	return pool;
}

void *thread_pool_process_jobs(thread_pool_t *pool) {
	for (int i=0; i<THREAD_COUNT; i++) {
		pthread_create(&pool->thread_ids[i], NULL, thread_process_job, (void *)pool);
		pthread_detach(pool->thread_ids[i]);
	}
	return NULL;
}
