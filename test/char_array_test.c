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
	free(vec);
}

void test_push_101_item() {
	struct CharArray *vec = NULL;
	struct CharArray c;
	unsigned int vec_len = 0;
	for (int i = 0; i < 102; i++) {
		vec = push_char_array(vec, &vec_len, c);
	}
	ASSERT_EQ(vec_len, 102);
	free(vec);
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
	free(vec);
}

void test_empty_str() {
	struct CharArray *vec = NULL;
	struct CharArray c;
	char *str = "";
	c.line = str;
	c.size = sizeof(str);
	unsigned int vec_len = 0;
	vec = push_char_array(vec, &vec_len, c);
	ASSERT_EQ_STR(vec[0].line, str);
	free(vec);
}

void test_multi_str_insert() {
	struct CharArray *vec = NULL;
	struct CharArray c;
	char *str = "hey";
	c.line = str;
	c.size = sizeof(str);
	unsigned int vec_len = 0;
	vec = push_char_array(vec, &vec_len, c);

	struct CharArray d;
	char *str2 = "";
	d.line = str2;
	d.size = sizeof(str2);
	vec = push_char_array(vec, &vec_len, d);
	ASSERT_EQ_STR(vec[0].line, str);
	ASSERT_EQ_STR(vec[1].line, str2);
	free(vec);
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
	free(vec);
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
	free(vec);
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
	ASSERT_EQ(vec[0].size, 13);
	ASSERT_EQ(vec[1].size, 13);
	ASSERT_EQ(vec[2].size, 0);
	ASSERT_EQ(vec[3].size, 13);

	ASSERT_EQ_STR(vec[0].line, "line number 1");
	ASSERT_EQ_STR(vec[1].line, "line number 2");
	ASSERT_EQ_STR(vec[2].line, "");
	ASSERT_EQ_STR(vec[3].line, "line number 3");
	free(vec);
#endif
}

void test_split_line2() {
	char *lines = "line number 1\r\n"
		"line number 2";
	int orig_line_count = 2;
	int lines_s = strlen(lines);

	char **buf = (char **)malloc(orig_line_count * sizeof(char **));
	int *buf_s = (int *)malloc(orig_line_count * sizeof(int));

	int line_count = split_lines2(lines, strlen(lines), buf, buf_s);

	ASSERT_EQ(line_count, 2);
	ASSERT_EQ(buf_s[0], 13);
	ASSERT_EQ(buf_s[1], 13);

	ASSERT_EQ_STR(buf[0], "line number 1");
	ASSERT_EQ_STR(buf[1], "line number 2");

	free(buf);
	free(buf_s);
}

void test_split_black_line2() {
	char *lines = "line number 1\r\n\r\n"
		"line number 2";
	int lines_s = strlen(lines);
	int orig_line_count = 3;

	char **buf = (char **)malloc(orig_line_count * sizeof(char **));
	int *buf_s = (int *)malloc(orig_line_count * sizeof(int));

	int line_count = split_lines2(lines, strlen(lines), buf, buf_s);

	ASSERT_EQ(line_count, 3);
	ASSERT_EQ(buf_s[0], 13);
	ASSERT_EQ(buf_s[1], 0);
	ASSERT_EQ(buf_s[2], 13);

	ASSERT_EQ_STR(buf[0], "line number 1");
	ASSERT_EQ_STR(buf[1], "");
	ASSERT_EQ_STR(buf[2], "line number 2");

	free(buf);
	free(buf_s);
}

void test_split_multiple_lines2() {
	char *lines = "line number 1\r\n"
		"line number 2\r\n\r\n"
		"line number 3";
	int lines_s = strlen(lines);
	int orig_line_count = 4;

	char **buf = (char **)malloc(orig_line_count * sizeof(char **));
	int *buf_s = (int *)malloc(orig_line_count * sizeof(int));

	int line_count = split_lines2(lines, strlen(lines), buf, buf_s);

	ASSERT_EQ(line_count, 4);
	ASSERT_EQ(buf_s[0], 13);
	ASSERT_EQ(buf_s[1], 13);
	ASSERT_EQ(buf_s[2], 0);
	ASSERT_EQ(buf_s[3], 13);

	ASSERT_EQ_STR(buf[0], "line number 1");
	ASSERT_EQ_STR(buf[1], "line number 2");
	ASSERT_EQ_STR(buf[2], "");
	ASSERT_EQ_STR(buf[3], "line number 3");

	free(buf);
	free(buf_s);
}

void test_split_by_word() {
	char *line = "hello world this is a line";
	int line_s =  strlen(line);
	int orig_word_count = 5;
	char **buf = (char **)malloc(orig_word_count * sizeof(char **));
	int *buf_s = (int *)malloc(orig_word_count * sizeof(int)); 

	int word_count = split_by_words(line, line_s, buf, buf_s);

	ASSERT_EQ_STR(buf[0], "hello");
	ASSERT_EQ_STR(buf[1], "world");
	ASSERT_EQ_STR(buf[2], "this");
	ASSERT_EQ_STR(buf[3], "is");
	ASSERT_EQ_STR(buf[4], "a");
	ASSERT_EQ_STR(buf[5], "line");

	ASSERT_EQ(buf_s[0], 5);
	ASSERT_EQ(buf_s[1], 5);
	ASSERT_EQ(buf_s[2], 4);
	ASSERT_EQ(buf_s[3], 2);
	ASSERT_EQ(buf_s[4], 1);
	ASSERT_EQ(buf_s[5], 4);

	ASSERT_EQ(word_count, 6);

	free(buf);
	free(buf_s);
}

int main(int argc, char **argv) {
	test_push_1_item();
	test_push_101_item();
	test_inner_str();
	test_empty_str();
	test_multi_str_insert();

	test_split_line();
	test_split_black_line();
	test_split_multiple_lines();

	test_split_line2();
	test_split_black_line2();
	test_split_multiple_lines2();

	test_split_by_word();

	return 0;
}
