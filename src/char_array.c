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

int split_by_words(char *line, int size, char **buf, int *buf_index) {
	int k = 0;
	int prev = 0;
	for (int i = 0; i < size; i++) {
		if (line[i] == ' ') {
			if (i == prev) continue;
			buf_index[k] = i - prev;
			buf[k] = &line[prev];
			prev = i + 1;
			++k;
		}
	}
	if (prev < size) {
		buf_index[k] = size - prev;
		buf[k] = &line[prev];
		++k;
	}
	return k;
}

int split_by(char *line, int size, char ctrl, char **buf, int *buf_index) {
	int k = 0;
	int prev = 0;
	for (int i = 0; i < size; i++) {
		if (line[i] == ctrl) {
			if (i == prev) continue;
			if (prev < size && line[prev] == ' ') {
				buf_index[k] = i - prev - 1;
				buf[k] = &line[prev+1];
				prev = i + 2;
				++k;
			} else{
				buf_index[k] = i - prev;
				buf[k] = &line[prev];
				prev = i + 1;
				++k;
			}
		}
	}
	if (prev < size) {
		if (prev < size && line[prev] == ' ') {
			buf_index[k] = size - prev - 1;
			buf[k] = &line[prev+1];
			++k;
		} else {
			buf_index[k] = size - prev;
			buf[k] = &line[prev];
			++k;
		}
	}
	return k;
}

int split_by_once(char *line, int size, char ctrl, char **buf, int *buf_index) {
	int split_at = -1;
	for (int i = 0; i < size; i++) {
		if (line[i] == ctrl) {
			split_at = i;
			break;
		}
	}
	if (split_at < 0) {
		return -1;
	}
	buf[0] = &line[0];
	buf_index[0] = split_at;
	buf[1] = &line[split_at + 1];
	buf_index[1] = size - (split_at + 1);
	return 2;
}

int trim_whitespaces_front(char *line, int size, char **out) {
	int i = 0;
	while (i < size) {
		if (line[i] != ' ') {
			break;
		}
		++i;
	}
	if (i < size) {
		*out = &line[i];
		return size - i;
	} else {
		*out = &line[0];
		return size;
	}
}

int get_line_count(char *buf, size_t size) {
	if (strcmp(buf, "") == 0) {
		return 0;
	}
	int count = 1;
	for (long unsigned int i=0; i<size-1; i++) {
		if (buf[i] == '\r' && buf[i+1] == '\n') {
			count += 1;
		}
	}
	return count;
}

int get_word_count(char *buf, size_t size) {
	if (size == 0) {
		return 0;
	}
	int count = 1;
	for (unsigned long int i=0; i<size; i++) {
		if (buf[i] == ' ') {
			++count;
		}
	}
	return count;
}

int get_split_count(char *buf, size_t size, char ctrl) {
	if (size == 0) {
		return 0;
	}
	int count = 1;
	for (unsigned long int i=0; i<size; i++) {
		if (buf[i] == ctrl) {
			++count;
		}
	}
	return count;
}
