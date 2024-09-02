#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_EQ(a, b)                                                        \
	if (a != b) {                                                              \
		fprintf(stderr, "Assert failed: %s, %s\nactual: %d, expected: %d\n",   \
				#a, #b, a, b);                                                 \
		exit(-1);                                                              \
	}

#define ASSERT_EQ_STR(a, b)                                                    \
	if (strlen(a) < strlen(b)) {                                               \
		fprintf(stderr,                                                        \
				"Assert failed: %s, %s\nactual: \"%s\", expected: \"%s\"\n",   \
				#a, #b, a, b);                                                 \
		fprintf(stderr,                                                        \
				"String Length: %s, %s\nactual: \"%ld\", expected: \"%ld\"\n", \
				#a, #b, strlen(a), strlen(b));                                 \
		exit(-1);                                                              \
	}                                                                          \
	if (strncmp(a, b, strlen(b)) != 0) {                                       \
		fprintf(stderr,                                                        \
				"Assert failed: %s, %s\nactual: \"%s\", expected: \"%s\"\n",   \
				#a, #b, a, b);                                                 \
		exit(-1);                                                              \
	}

#define ASSERT_NEQ(a, b)                                                       \
	if (a == b) {                                                              \
		fprintf(stderr, "Not Equals Assert failed: %s, %s, \nvalue: %d\n", #a, \
				#b, a);                                                        \
		exit(-1);                                                              \
	}

#endif
