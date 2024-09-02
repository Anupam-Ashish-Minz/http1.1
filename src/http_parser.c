#include "http_parser.h"
#include "http_headers.h"
#include "char_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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
	out->requri[words_index[1]] = '\0';
	out->requri_s = words_index[1] + 1;

	for (int i = 1; i < line_count; i++) {
		parse_header(lines[i], (size_t)lines_index[i], &out->general_headers,
					 &out->request_headers, &out->entity_headers);
	}

	free(words);
	free(words_index);
	free(lines);
	free(lines_index);

	return 0;
}

struct RequestHeaders init_request_headers() {
	struct RequestHeaders request_headers;
	request_headers.Accept = NULL;
	request_headers.Accept_Charset = NULL;
	request_headers.Accept_Encoding = NULL;
	request_headers.Accept_Language = NULL;
	request_headers.Authorization = NULL;
	request_headers.Expect = NULL;
	request_headers.From = NULL;
	request_headers.Host = NULL;
	request_headers.If_Match = NULL;
	request_headers.If_Modified_Since = NULL;
	request_headers.If_None_Match = NULL;
	request_headers.If_Range = NULL;
	request_headers.If_Unmodified_Since = NULL;
	request_headers.Max_Forwards = NULL;
	request_headers.Proxy_Authorization = NULL;
	request_headers.Range = NULL;
	request_headers.Referer = NULL;
	request_headers.TE = NULL;
	request_headers.User_Agent = NULL;
	request_headers.s_Accept = 0;
	request_headers.s_Accept_Charset = 0;
	request_headers.s_Accept_Encoding = 0;
	request_headers.s_Accept_Language = 0;
	request_headers.s_Authorization = 0;
	request_headers.s_Expect = 0;
	request_headers.s_From = 0;
	request_headers.s_Host = 0;
	request_headers.s_If_Match = 0;
	request_headers.s_If_Modified_Since = 0;
	request_headers.s_If_None_Match = 0;
	request_headers.s_If_Range = 0;
	request_headers.s_If_Unmodified_Since = 0;
	request_headers.s_Max_Forwards = 0;
	request_headers.s_Proxy_Authorization = 0;
	request_headers.s_Range = 0;
	request_headers.s_Referer = 0;
	request_headers.s_TE = 0;
	request_headers.s_User_Agent = 0;
	return request_headers;
}

struct HttpRequest init_request_obj() {
	struct HttpRequest request;
	request.requri = NULL;
	request.requri_s = 0;
	request.general_headers = init_general_headers();
	request.request_headers = init_request_headers();
	request.entity_headers = init_entity_headers();

	return request;
}

bool str_CIEQ(char *a, char *b, int a_len, int b_len) {
	bool t = false;
	if (a_len != b_len) {
		return t;
	}
	char *lower_case_a = (char *)malloc(a_len * sizeof(char));
	char *lower_case_b = (char *)malloc(a_len * sizeof(char));
	for(int i=0; i<a_len; i++) {
		lower_case_a[i] = tolower(a[i]);
		lower_case_b[i] = tolower(b[i]);
	}
	if (strncmp(lower_case_a, lower_case_b, a_len) == 0) {
		t = true;
	}
	free(lower_case_a);
	free(lower_case_b);
	return t;
}

int parse_header(char *header, size_t s_header,
				 struct GeneralHeaders *general_headers,
				 struct RequestHeaders *request_headers,
				 struct EntityHeaders *entity_headers) {

	if (header == NULL) {
		return -1;
	} else if (s_header == 0) {
		return -1;
	} else if (strlen(header) == 0) {
		return -1;
	}
	int split_count = get_split_count(header, s_header, ':');
	char **out = (char **)malloc(s_header * sizeof(char *));
	int *out_lens = (int *)malloc(split_count * sizeof(int));

	int word_count = split_by_once(header, s_header, ':', out, out_lens);
	char *header_name = out[0];
	size_t s_header_name = out_lens[0];
	char *header_body = out[1];
	size_t s_header_body = trim_whitespaces_front(out[1], out_lens[1], &header_body);

	if (word_count == 0) {
		return -1;
	}
	if (general_headers != NULL) {
		if (str_CIEQ(header_name, "Cache-Control", s_header_name, strlen("Cache-Control"))) {
			general_headers->Cache_Control = (char *)malloc(s_header_body + 1);
			strncpy(general_headers->Cache_Control, header_body, s_header_body);
			general_headers->Cache_Control[s_header_body] = '\0';
			general_headers->s_Cache_Control = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Connection", s_header_name, strlen("Connection"))) {
			general_headers->Connection = (char *)malloc(s_header_body + 1);
			strncpy(general_headers->Connection, header_body, s_header_body);
			general_headers->Connection[s_header_body] = '\0';
			general_headers->s_Connection = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Date", s_header_name, strlen("Date"))) {
			general_headers->Date = (char *)malloc(s_header_body + 1);
			strncpy(general_headers->Date, header_body, s_header_body);
			general_headers->Date[s_header_body] = '\0';
			general_headers->s_Date = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Pragma", s_header_name, strlen("Pragma"))) {
			general_headers->Pragma = (char *)malloc(s_header_body + 1);
			strncpy(general_headers->Pragma, header_body, s_header_body);
			general_headers->Pragma[s_header_body] = '\0';
			general_headers->s_Pragma = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Trailer", s_header_name, strlen("Trailer"))) {
			general_headers->Trailer = (char *)malloc(s_header_body + 1);
			strncpy(general_headers->Trailer, header_body, s_header_body);
			general_headers->Trailer[s_header_body] = '\0';
			general_headers->s_Trailer = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Transfer-Encoding", s_header_name, strlen("Transfer-Encoding"))) {
			general_headers->Transfer_Encoding = (char *)malloc(s_header_body + 1);
			strncpy(general_headers->Transfer_Encoding, header_body,
					s_header_body);
			general_headers->Transfer_Encoding[s_header_body] = '\0';
			general_headers->s_Transfer_Encoding = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Upgrade", s_header_name, strlen("Upgrade"))) {
			general_headers->Upgrade = (char *)malloc(s_header_body + 1);
			strncpy(general_headers->Upgrade, header_body, s_header_body);
			general_headers->Upgrade[s_header_body] = '\0';
			general_headers->s_Upgrade = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Via", s_header_name, strlen("Via"))) {
			general_headers->Via = (char *)malloc(s_header_body + 1);
			strncpy(general_headers->Via, header_body, s_header_body);
			general_headers->Via[s_header_body] = '\0';
			general_headers->s_Via = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Warning", s_header_name, strlen("Warning"))) {
			general_headers->Warning = (char *)malloc(s_header_body + 1);
			strncpy(general_headers->Warning, header_body, s_header_body);
			general_headers->Warning[s_header_body] = '\0';
			general_headers->s_Warning = s_header_body + 1;
		}
	}
	if (request_headers != NULL) {
		if (str_CIEQ(header_name, "Accept", s_header_name, strlen("Accept"))) {
			request_headers->Accept = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->Accept, header_body, s_header_body);
			request_headers->Accept[s_header_body] = '\0';
			request_headers->s_Accept = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Accept-Charset", s_header_name, strlen("Accept-Charset"))) {
			request_headers->Accept_Charset = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->Accept_Charset, header_body,
					s_header_body);
			request_headers->Accept_Charset[s_header_body] = '\0';
			request_headers->s_Accept_Charset = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Accept-Encoding", s_header_name, strlen("Accept-Encoding"))) {
			request_headers->Accept_Encoding = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->Accept_Encoding, header_body,
					s_header_body);
			request_headers->Accept_Encoding[s_header_body] = '\0';
			request_headers->s_Accept_Encoding = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Accept-Language", s_header_name, strlen("Accept-Language"))) {
			request_headers->Accept_Language = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->Accept_Language, header_body,
					s_header_body);
			request_headers->Accept_Language[s_header_body] = '\0';
			request_headers->s_Accept_Language = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Authorization", s_header_name, strlen("Authorization"))) {
			request_headers->Authorization = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->Authorization, header_body, s_header_body);
			request_headers->Authorization[s_header_body] = '\0';
			request_headers->s_Authorization = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Expect", s_header_name, strlen("Expect"))) {
			request_headers->Expect = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->Expect, header_body, s_header_body);
			request_headers->Expect[s_header_body] = '\0';
			request_headers->s_Expect = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "From", s_header_name, strlen("From"))) {
			request_headers->From = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->From, header_body, s_header_body);
			request_headers->From[s_header_body] = '\0';
			request_headers->s_From = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Host", s_header_name, strlen("Host"))) {
			request_headers->Host = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->Host, header_body, s_header_body);
			request_headers->Host[s_header_body] = '\0';
			request_headers->s_Host = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "If-Match", s_header_name, strlen("If-Match"))) {
			request_headers->If_Match = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->If_Match, header_body, s_header_body);
			request_headers->If_Match[s_header_body] = '\0';
			request_headers->s_If_Match = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "If-Modified-Since", s_header_name, strlen("If-Modified-Since"))) {
			request_headers->If_Modified_Since = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->If_Modified_Since, header_body,
					s_header_body);
			request_headers->If_Modified_Since[s_header_body] = '\0';
			request_headers->s_If_Modified_Since = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "If-None-Match", s_header_name, strlen("If-None-Match"))) {
			request_headers->If_None_Match = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->If_None_Match, header_body, s_header_body);
			request_headers->If_None_Match[s_header_body] = '\0';
			request_headers->s_If_None_Match = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "If-Range", s_header_name, strlen("If-Range"))) {
			request_headers->If_Range = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->If_Range, header_body, s_header_body);
			request_headers->If_Range[s_header_body] = '\0';
			request_headers->s_If_Range = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "If-Unmodified-Since", s_header_name, strlen("If-Unmodified-Since"))) {
			request_headers->If_Unmodified_Since =
				(char *)malloc(s_header_body + 1);
			strncpy(request_headers->If_Unmodified_Since, header_body, s_header_body);
			request_headers->If_Unmodified_Since[s_header_body] = '\0';
			request_headers->s_If_Unmodified_Since = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Max-Forwards", s_header_name, strlen("Max-Forwards"))) {
			request_headers->Max_Forwards = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->Max_Forwards, header_body, s_header_body);
			request_headers->Max_Forwards[s_header_body] = '\0';
			request_headers->s_Max_Forwards = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Proxy-Authorization", s_header_name, strlen("Proxy-Authorization"))) {
			request_headers->Proxy_Authorization = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->Proxy_Authorization, header_body,
					s_header_body);
			request_headers->Proxy_Authorization[s_header_body] = '\0';
			request_headers->s_Proxy_Authorization = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Range", s_header_name, strlen("Range"))) {
			request_headers->Range = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->Range, header_body, s_header_body);
			request_headers->Range[s_header_body] = '\0';
			request_headers->s_Range = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Referer", s_header_name, strlen("Referer"))) {
			request_headers->Referer = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->Referer, header_body, s_header_body);
			request_headers->Referer[s_header_body] = '\0';
			request_headers->s_Referer = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "TE", s_header_name, strlen("TE"))) {
			request_headers->TE = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->TE, header_body, s_header_body);
			request_headers->TE[s_header_body] = '\0';
			request_headers->s_TE = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "User-Agent", s_header_name, strlen("User-Agent"))) {
			request_headers->User_Agent = (char *)malloc(s_header_body + 1);
			strncpy(request_headers->User_Agent, header_body, s_header_body);
			request_headers->User_Agent[s_header_body] = '\0';
			request_headers->s_User_Agent = s_header_body + 1;
		}
	}
	if (entity_headers != NULL) {
		if (str_CIEQ(header_name, "Allow", s_header_name, strlen("Allow"))) {
			entity_headers->Allow = (char *)malloc(s_header_body + 1);
			strncpy(entity_headers->Allow, header_body, s_header_body);
			entity_headers->Allow[s_header_body] = '\0';
			entity_headers->s_Allow = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Content-Encoding", s_header_name, strlen("Content-Encoding"))) {
			entity_headers->Content_Encoding = (char *)malloc(s_header_body + 1);
			strncpy(entity_headers->Content_Encoding, header_body,
					s_header_body);
			entity_headers->Content_Encoding[s_header_body] = '\0';
			entity_headers->s_Content_Encoding = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Content-Language", s_header_name, strlen("Content-Language"))) {
			entity_headers->Content_Language = (char *)malloc(s_header_body + 1);
			strncpy(entity_headers->Content_Language, header_body,
					s_header_body);
			entity_headers->Content_Language[s_header_body] = '\0';
			entity_headers->s_Content_Language = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Content-Length", s_header_name, strlen("Content-Length"))) {
			char *cstr_content_length = (char *)malloc(s_header_body + 1);
			strncpy(cstr_content_length, header_body, s_header_body);
			cstr_content_length[s_header_body] = '\0';
			entity_headers->Content_Length = atoi(cstr_content_length);
			free(cstr_content_length);
		}
		if (str_CIEQ(header_name, "Content-Location", s_header_name, strlen("Content-Location"))) {
			entity_headers->Content_Location = (char *)malloc(s_header_body + 1);
			strncpy(entity_headers->Content_Location, header_body,
					s_header_body);
			entity_headers->Content_Location[s_header_body] = '\0';
			entity_headers->s_Content_Location = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Content-MD5", s_header_name, strlen("Content-MD5"))) {
			entity_headers->Content_MD5 = (char *)malloc(s_header_body + 1);
			strncpy(entity_headers->Content_MD5, header_body, s_header_body);
			entity_headers->Content_MD5[s_header_body] = '\0';
			entity_headers->s_Content_MD5 = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Content-Range", s_header_name, strlen("Content-Range"))) {
			entity_headers->Content_Range = (char *)malloc(s_header_body + 1);
			strncpy(entity_headers->Content_Range, header_body, s_header_body);
			entity_headers->Content_Range[s_header_body] = '\0';
			entity_headers->s_Content_Range = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Content-Type", s_header_name, strlen("Content-Type"))) {
			entity_headers->Content_Type = (char *)malloc(s_header_body + 1);
			strncpy(entity_headers->Content_Type, header_body, s_header_body);
			entity_headers->Content_Type[s_header_body] = '\0';
			entity_headers->s_Content_Type = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Expires", s_header_name, strlen("Expires"))) {
			entity_headers->Expires = (char *)malloc(s_header_body + 1);
			strncpy(entity_headers->Expires, header_body, s_header_body);
			entity_headers->Expires[s_header_body] = '\0';
			entity_headers->s_Expires = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "Last-Modified", s_header_name, strlen("Last-Modified"))) {
			entity_headers->Last_Modified = (char *)malloc(s_header_body + 1);
			strncpy(entity_headers->Last_Modified, header_body, s_header_body);
			entity_headers->Last_Modified[s_header_body] = '\0';
			entity_headers->s_Last_Modified = s_header_body + 1;
		}
		if (str_CIEQ(header_name, "extension-header", s_header_name, strlen("extension-header"))) {
			entity_headers->Extension_Header = (char *)malloc(s_header_body + 1);
			strncpy(entity_headers->Extension_Header, header_body,
					s_header_body);
			entity_headers->Extension_Header[s_header_body] = '\0';
			entity_headers->s_Extension_Header = s_header_body + 1;
		}
	}

	free(out);
	free(out_lens);
	return 0;
}
