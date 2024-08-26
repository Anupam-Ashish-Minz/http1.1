#ifndef _CHAR_ARRAY_H
#define _CHAR_ARRAY_H

#include <stddef.h>

int split_lines2(char *lines, int size, char **ret, int *ret_s);
int split_by_words(char *line, int size, char **ret, int *ret_s);
int get_line_count(char *buf, size_t size);

#endif
