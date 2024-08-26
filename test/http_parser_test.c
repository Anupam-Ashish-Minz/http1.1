#include "http_parser.h"
#include "char_array.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>

void test_parse_simple_get_request() {
	char *raw_req = "get / http/1.1\r\n"
		"host: localhost:4000\r\n"
		"user-agent: curl/8.6.0\r\n"
		"Accept: */*\r\n";

	struct HttpRequest request;
	int status = parse_http_request(raw_req, strlen(raw_req), &request);
	if (status != 0) {
		fprintf(stderr, "failed to parse to http request\n");
		exit(-1);
	}

	ASSERT_EQ(request.method, GET);
	ASSERT_EQ_STR(request.path, "/");
}

void test_parse_post_request() {
	char *raw = "POST / HTTP/1.1\r\n"
		"Host: localhost:4000\r\n"
		"User-Agent: curl/8.6.0\r\n"
		"Accept: */*\r\n"
		"Content-Type: application/json\r\n"
		"Content-Length: 61\r\n\r\n"
		"{\"name\": \"amy\", \"email\":\"alice@mail.com\", \"password\": \"pass\"}\r\n";

	struct HttpRequest request;
	int status = parse_http_request(raw, strlen(raw), &request);
	if (status != 0) {
		fprintf(stderr, "failed to parse http request\n");
		exit(-1);
	}

	ASSERT_EQ(request.method, POST);
	ASSERT_EQ_STR(request.path, "/");
}

int main() {
	test_parse_simple_get_request();
	test_parse_post_request();

	return 0;
}
