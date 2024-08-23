#include "http_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void parse_http(char *buf, size_t buflen) {
	// GET / HTTP/1.1
	// Host: localhost:4000
	// User-Agent: curl/8.6.0
	// Accept: */*
	int split_at = -1;
	struct CharArray *filelines[5];

	int prev = 0;
	for (int i = 0; i < buflen - 1; i++) {
		if (buf[i] == '\r' && buf[i + 1] == '\n') {
			split_at = i;
			char *line = (char *)malloc(i - 1 - prev);
			strncpy(line, &buf[prev], i - 1);
		}
	}
}
