#include "char_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if CHARARR == 1

struct VecCharArray new_vec_char_array() {
	struct VecCharArray arr = {
	    NULL,
	    0,
	    0,
	};
	return arr;
}

void push_char_array(struct VecCharArray *vec, struct CharArray *arr) {
	if (vec->arr == NULL) {
		vec->arr = (struct CharArray **)malloc(
		    10 * sizeof(struct CharArray *));
		vec->len = 0;
		vec->max_len = 10;
	}
	if (vec->len - 1 == vec->max_len) {
		vec->arr = (struct CharArray **)realloc(
		    vec->arr, (vec->max_len + 10) * sizeof(struct CharArray *));
		vec->max_len += 10;
	}
	vec->arr[vec->len] = arr;
	vec->len += 1;
}

struct VecCharArray split_lines(char *lines, size_t size) {
	struct VecCharArray vlines = new_vec_char_array();
	int prev = 0;

	for (int i=0; i<size-1; i++) {
		if (lines[i] == '\r' && lines[i+1] == '\n') {
			struct CharArray *line = (struct CharArray *)malloc(sizeof(struct CharArray));
			line->line = (char *)malloc(i - prev);
			line->size = i - prev;
			strncpy(line->line, &lines[prev], i - prev);
			printf("->%s<-\n", line->line);
			push_char_array(&vlines, line);
			prev = i+2;
		}
	}
	if (prev < size) {
		struct CharArray *line = (struct CharArray *)malloc(sizeof(struct CharArray));
		line->line = (char *)malloc(size - prev);
		line->size = size - prev;
		strncpy(line->line, &lines[prev], size - prev);
		printf("->%s<-\n", line->line);
		push_char_array(&vlines, line);
		prev = size;
	}

	return vlines;
}

#elif CHARARR == 2

struct CharArray *push_char_array(struct CharArray *vec, unsigned int *vec_len, struct CharArray c) {
	if (vec == NULL) {
		vec = (struct CharArray *)malloc(VECBUF * sizeof(struct CharArray));
		*vec_len = 0;
	} else if (*vec_len % VECBUF == 0) {
		vec = (struct CharArray *)realloc(vec, (*vec_len + VECBUF) * sizeof(struct CharArray));
	}
	vec[*vec_len] = c;
	*vec_len += 1;
	return vec;
}

struct CharArray *split_lines(char *lines, size_t size) {
	struct CharArray *vec = NULL;
	unsigned int vec_len = 0;
	int prev = 0;

	for (int i=0; i<size-1; i++) {
		if (lines[i] == '\r' && lines[i+1] == '\n') {
			struct CharArray line;
			if (i == prev) {
				line.line = "";
				line.size = 0;
			} else {
				line.line = (char *)malloc(i - prev);
				line.size = i - prev;
				strncpy(line.line, &lines[prev], i - prev);
			}
			vec = push_char_array(vec, &vec_len, line);
			prev = i+2;
		}
	}
	if (prev < size) {
		struct CharArray line;
		line.line = (char *)malloc(size - prev);
		line.size = size - prev;
		strncpy(line.line, &lines[prev], size - prev);
		vec = push_char_array(vec, &vec_len, line);
		prev = size;
	}

	return vec;
}

int split_lines2(char *lines, int size, char **buf, int *buf_s) {
	int prev = 0;
	int k = 0;
	for (int i=0; i<size-1; i++) {
		if (lines[i] == '\r' && lines[i+1] == '\n') {
			char *line;
			unsigned int line_s;
			if (i == prev) {
				line = NULL;
				line_s = 0;
			} else {
				line = &lines[prev];
				line_s = i - prev;
			}
			buf[k] = line;
			buf_s[k] = line_s;
			++k;
			prev = i+2;
		}
	}
	if (prev < size) {
		char *line;
		int line_s = size - prev;
		line = &lines[prev];
		buf[k] = line;
		buf_s[k] = line_s;
		++k;
		prev = size;
	}
	return k;
}

#endif

int split_by_words(char *line, int size, char **buf, int *buf_s) {
	int k = 0;
	int prev = 0;
	for (int i = 0; i < size; i++) {
		if (line[i] == ' ') {
			if (i == prev) continue;
			buf_s[k] = i - prev;
			buf[k] = (char *)malloc(buf_s[k]);
			strncpy(buf[k], &line[prev], buf_s[k]);
			prev = i + 1;
			++k;
		}
	}
	if (prev < size) {
		buf_s[k] = size - prev;
		buf[k] = (char *)malloc(buf_s[k]);
		strncpy(buf[k], &line[prev], buf_s[k]);
		++k;
	}
	return k;
}
