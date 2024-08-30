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
	if (strncmp(a, b, strlen(a) < strlen(b) ? strlen(a) : strlen(b)) != 0) {   \
		fprintf(stderr,                                                        \
				"Assert failed: %s, %s\nactual: \"%s\", expected: \"%s\"\n",   \
				#a, #b, a, b);                                                 \
		exit(-1);                                                              \
	}

#endif
