#include <stdio.h>
#include <stdlib.h>
#include "char_array.h"

int main(int argc, char **argv) {
	struct VecCharArray vec = new_vec_char_array();

	struct CharArray *arr =
	    (struct CharArray *)malloc(sizeof(struct CharArray));

	push_char_array(&vec, arr);

	if (vec.len != 1) {
		fprintf(stderr, "vector length 1 != %d\n", vec.len); 
		return -1;
	}

	return 0;
}
