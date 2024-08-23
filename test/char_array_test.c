#include "char_array.h"
#include <stdio.h>
#include <stdlib.h>

void test_push_1_item() {
	struct VecCharArray vec = new_vec_char_array();

	struct CharArray *arr =
	    (struct CharArray *)malloc(sizeof(struct CharArray));

	push_char_array(&vec, arr);

	if (vec.len != 1) {
		fprintf(stderr, "vector length 1 != %d\n", vec.len);
		exit(-1);
	}

	if (vec.max_len != 10) {
		fprintf(stderr, "vector max length 10 != %d\n", vec.max_len);
		exit(-1);
	}
}

void test_push_101_item() {
	struct VecCharArray vec = new_vec_char_array();

	struct CharArray *arr =
	    (struct CharArray *)malloc(sizeof(struct CharArray));

	for (int i=0; i<102; i++) {
		push_char_array(&vec, arr);
	}

	if (vec.len != 102) {
		fprintf(stderr, "vector length 101 != %d\n", vec.len);
		exit(-1);
	}

	if (vec.max_len != 110) {
		fprintf(stderr, "vector max length 110 != %d\n", vec.max_len);
		exit(-1);
	}
}

int main(int argc, char **argv) {
	test_push_1_item();
	test_push_101_item();

	return 0;
}
