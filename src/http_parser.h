#ifndef _HTTP_PARSER_H
#define _HTTP_PARSER_H

#include "char_array.h"
#include "http_headers.h"
#include <stdbool.h>
#include <stddef.h>

enum HTTP_METHOD {
	GET,
	POST,
	PUT,
	DELETE,
};

enum HTTP_VERSION { HTTP_1_1 };

struct RequestHeaders {
	char *Accept;
	char *Accept_Charset;
	char *Accept_Encoding;
	char *Accept_Language;
	char *Authorization;
	char *Expect;
	char *From;
	char *Host;
	char *If_Match;
	char *If_Modified_Since;
	char *If_None_Match;
	char *If_Range;
	char *If_Unmodified_Since;
	char *Max_Forwards;
	char *Proxy_Authorization;
	char *Range;
	char *Referer;
	char *TE;
	char *User_Agent;
	size_t s_Accept;
	size_t s_Accept_Charset;
	size_t s_Accept_Encoding;
	size_t s_Accept_Language;
	size_t s_Authorization;
	size_t s_Expect;
	size_t s_From;
	size_t s_Host;
	size_t s_If_Match;
	size_t s_If_Modified_Since;
	size_t s_If_None_Match;
	size_t s_If_Range;
	size_t s_If_Unmodified_Since;
	size_t s_Max_Forwards;
	size_t s_Proxy_Authorization;
	size_t s_Range;
	size_t s_Referer;
	size_t s_TE;
	size_t s_User_Agent;
};

struct HttpRequest {
	enum HTTP_METHOD method;
	char *requri;
	size_t requri_s;
	enum HTTP_VERSION version;
	struct GeneralHeaders general_headers;
	struct RequestHeaders request_headers;
	struct EntityHeaders entity_headers;
};

struct HttpRequest init_request_obj();
struct RequestHeaders init_request_headers();

int parse_http_request(char *request, size_t request_s,
					   struct HttpRequest *ret);

int parse_header(char *header, size_t s_header,
				 struct GeneralHeaders *general_headers,
				 struct RequestHeaders *request_headers,
				 struct EntityHeaders *entity_headers);

int dealloc_general_headers(struct GeneralHeaders *general_headers);
int dealloc_request_headers(struct RequestHeaders *reqeust_headers);
int dealloc_entity_headers(struct EntityHeaders *entity_headers);

int dealloc_request(struct HttpRequest *request);

#define TOLOWER                                                                \
	(string, len) {                                                            \
		char *outstr = (char *)malloc(len * sizeof(char));                     \
		strncpy(outstr, string, len);                                          \
		for (int i = 0; i < len; i++) {                                        \
			outstr[i] = tolower(outstr[i]);                                    \
		}                                                                      \
	}


bool str_CIEQ(char *a, char *b, int a_len, int b_len);

#endif
