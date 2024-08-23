#include <stdio.h>
#include <stdlib.h>
#include "char_array.h"

void push_char_array(struct VecCharArray vec, struct CharArray *arr) {
	if (vec.arr == NULL) {
		vec.arr = (struct CharArray **)malloc(10 * sizeof(struct CharArray *));
		vec.len = 0;
		vec.max_len = 10;
	}
	if (vec.len-1 == vec.max_len) {
		vec.arr = (struct CharArray **)realloc(vec.arr, (vec.max_len + 10) * sizeof(struct CharArray *));
		vec.max_len += 10;
	}
	vec.arr[vec.len] = arr;
	vec.len += 1;
}
