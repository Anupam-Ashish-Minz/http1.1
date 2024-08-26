#ifndef _HTTP_PARSER_H
#define _HTTP_PARSER_H

#include "char_array.h"
#include <stddef.h>

enum HTTP_METHOD {
	GET,
	POST,
	PUT,
	DELETE,
};

struct HttpRequest {
	enum HTTP_METHOD method;
	char *path;
	size_t path_s;
};

int parse_http_request(char *request, size_t request_s, struct HttpRequest *ret);

#endif
