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
	ASSERT_EQ(0, thread_task_queue_add(queue, task));
	ASSERT_EQ(0, thread_task_queue_add(queue, task));
	ASSERT_EQ(0, thread_task_queue_add(queue, task));
	ASSERT_EQ(0, thread_task_queue_add(queue, task));
	ASSERT_EQ(0, thread_task_queue_add(queue, task));
}

int main() {
	test_thread_init();
	test_thread_task_queue_add_items();
	return 0;
}
