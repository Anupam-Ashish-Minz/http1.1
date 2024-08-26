#include "char_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int split_by_words(char *line, int size, char **buf, int *buf_s) {
	int k = 0;
	int prev = 0;
	for (int i = 0; i < size; i++) {
		if (line[i] == ' ') {
			if (i == prev) continue;
			buf_s[k] = i - prev;
			buf[k] = &line[prev];
			prev = i + 1;
			++k;
		}
	}
	if (prev < size) {
		buf_s[k] = size - prev;
		buf[k] = &line[prev];
		++k;
	}
	return k;
}
