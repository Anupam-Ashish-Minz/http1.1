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

enum HTTP_VERSION {
	HTTP_1_1
};

struct HttpRequest {
	enum HTTP_METHOD method;
	char *requri;
	size_t requri_s;
	enum HTTP_VERSION version;
};

int parse_http_request(char *request, size_t request_s, struct HttpRequest *ret);

#endif
