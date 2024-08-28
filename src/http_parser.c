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
	out->requri = (char *)malloc(words_index[1] + 1);
	strncpy(out->requri, words[1], words_index[1]);
	out->requri += '\0';
	out->requri_s = words_index[1] + 1;

	return 0;
}


int parse_header(char *header, size_t s_header,
				 struct GeneralHeaders *general_headers,
				 struct RequestHeaders *request_headers,
				 struct EntityHeaders *entity_headers) {


	int split_count = get_split_count(header, s_header, ':');
	char **out = (char **)malloc(s_header * sizeof(char)); // TODO fix the size late
	int *out_lens = (int *)malloc(split_count * sizeof(int));

	int word_count = split_by(header, s_header, ':', out, out_lens);
	char *header_name = out[0];
	size_t s_header_name = out_lens[0];
	char *header_body = out[1];
	size_t s_header_body = out_lens[1];

	if (word_count == 0) {
		return -1;
	}
	if (general_headers != NULL) {
		if (strncmp(header_name, "Cache-Control", s_header_name) == 0) {
			general_headers->Cache_Control = (char *)malloc(s_header_body);
			strncpy(general_headers->Cache_Control, header_body, s_header_body);
			general_headers->s_Cache_Control = s_header_body;
		}
		if (strncmp(header_name, "Connection", s_header_name) == 0) {
			general_headers->Connection = (char *)malloc(s_header_body);
			strncpy(general_headers->Connection, header_body, s_header_body);
			general_headers->s_Connection = s_header_body;
		}
		if (strncmp(header_name, "Date", s_header_name) == 0) {
			general_headers->Date = (char *)malloc(s_header_body);
			strncpy(general_headers->Date, header_body, s_header_body);
			general_headers->s_Date = s_header_body;
		}
		if (strncmp(header_name, "Pragma", s_header_name) == 0) {
			general_headers->Pragma = (char *)malloc(s_header_body);
			strncpy(general_headers->Pragma, header_body, s_header_body);
			general_headers->s_Pragma = s_header_body;
		}
		if (strncmp(header_name, "Trailer", s_header_name) == 0) {
			general_headers->Trailer = (char *)malloc(s_header_body);
			strncpy(general_headers->Trailer, header_body, s_header_body);
			general_headers->s_Trailer = s_header_body;
		}
		if (strncmp(header_name, "Transfer-Encoding", s_header_name) == 0) {
			general_headers->Transfer_Encoding = (char *)malloc(s_header_body);
			strncpy(general_headers->Transfer_Encoding, header_body, s_header_body);
			general_headers->s_Transfer_Encoding = s_header_body;
		}
		if (strncmp(header_name, "Upgrade", s_header_name) == 0) {
			general_headers->Upgrade = (char *)malloc(s_header_body);
			strncpy(general_headers->Upgrade, header_body, s_header_body);
			general_headers->s_Upgrade = s_header_body;
		}
		if (strncmp(header_name, "Via", s_header_name) == 0) {
			general_headers->Via = (char *)malloc(s_header_body);
			strncpy(general_headers->Via, header_body, s_header_body);
			general_headers->s_Via = s_header_body;
		}
		if (strncmp(header_name, "Warning", s_header_name) == 0) {
			general_headers->Warning = (char *)malloc(s_header_body);
			strncpy(general_headers->Warning, header_body, s_header_body);
			general_headers->s_Warning = s_header_body;
		}
	}
	if (request_headers != NULL) {
		if (strncmp(header_name, "Accept", s_header_name) == 0) {
			request_headers->Accept = (char *)malloc(s_header_body);
			strncpy(request_headers->Accept, header_body, s_header_body);
			request_headers->s_Accept = s_header_body;
		}
		if (strncmp(header_name, "Accept-Charset", s_header_name) == 0) {
			request_headers->Accept_Charset = (char *)malloc(s_header_body);
			strncpy(request_headers->Accept_Charset, header_body, s_header_body);
			request_headers->s_Accept_Charset = s_header_body;
		}
		if (strncmp(header_name, "Accept-Encoding", s_header_name) == 0) {
			request_headers->Accept_Encoding = (char *)malloc(s_header_body);
			strncpy(request_headers->Accept_Encoding, header_body, s_header_body);
			request_headers->s_Accept_Encoding = s_header_body;
		}
		if (strncmp(header_name, "Accept-Language", s_header_name) == 0) {
			request_headers->Accept_Language = (char *)malloc(s_header_body);
			strncpy(request_headers->Accept_Language, header_body, s_header_body);
			request_headers->s_Accept_Language = s_header_body;
		}
		if (strncmp(header_name, "Authorization", s_header_name) == 0) {
			request_headers->Authorization = (char *)malloc(s_header_body);
			strncpy(request_headers->Authorization, header_body, s_header_body);
			request_headers->s_Authorization = s_header_body;
		}
		if (strncmp(header_name, "Expect", s_header_name) == 0) {
			request_headers->Expect = (char *)malloc(s_header_body);
			strncpy(request_headers->Expect, header_body, s_header_body);
			request_headers->s_Expect = s_header_body;
		}
		if (strncmp(header_name, "From", s_header_name) == 0) {
			request_headers->From = (char *)malloc(s_header_body);
			strncpy(request_headers->From, header_body, s_header_body);
			request_headers->s_From = s_header_body;
		}
		if (strncmp(header_name, "Host", s_header_name) == 0) {
			request_headers->Host = (char *)malloc(s_header_body);
			strncpy(request_headers->Host, header_body, s_header_body);
			request_headers->s_Host = s_header_body;
		}
		if (strncmp(header_name, "If-Match", s_header_name) == 0) {
			request_headers->If_Match = (char *)malloc(s_header_body);
			strncpy(request_headers->If_Match, header_body, s_header_body);
			request_headers->s_If_Match = s_header_body;
		}
		if (strncmp(header_name, "If-Modified-Since", s_header_name) == 0) {
			request_headers->If_Modified_Since = (char *)malloc(s_header_body);
			strncpy(request_headers->If_Modified_Since, header_body, s_header_body);
			request_headers->s_If_Modified_Since = s_header_body;
		}
		if (strncmp(header_name, "If-None-Match", s_header_name) == 0) {
			request_headers->If_None_Match = (char *)malloc(s_header_body);
			strncpy(request_headers->If_None_Match, header_body, s_header_body);
			request_headers->s_If_None_Match = s_header_body;
		}
		if (strncmp(header_name, "If-Range", s_header_name) == 0) {
			request_headers->If_Range = (char *)malloc(s_header_body);
			strncpy(request_headers->If_Range, header_body, s_header_body);
			request_headers->s_If_Range = s_header_body;
		}
		if (strncmp(header_name, "If-Unmodified-Since", s_header_name) == 0) {
			request_headers->If_Unmodified_Since = (char *)malloc(s_header_body);
			strncpy(request_headers->If_Unmodified_Since, header_body, s_header_body);
			request_headers->s_If_Unmodified_Since = s_header_body;
		}
		if (strncmp(header_name, "Max-Forwards", s_header_name) == 0) {
			request_headers->Max_Forwards = (char *)malloc(s_header_body);
			strncpy(request_headers->Max_Forwards, header_body, s_header_body);
			request_headers->s_Max_Forwards = s_header_body;
		}
		if (strncmp(header_name, "Proxy-Authorization", s_header_name) == 0) {
			request_headers->Proxy_Authorization = (char *)malloc(s_header_body);
			strncpy(request_headers->Proxy_Authorization, header_body, s_header_body);
			request_headers->s_Proxy_Authorization = s_header_body;
		}
		if (strncmp(header_name, "Range", s_header_name) == 0) {
			request_headers->Range = (char *)malloc(s_header_body);
			strncpy(request_headers->Range, header_body, s_header_body);
			request_headers->s_Range = s_header_body;
		}
		if (strncmp(header_name, "Referer", s_header_name) == 0) {
			request_headers->Referer = (char *)malloc(s_header_body);
			strncpy(request_headers->Referer, header_body, s_header_body);
			request_headers->s_Referer = s_header_body;
		}
		if (strncmp(header_name, "TE", s_header_name) == 0) {
			request_headers->TE = (char *)malloc(s_header_body);
			strncpy(request_headers->TE, header_body, s_header_body);
			request_headers->s_TE = s_header_body;
		}
		if (strncmp(header_name, "User-Agent", s_header_name) == 0) {
			request_headers->User_Agent = (char *)malloc(s_header_body);
			strncpy(request_headers->User_Agent, header_body, s_header_body);
			request_headers->s_User_Agent = s_header_body;
		}
	}

	if (entity_headers != NULL) {
	}

	free(out);
	free(out_lens);
}

