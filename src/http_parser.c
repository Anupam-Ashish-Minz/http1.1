#include "http_parser.h"
#include "char_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct VecCharArray split_lines(char *lines, size_t size) {
	struct VecCharArray vlines = new_vec_char_array();
	int prev = 0;

	for (int i=0; i<size-1; i++) {
		if (lines[i] == '\r' && lines[i+1] == '\n') {
			struct CharArray *line = (struct CharArray *)malloc(sizeof(struct CharArray));
			line->line = (char *)malloc(i - prev);
			line->size = i - prev;
			strncpy(line->line, &lines[prev], i - prev);
			push_char_array(&vlines, line);
			prev = i+2;
		}
	}
	if (prev < size) {
		struct CharArray *line = (struct CharArray *)malloc(sizeof(struct CharArray));
		line->line = (char *)malloc(size - prev);
		line->size = size - prev;
		strncpy(line->line, &lines[prev], size - prev);
		push_char_array(&vlines, line);
		prev = size;
	}

	return vlines;
}

void parse_http(char *buf, size_t buflen) {
}
