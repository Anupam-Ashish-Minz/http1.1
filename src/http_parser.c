#include "http_parser.h"
#include "char_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_http_request(char *raw, size_t raw_s, struct HttpRequest *out) {
	int line_count = get_line_count(raw, raw_s);
	char **lines = (char **)malloc(line_count * sizeof(char **));
	int *lines_index = (int *)malloc(line_count * sizeof(int *));
	line_count = split_lines2(raw, raw_s, lines, lines_index);
	if (line_count == 0) {
		fprintf(stderr, "incorrect http package incorrect number of line: %d",
				line_count);
		return -1;
	}

	int word_count = get_word_count(lines[0], lines_index[0]);
	char **words = (char **)malloc(word_count * sizeof(char **));
	int *words_index = (int *)malloc(word_count * sizeof(int *));
	word_count = split_by_words(lines[0], lines_index[0], words, words_index);
	if (word_count == 0) {
		fprintf(stderr, "incorrect word count should be 3, is %d\n",
				word_count);
		return -1;
	}

	if (strncmp(words[0], "get", words_index[0]) == 0 ||
		strncmp(words[0], "Get", words_index[0]) == 0 ||
		strncmp(words[0], "GET", words_index[0]) == 0) {
		out->method = GET;
	} else if (strncmp(words[0], "post", words_index[0]) == 0 ||
			   strncmp(words[0], "Post", words_index[0]) == 0 ||
			   strncmp(words[0], "POST", words_index[0]) == 0) {
		out->method = POST;
	} else if (strncmp(words[0], "put", words_index[0]) == 0 ||
			   strncmp(words[0], "Put", words_index[0]) == 0 ||
			   strncmp(words[0], "PUT", words_index[0]) == 0) {
		out->method = PUT;
	} else if (strncmp(words[0], "delete", words_index[0]) == 0 ||
			   strncmp(words[0], "Delete", words_index[0]) == 0 ||
			   strncmp(words[0], "DELETE", words_index[0]) == 0) {
		out->method = DELETE;
	} else {
		fprintf(stderr, "invalid method type parsing failed\n");
		return -1;
	}
	out->path = (char *)malloc(words_index[1] + 1);
	strncpy(out->path, words[1], words_index[1]);
	out->path += '\0';
	out->path_s = words_index[1] + 1;

	return 0;
}
