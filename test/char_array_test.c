#include "char_array.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_split_line2() {
	char *lines = "line number 1\r\n"
		"line number 2";
	int orig_line_count = 2;

	char **buf = (char **)malloc(orig_line_count * sizeof(char **));
	int *buf_s = (int *)malloc(orig_line_count * sizeof(int *));

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
	int orig_line_count = 3;

	char **buf = (char **)malloc(orig_line_count * sizeof(char **));
	int *buf_s = (int *)malloc(orig_line_count * sizeof(int *));

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
	int orig_line_count = 4;

	char **buf = (char **)malloc(orig_line_count * sizeof(char **));
	int *buf_s = (int *)malloc(orig_line_count * sizeof(int *));

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
	int orig_word_count = 6;
	char **buf = (char **)malloc(orig_word_count * sizeof(char*));
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

void test_word_count() {
	char *lines = "line number 1\r\nline number 2";
	int line_count = get_line_count(lines, strlen(lines));
	ASSERT_EQ(line_count, 2);
}

void test_word_count_blank_lines() {
	char *lines = "line number 1\r\n"
		"line number 2\r\n\r\n"
		"line number 3";
	int line_count = get_line_count(lines, strlen(lines));
	ASSERT_EQ(line_count, 4);
}

int main() {
	test_split_line2();
	test_split_black_line2();
	test_split_multiple_lines2();

	test_split_by_word();

	test_word_count();
	test_word_count_blank_lines();

	return 0;
}
