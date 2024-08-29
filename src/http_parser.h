#ifndef _HTTP_PARSER_H
#define _HTTP_PARSER_H

#include "char_array.h"
#include <stddef.h>

enum HTTP_METHOD {
	GET,
	POST,
	PUT,
	DELETE,
};

enum HTTP_VERSION {
	HTTP_1_1
};

struct GeneralHeaders {
	char *Cache_Control;
	char *Connection;
	char *Date;
	char *Pragma;
	char *Trailer;
	char *Transfer_Encoding;
	char *Upgrade;
	char *Via;
	char *Warning;
	size_t s_Cache_Control;
	size_t s_Connection;
	size_t s_Date;
	size_t s_Pragma;
	size_t s_Trailer;
	size_t s_Transfer_Encoding;
	size_t s_Upgrade;
	size_t s_Via;
	size_t s_Warning;
};

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

struct EntityHeaders {
	char *Allow;
	char *Content_Encoding;
	char *Content_Language;
	char *Content_Length;
	char *Content_Location;
	char *Content_MD5;
	char *Content_Range;
	char *Content_Type;
	char *Expires;
	char *Last_Modified;
	char *Extension_Header;
	size_t s_Allow;
	size_t s_Content_Encoding;
	size_t s_Content_Language;
	size_t s_Content_Length;
	size_t s_Content_Location;
	size_t s_Content_MD5;
	size_t s_Content_Range;
	size_t s_Content_Type;
	size_t s_Expires;
	size_t s_Extension_Header;
	size_t s_Last_Modified;
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

int parse_http_request(char *request, size_t request_s, struct HttpRequest *ret);

int parse_header(char *header, size_t s_header,
				 struct GeneralHeaders *general_headers,
				 struct RequestHeaders *request_headers,
				 struct EntityHeaders *entity_headers);

int dealloc_general_headers(struct GeneralHeaders *general_headers);
int dealloc_request_headers(struct RequestHeaders *reqeust_headers);
int dealloc_entity_headers(struct EntityHeaders *entity_headers);

int dealloc_request(struct HttpRequest *request);

#endif
