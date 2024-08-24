#include "http_parser.h"
#include "char_array.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>

void test_parse_simple_get_request() {
	char *request = "get / http/1.1\r\n"
		"host: localhost:4000\r\n"
		"user-agent: curl/8.6.0\r\n"
		"Accept: */*\r\n";

	parse_http(request, strlen(request));
}

void test_parse_post_request() {

	char *request="POST / HTTP/1.1\r\n"
		"Host: localhost:4000\r\n"
		"User-Agent: curl/8.6.0\r\n"
		"Accept: */*\r\n"
		"Content-Type: application/json\r\n"
		"Content-Length: 61\r\n\r\n"
		"{\"name\": \"amy\", \"email\":\"alice@mail.com\", \"password\": \"pass\"}\r\n";

	parse_http(request, strlen(request));
}

int main(int argc, char **argv) {
	// test_parse_simple_get_request();
	// test_parse_post_request();

	return 0;
}
