#include "http_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void parse_http(char *buf, size_t buflen) {
	// get / http/1.1\r\n
	// host: localhost:4000
	// user-agent: curl/8.6.0
	// Accept: */*
	
	int prev = 0;
	for (int i=0; i<buflen-1; i++) {
		if (buf[i] == '\r' && buf[i+1] == '\n') {
			if (prev == i) {
				continue;
			}
			char *line = malloc(i - prev);
			strncpy(line, &buf[prev], i - prev);
			printf("->%s\n", line);
			prev = i+2;
		}
	}
}
