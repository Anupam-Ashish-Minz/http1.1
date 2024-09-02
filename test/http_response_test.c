#include "http_response.h"
#include "http_headers.h"
#include "utils.h"

void test_header_stringification() {
	struct GeneralHeaders general_headers = init_general_headers();
	general_headers.Cache_Control = "something else";
	general_headers.s_Cache_Control = 15;
	char *out = (char *)malloc(sizeof("Cache-Control: something else"));
	int out_i = stringify_general_headers(general_headers, out, 0, 30);
	ASSERT_EQ_STR(out, "Cache-Control: something else");
	ASSERT_EQ(out_i, 29);
	free(out);
}

int main() {
	test_header_stringification();
	return 0;
}
