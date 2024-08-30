#ifndef _CHAR_ARRAY_H
#define _CHAR_ARRAY_H

#include <stddef.h>

int split_lines2(char *lines, int size, char **ret, int *ret_s);
int split_by_words(char *line, int size, char **ret, int *ret_s);
int get_line_count(char *buf, size_t size);
int get_word_count(char *buf, size_t size);
int split_by(char *line, int size, char ctrl, char **buf, int *buf_index);
int get_split_count(char *buf, size_t size, char ctrl);
int split_by_once(char *line, int size, char ctrl, char **buf, int *buf_index);
int trim_whitespaces_front(char *line, int size, char **out);

#endif
