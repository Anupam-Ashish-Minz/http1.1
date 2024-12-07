#include "utils.h"
#include "thread_task_queue.h"

void test_thread_init() {
	thread_task_queue_t *queue = thread_task_queue_init(4);
	if (queue == NULL) {
		fprintf(stderr, "Queue could not be initialized\n");
		exit(-1);
	}
}

void test_thread_task_queue_add_items() {
	thread_task_queue_t *queue = thread_task_queue_init(4);
	for (int i=0; i<queue->size; i++) {
		ASSERT_EQ(0, thread_task_queue_add(queue, NULL, NULL));
	}
	ASSERT_EQ(-1, thread_task_queue_add(queue, NULL, NULL));
	ASSERT_EQ(-1, thread_task_queue_add(queue, NULL, NULL));
}

void test_thread_task_queue_add_overflow() {
	thread_task_queue_t *queue = thread_task_queue_init(4);
	for (int i=0; i<queue->size * 2; i++) {
		if (i < queue->size) {
			ASSERT_EQ(0, thread_task_queue_add(queue, NULL, NULL));
		} else {
			ASSERT_EQ(-1, thread_task_queue_add(queue, NULL, NULL));
		}
	}
}

void test_thread_task_queue_overflow2() {
	thread_task_queue_t *queue = thread_task_queue_init(4);
	ASSERT_EQ(0, thread_task_queue_add(queue, NULL, NULL));
	ASSERT_EQ(0, thread_task_queue_add(queue, NULL, NULL));
	thread_task_queue_pull(queue);
	ASSERT_EQ(0, thread_task_queue_add(queue, NULL, NULL));
	ASSERT_EQ(0, thread_task_queue_add(queue, NULL, NULL));
	ASSERT_EQ(0, thread_task_queue_add(queue, NULL, NULL));
	ASSERT_EQ(-1, thread_task_queue_add(queue, NULL, NULL));
}

void test_thread_task_queue_pull() {
	thread_task_queue_t *queue = thread_task_queue_init(4);
	thread_task_queue_add(queue, NULL, (void *)1234);
	thread_task_t *task = thread_task_queue_pull(queue);
	ASSERT_EQ(1234, (long int)task->args);
}

void test_thread_task_queue_pull_muliple() {
	thread_task_queue_t *queue = thread_task_queue_init(4);
	thread_task_queue_add(queue, NULL, (void *)1234);
	thread_task_queue_add(queue, NULL, (void *)3456);
	thread_task_t *task = thread_task_queue_pull(queue);
	ASSERT_EQ(1234, (long int)task->args);
	task = thread_task_queue_pull(queue);
	ASSERT_EQ(3456, (long int)task->args);
}


void test_thread_task_queue_pull_null() {
	thread_task_queue_t *queue = thread_task_queue_init(4);
	thread_task_t *task = thread_task_queue_pull(queue);
	if (task != NULL) {
		fprintf(stderr, "thread task queue pull not implemented correctly error");
		exit(-1);
	}
}


int main() {
	test_thread_init();
	test_thread_task_queue_add_items();
	test_thread_task_queue_add_overflow();
	test_thread_task_queue_overflow2();
	test_thread_task_queue_pull();
	test_thread_task_queue_pull_muliple();
	test_thread_task_queue_pull_null();
	return 0;
}
