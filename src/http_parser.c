#include "http_parser.h"
#include "char_array.h"
#include <stdio.h>
#include <stdlib.h>

void parse_http(char *request, size_t request_s) {
	int line_count = get_line_count(request, request_s);
	char **buf = (char **)malloc(line_count * sizeof(char **));
	int *buf_s = (int *)malloc(line_count * sizeof(int *));
	int split_line_count = split_lines2(request, request_s, buf, buf_s);
	if (line_count != split_line_count) {
		printf("line count does not match\n");
	} else {
		for (int i=0; i<line_count; i++) {
			printf("%s\n", buf[i]);
		}
	}
}
