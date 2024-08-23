#ifndef _CHAR_ARRAY_H
#define _CHAR_ARRAY_H

struct CharArray {
	char *line;
	unsigned int size;
};

struct VecCharArray {
	struct CharArray **arr;
	unsigned int len;
};

struct CharArray *new_char_array(char *line, unsigned int size);
int set_char_array(struct CharArray *arr, char *line, unsigned int size);
void push_char_array(struct CharArray **vec, struct CharArray *arr);

#endif
