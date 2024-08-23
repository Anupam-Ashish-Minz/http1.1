#include <stdio.h>
#include <stdlib.h>
#include "chararray.h"

struct CharArray *new_char_array(char *line, unsigned int size) {
	struct CharArray *arr = (struct CharArray *)malloc(sizeof(struct CharArray));
	arr->line = line;
	arr->size = size;
	return arr;
}

int set_char_array(struct CharArray *arr, char *line, unsigned int size) {
	arr = (struct CharArray *)malloc(sizeof(struct CharArray));
	arr->line = line;
	arr->size = size;
	return 0;
}

void push_char_array(struct CharArray **vec, struct CharArray *arr) {
	vec[0] = arr;
}
