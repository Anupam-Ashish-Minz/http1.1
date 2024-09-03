#include "http_response.h"
#include "http_headers.h"
#include "utils.h"

void test_header_stringification() {
	struct GeneralHeaders general_headers = init_general_headers();
	general_headers.Cache_Control = "something else";
	general_headers.s_Cache_Control = 15;
	char *out = (char *)malloc(34);
	int out_i = stringify_general_headers(general_headers, out, 0, 34);
	ASSERT_NEQ(out_i, -1);
	ASSERT_EQ_STR(out, "Cache-Control: something else\r\n");
	ASSERT_EQ(out_i, 32);
	free(out);
}

void test_multi_header_stringification() {
	struct GeneralHeaders general_headers = init_general_headers();
	general_headers.Cache_Control = "something else";
	general_headers.s_Cache_Control = 15;
	general_headers.Connection = "some other thing";
	general_headers.s_Connection = 17;
	char *out = (char *)malloc(67);
	int out_i = stringify_general_headers(general_headers, out, 0, 67);
	ASSERT_EQ_STR(out, "Cache-Control: something else\r\nConnection: some other thing\r\n");
	ASSERT_EQ(out_i, 62);
	free(out);
}

void test_outof_bound_check() {
	struct GeneralHeaders general_headers = init_general_headers();
	general_headers.Cache_Control = "something else";
	general_headers.s_Cache_Control = 15;
	general_headers.Connection = "some other thing";
	general_headers.s_Connection = 17;
	char *out = (char *)malloc(22);
	int out_i = stringify_general_headers(general_headers, out, 0, 22);
	ASSERT_EQ(out_i, -1);
	free(out);
}

void test_entity_headers_stringification() {
	struct EntityHeaders entity_headers = init_entity_headers();
	entity_headers.Allow = "http://localhost:4000";
	entity_headers.s_Allow = 22;
	char *out = (char *)malloc(31);
	int out_i = stringify_entity_headers(entity_headers, out, 0, 31);
	ASSERT_NEQ(out_i, -1);
	ASSERT_EQ_STR(out, "Allow: http://localhost:4000\r\n");
	ASSERT_EQ(out_i, 30);
}

void test_response_headers_stringification() {
	struct ResponseHeaders response_headers = init_response_headers();
	response_headers.Location = "http://www.w3.org/pub/WWW/People.html";
	char *out = (char *)malloc(62);
	int out_i = stringify_response_headers(response_headers, out, 0, 62);
	ASSERT_NEQ(out_i, -1);
	ASSERT_EQ_STR(out, "Age: 86400\r\nLocation: http://www.w3.org/pub/WWW/People.html");
	ASSERT_EQ(out_i, 62);
	free(out);
}

int main() {
	test_header_stringification();
	test_multi_header_stringification();
	test_outof_bound_check();
	test_response_headers_stringification();
	return 0;
}
