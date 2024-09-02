#include "http_response.h"
#include "http_headers.h"
#include "utils.h"

void test_header_stringification() {
	struct GeneralHeaders general_headers = init_general_headers();
	general_headers.Cache_Control = "something else";
	general_headers.s_Cache_Control = 15;
	char *out = (char *)malloc(34);
	int out_i = stringify_general_headers(general_headers, out, 0, 34);
	ASSERT_EQ_STR(out, "Cache-Control: something else\r\n");
	ASSERT_EQ(out_i, 31);
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
	ASSERT_EQ(out_i, 61);
	free(out);
}

int main() {
	test_header_stringification();
	test_multi_header_stringification();
	return 0;
}
