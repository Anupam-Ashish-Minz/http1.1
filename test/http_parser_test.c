#include "char_array.h"
#include "http_parser.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

void test_parse_simple_get_request() {
	char *raw = "get / http/1.1\r\n"
				"host: localhost:4000\r\n"
				"user-agent: curl/8.6.0\r\n"
				"Accept: */*\r\n";

	struct HttpRequest request = init_request_obj();
	int status = parse_http_request(raw, strlen(raw), &request);
	if (status != 0) {
		fprintf(stderr, "failed to parse to http request\n");
		exit(-1);
	}

	ASSERT_EQ(request.method, GET);
	ASSERT_EQ_STR(request.requri, "/");

	dealloc_request(&request);
}

void test_parse_post_request() {
	char *raw = "POST / HTTP/1.1\r\n"
				"Host: localhost:4000\r\n"
				"User-Agent: curl/8.6.0\r\n"
				"Accept: */*\r\n"
				"Content-Type: application/json\r\n"
				"Content-Length: 61\r\n\r\n"
				"{\"name\": \"amy\", \"email\":\"alice@mail.com\", "
				"\"password\": \"pass\"}\r\n";

	struct HttpRequest request = init_request_obj();
	int status = parse_http_request(raw, strlen(raw), &request);
	if (status != 0) {
		fprintf(stderr, "failed to parse http request\n");
		exit(-1);
	}

	ASSERT_EQ(request.method, POST);
	ASSERT_EQ_STR(request.requri, "/");

	dealloc_request(&request);
}

void test_header_parser() {
	char *data = "Accept: *";
	size_t s_data = strlen(data);
	struct RequestHeaders request_headers;
	parse_header(data, s_data, NULL, &request_headers, NULL);

	ASSERT_EQ_STR(request_headers.Accept, "*");
	ASSERT_EQ((int)request_headers.s_Accept, 2);

	dealloc_request_headers(&request_headers);
}

void test_authorization_header_parsing() {
	char *data = "Authorization: Basic YWxhZGRpbjpvcGVuc2VzYW1l";
	size_t s_data = strlen(data);
	struct RequestHeaders request_headers;
	parse_header(data, s_data, NULL, &request_headers, NULL);

	ASSERT_EQ_STR(request_headers.Authorization, "Basic YWxhZGRpbjpvcGVuc2VzYW1l");
	ASSERT_EQ((int)request_headers.s_Authorization, 31);

	dealloc_request_headers(&request_headers);
}

int main() {
	test_header_parser();
	test_authorization_header_parsing();
	test_parse_simple_get_request();
	test_parse_post_request();

	return 0;
}
