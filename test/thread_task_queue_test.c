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
	thread_task_t *task = (thread_task_t *)malloc(sizeof(thread_task_t));
	task->callback = NULL;
	task->args = NULL;
	for (int i=0; i<queue->size; i++) {
		ASSERT_EQ(0, thread_task_queue_add(queue, task));
	}
	ASSERT_EQ(-1, thread_task_queue_add(queue, task));
	ASSERT_EQ(-1, thread_task_queue_add(queue, task));
}

void test_thread_task_queue_add_overflow() {
	thread_task_queue_t *queue = thread_task_queue_init(4);
	thread_task_t *task = (thread_task_t *)malloc(sizeof(thread_task_t));
	task->callback = NULL;
	task->args = NULL;
	for (int i=0; i<queue->size * 2; i++) {
		if (i < queue->size) {
			ASSERT_EQ(0, thread_task_queue_add(queue, task));
		} else {
			ASSERT_EQ(-1, thread_task_queue_add(queue, task));
		}
	}
}

void test_thread_task_queue_overflow2() {
	thread_task_queue_t *queue = thread_task_queue_init(4);
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

void test_thread_task_queue_pull() {
	thread_task_queue_t *queue = thread_task_queue_init(4);
	thread_task_t *task_orig = (thread_task_t *)malloc(sizeof(thread_task_t));
	task_orig->callback = NULL;
	task_orig->args = NULL;
	ASSERT_EQ(0, thread_task_queue_add(queue, task_orig));
	thread_task_t *task_ret = thread_task_queue_pull(queue);
	ASSERT_EQ(task_orig, task_ret);
	task_ret = thread_task_queue_pull(queue);
	ASSERT_EQ(NULL, task_ret);
}

void test_thread_task_queue_pull_muliple() {
	thread_task_queue_t *queue = thread_task_queue_init(4);
	thread_task_t *task1 = (thread_task_t *)malloc(sizeof(thread_task_t));
	task1->callback = NULL;
	task1->args = NULL;
	thread_task_t *task2 = (thread_task_t *)malloc(sizeof(thread_task_t));
	task2->callback = NULL;
	task2->args = NULL;

	ASSERT_EQ(0, thread_task_queue_add(queue, task1));
	ASSERT_EQ(0, thread_task_queue_add(queue, task2));

	thread_task_t *task_ret = thread_task_queue_pull(queue);
	ASSERT_EQ(task1, task_ret);
	task_ret = thread_task_queue_pull(queue);
	ASSERT_EQ(task2, task_ret);
}


int main() {
	test_thread_init();
	test_thread_task_queue_add_items();
	test_thread_task_queue_add_overflow();
	test_thread_task_queue_overflow2();
	test_thread_task_queue_pull();
	test_thread_task_queue_pull_muliple();
	return 0;
}
