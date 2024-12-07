#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include "thread_task_queue.h"

#define THREAD_COUNT 8

typedef struct ThreadPool {
	pthread_mutex_t lock;
	thread_task_queue_t *queue;
} thread_pool_t;

void *thread_pool_process_job(void *args) {
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

void *thread_pool_add_job(thread_pool_t *pool, void *args) {
	pthread_mutex_lock(&pool->lock);
	thread_task_t *task = thread_task_queue_pull(pool->queue);
	pthread_mutex_unlock(&pool->lock);
	task->callback(task->args);
	return NULL;
}

void thread_pool_init() {
	thread_pool_t *pool = (thread_pool_t *)malloc(sizeof(thread_pool_t));
	pool->queue = thread_task_queue_init(128);
	pthread_t thread_ids[THREAD_COUNT];
	for (int i=0; i<THREAD_COUNT; i++) {
		pthread_create(&thread_ids[i], NULL, thread_pool_process_job, (void *)pool);
	}
	for (int i=0; i<THREAD_COUNT; i++) {
		pthread_join(thread_ids[i], NULL);
	}
}
