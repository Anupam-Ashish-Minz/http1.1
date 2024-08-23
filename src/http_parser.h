#ifndef _HTTP_PARSER_H
#define _HTTP_PARSER_H

#include <stddef.h>

struct HttpPackat {
};

void parse_http(char *buf, size_t buflen);

#endif
