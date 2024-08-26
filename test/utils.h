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
	if (strncmp(a, b, strlen(b))) {                                            \
		fprintf(stderr,                                                        \
				"Assert failed: %s, %s\nactual: \"%s\", expected: \"%s\"\n",   \
				#a, #b, a, b);                                                 \
		exit(-1);                                                              \
	}

#define ASSERT_EQ_T(t, a, b)                                                   \
	if (t == "string") {                                                       \
		ASSERT_EQ_STR(a, b)                                                    \
	} else if (a != b) {                                                       \
		fprintf(stderr, "Assert failed: %s, %s\n", #a, #b);                    \
		if (strcmp(t, "int") == 0) {                                           \
			fprintf(stderr, "Assert values: %d, %d\n", a, b);                  \
		} else if (strcmp(t, "float") == 0) {                                  \
			fprintf(stderr, "Assert values: %f, %f\n", a, b);                  \
		}                                                                      \
		exit(-1);                                                              \
	}

#endif
