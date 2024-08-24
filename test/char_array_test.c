#include "char_array.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if CHARARR == 1
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

#elif CHARARR == 2

void test_push_1_item() {
	struct CharArray *vec = NULL;
	struct CharArray c;
	unsigned int vec_len = 0;
	vec = push_char_array(vec, &vec_len, c);
	ASSERT_EQ(vec_len, 1);
}

void test_push_101_item() {
	struct CharArray *vec = NULL;
	struct CharArray c;
	unsigned int vec_len = 0;
	for (int i = 0; i < 102; i++) {
		vec = push_char_array(vec, &vec_len, c);
	}
	ASSERT_EQ(vec_len, 102);
}

void test_inner_str() {
	struct CharArray *vec = NULL;
	struct CharArray c;
	char *str = "hello world";
	c.line = str;
	c.size = sizeof(str);
	unsigned int vec_len = 0;
	vec = push_char_array(vec, &vec_len, c);
	ASSERT_EQ_STR(vec[0].line, str);
}

#endif

void test_split_line() {
	char *lines = "line number 1\r\n"
		"line number 2";
#if CHARARR == 1
	struct VecCharArray vec = split_lines(lines, strlen(lines));
	ASSERT_EQ_STR(vec.arr[0]->line, "line number 1");
	ASSERT_EQ_STR(vec.arr[1]->line, "line number 2");
#elif CHARARR == 2
	struct CharArray *vec = split_lines(lines, strlen(lines));
	ASSERT_EQ_STR(vec[0].line, "line number 1");
	ASSERT_EQ_STR(vec[1].line, "line number 2");
#endif
}

void test_split_black_line() {
	char *lines = "line number 1\r\n\r\n"
		"line number 2";
#if CHARARR == 1
	struct VecCharArray vec = split_lines(lines, strlen(lines));
	ASSERT_EQ_STR(vec.arr[0]->line, "line number 1");
	ASSERT_EQ_STR(vec.arr[1]->line, "");
	ASSERT_EQ_STR(vec.arr[2]->line, "line number 2");
#elif CHARARR == 2
	struct CharArray *vec = split_lines(lines, strlen(lines));
	ASSERT_EQ_STR(vec[0].line, "line number 1");
	ASSERT_EQ_STR(vec[1].line, "");
	ASSERT_EQ_STR(vec[2].line, "line number 2");
#endif
}

void test_split_multiple_lines() {
	char *lines = "line number 1\r\n"
		"line number 2\r\n\r\n"
		"line number 3";
#if CHARARR == 1
	struct VecCharArray vec = split_lines(lines, strlen(lines));
	ASSERT_EQ_STR(vec.arr[0]->line, "line number 1");
	ASSERT_EQ_STR(vec.arr[1]->line, "line number 2");
	ASSERT_EQ_STR(vec.arr[2]->line, "");
	ASSERT_EQ_STR(vec.arr[3]->line, "line number 3");
#elif CHARARR == 2
	struct CharArray *vec = split_lines(lines, strlen(lines));
	ASSERT_EQ_STR(vec[0].line, "line number 1");
	ASSERT_EQ_STR(vec[1].line, "line number 2");
	ASSERT_EQ_STR(vec[2].line, "");
	ASSERT_EQ_STR(vec[3].line, "line number 3");
#endif
}


int main(int argc, char **argv) {
	test_push_1_item();
	test_push_101_item();
	test_inner_str();

	test_split_line();
	test_split_black_line();
	test_split_multiple_lines();

	return 0;
}
