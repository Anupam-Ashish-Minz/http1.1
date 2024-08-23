#include "char_array.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_push_1_item() {
	struct VecCharArray vec = new_vec_char_array();
	struct CharArray *arr =
		(struct CharArray *)malloc(sizeof(struct CharArray));

	push_char_array(&vec, arr);
	ASSERT_EQ(vec.len, 1);
	ASSERT_EQ(vec.max_len, 10);
}

void test_push_101_item() {
	struct VecCharArray vec = new_vec_char_array();
	struct CharArray *arr =
		(struct CharArray *)malloc(sizeof(struct CharArray));

	for (int i = 0; i < 102; i++) {
		push_char_array(&vec, arr);
	}
	ASSERT_EQ(vec.len, 102);
	ASSERT_EQ(vec.max_len, 110);
}

void test_inner_str() {
	struct VecCharArray vec = new_vec_char_array();
	struct CharArray *arr =
		(struct CharArray *)malloc(sizeof(struct CharArray));
	char *str = "hello world";
	arr->line = str;
	arr->size = sizeof(str);
	push_char_array(&vec, arr);
	ASSERT_EQ_STR(vec.arr[0]->line, str);
}

int main(int argc, char **argv) {
	test_push_1_item();
	test_push_101_item();
	test_inner_str();

	return 0;
}
