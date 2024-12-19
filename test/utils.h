#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_EQ_STR(a, b) \
	if (strncmp(a, b, strlen(b)) != 0) { \
		fprintf(stderr, "Assert failed: %s:%d in function: %s for " \
			  "expression ASSERT_EQ_STR(%s, %s) values " \
			  "expected: \"%s\", actual: \"%s\"\n", \
			__FILE__, __LINE__, __FUNCTION__, #a, #b, a, b); \
		exit(-1); \
	}

#define ASSERT_NEQ(a, b)                                                       \
	if (a == b) {                                                              \
		fprintf(stderr, "Not Equals Assert failed: %s, %s, \nvalue: %d\n", #a, \
				#b, a);                                                        \
		exit(-1);                                                              \
	}

#define ASSERT_EQ(a, b) \
	if ((long)a != (long)b) { \
		fprintf(stderr, "Assert failed: %s:%d in function: %s for " \
			  "expression ASSERT_EQ(%s, %s) values " \
			  "expected: %ld, actual: %ld\n", \
			__FILE__, __LINE__, __FUNCTION__, #a, #b, (long)a, \
			(long)b); \
		exit(-1); \
	}

#endif
