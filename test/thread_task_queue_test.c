#include "utils.h"
#include "thread_task_queue.h"

void test_thread_init() {
	thread_task_queue_t *queue = thread_task_queue_init();
	if (queue == NULL) {
		fprintf(stderr, "Queue could not be initialized\n");
		exit(-1);
	}
}

void test_thread_task_queue_add_items() {
	thread_task_queue_t *queue = thread_task_queue_init();
	thread_task_t *task = (thread_task_t *)malloc(sizeof(thread_task_t));
	task->callback = NULL;
	task->args = NULL;
	for (int i=0; i<THREAD_TASK_QUEUE_SIZE_MAX; i++) {
		ASSERT_EQ(0, thread_task_queue_add(queue, task));
	}
	ASSERT_EQ(-1, thread_task_queue_add(queue, task));
	ASSERT_EQ(-1, thread_task_queue_add(queue, task));
}

void test_thread_task_queue_add_overflow() {
	thread_task_queue_t *queue = thread_task_queue_init();
	thread_task_t *task = (thread_task_t *)malloc(sizeof(thread_task_t));
	task->callback = NULL;
	task->args = NULL;
	for (int i=0; i<THREAD_TASK_QUEUE_SIZE_MAX * 2; i++) {
		if (i < THREAD_TASK_QUEUE_SIZE_MAX) {
			ASSERT_EQ(0, thread_task_queue_add(queue, task));
		} else {
			ASSERT_EQ(-1, thread_task_queue_add(queue, task));
		}
	}
}

void test_thread_task_queue_overflow2() {
	thread_task_queue_t *queue = thread_task_queue_init();
	thread_task_t *task = (thread_task_t *)malloc(sizeof(thread_task_t));
	task->callback = NULL;
	task->args = NULL;
	ASSERT_EQ(0, thread_task_queue_add(queue, task));
	ASSERT_EQ(0, thread_task_queue_add(queue, task));
	thread_task_queue_pull(queue);
	ASSERT_EQ(0, thread_task_queue_add(queue, task));
	ASSERT_EQ(0, thread_task_queue_add(queue, task));
	ASSERT_EQ(0, thread_task_queue_add(queue, task));
	ASSERT_EQ(-1, thread_task_queue_add(queue, task));
}

int main() {
	test_thread_init();
	test_thread_task_queue_add_items();
	test_thread_task_queue_add_overflow();
	// test_thread_task_queue_overflow2();
	return 0;
}
