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
}

int main(int argc, char **argv) {
	test_push_1_item();

	return 0;
}
