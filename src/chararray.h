#ifndef _CHAR_ARRAY_H
#define _CHAR_ARRAY_H

struct CharArray {
	char *line;
	unsigned int size;
};

struct VecCharArray {
	struct CharArray **arr;
	unsigned int len;
	unsigned int max_len;
};

void push_char_array(struct VecCharArray vec, struct CharArray *arr);

#endif
