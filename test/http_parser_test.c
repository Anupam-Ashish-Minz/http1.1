#include "char_array.h"
#include "http_parser.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void test_str_cieq() {
	char *a = "host";
	char *b = "Host";

	ASSERT_EQ(str_CIEQ(a, b, strlen(a), strlen(b)), true);

	a = "bost";
	b = "roast";

	ASSERT_EQ(str_CIEQ(a, b, strlen(a), strlen(b)), false);
}

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

	ASSERT_EQ_STR(request.request_headers.Host, "localhost:4000");
	ASSERT_EQ_STR(request.request_headers.User_Agent, "curl/8.6.0");
	ASSERT_EQ_STR(request.request_headers.Accept, "*/*");

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

	ASSERT_EQ_STR(request.request_headers.Host, "localhost:4000");
	ASSERT_EQ_STR(request.request_headers.User_Agent, "curl/8.6.0");
	ASSERT_EQ_STR(request.request_headers.Accept, "*/*");
	ASSERT_EQ_STR(request.entity_headers.Content_Type, "application/json");
	// ASSERT_EQ_STR(request.entity_headers.Content_Length, "61");
	ASSERT_EQ(request.entity_headers.Content_Length, 61);

	dealloc_request(&request);
}

void test_header_parser() {
	char *data = "Accept: *";
	size_t s_data = strlen(data);
	struct RequestHeaders request_headers = init_request_headers();
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

	ASSERT_EQ((int)request_headers.s_Authorization, 31);
	ASSERT_EQ_STR(request_headers.Authorization, "Basic YWxhZGRpbjpvcGVuc2VzYW1l");

	dealloc_request_headers(&request_headers);
}

void test_host_header_parsing() {
	char *data = "host: localhost:4000";
	size_t s_data = strlen(data);
	struct RequestHeaders request_headers;
	parse_header(data, s_data, NULL, &request_headers, NULL);

	ASSERT_EQ_STR(request_headers.Host, "localhost:4000");
	ASSERT_EQ((int)request_headers.s_Host, (int)strlen("localhost:4000") + 1);

	dealloc_request_headers(&request_headers);
}

int main() {
	test_str_cieq();
	test_header_parser();
	test_authorization_header_parsing();
	test_host_header_parsing();
	test_parse_simple_get_request();
	test_parse_post_request();

	return 0;
}
