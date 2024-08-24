#ifndef _CHAR_ARRAY_H
#define _CHAR_ARRAY_H

#include <stddef.h>

/** CHARARR
* 1 -> version 1
* 2 -> version 2
*/
#define CHARARR 2
#define VECBUF 10

#if CHARARR == 1

struct CharArray {
	char *line;
	unsigned int size;
};

struct VecCharArray {
	struct CharArray **arr;
	unsigned int len;
	unsigned int max_len;
};

struct VecCharArray new_vec_char_array();
void push_char_array(struct VecCharArray *vec, struct CharArray *arr);
struct VecCharArray split_lines(char *lines, size_t size);

#elif CHARARR == 2

struct CharArray {
	char *line;
	unsigned int size;
};

struct CharArray *push_char_array(struct CharArray *vec, unsigned int *vec_len, struct CharArray c);
struct CharArray *split_lines(char *lines, size_t size);
int split_lines2(char *lines, size_t size, char **ret, size_t *ret_s);

#endif
#endif
