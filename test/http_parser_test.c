#include "http_parser.h"
#include <string.h>

int main(int argc, char **argv) {

	char *request = "get / http/1.1\r\n\
host: localhost:4000\r\n\
user-agent: curl/8.6.0\r\n\
Accept: */*\r\n";

	parse_http(request, strlen(request));

	return 0;
}
