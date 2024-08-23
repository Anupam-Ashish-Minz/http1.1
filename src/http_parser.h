#ifndef _HTTP_PARSER_H
#define _HTTP_PARSER_H

#include "char_array.h"
#include <stddef.h>

struct HttpPackat {
};

struct VecCharArray split_lines(char *lines, size_t size);
void parse_http(char *buf, size_t buflen);

#endif
