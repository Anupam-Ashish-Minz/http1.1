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
	char *Connection;
	char *Date;
	char *Pragma;
	char *Trailer;
	char *Tranfer_Encoding;
	char *Upgrade;
	char *Via;
	char *Warning;
	size_t Connection_s;
	size_t Date_s;
	size_t Pragma_s;
	size_t Trailer_s;
	size_t Tranfer_Encoding_s;
	size_t Upgrade_s;
	size_t Via_s;
	size_t Warning_s;
};

struct RequestHeaders {
	char *Accept;
	char *Accept_Charset;
	char *Accept_Encoding;
	char *Accept_Language;
	char *Authorization;
	char *Except;
	char *From;
	char *Host;
	char *If_Match;
	size_t Accept_Charset_s;
	size_t Accept_Encoding_s;
	size_t Accept_Language_s;
	size_t Accept_s;
	size_t Authorization_s;
	size_t Except_s;
	size_t From_s;
	size_t Host_s;
	size_t If_Match_s;
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
	size_t Allow_s;
	size_t Content_Encoding_s;
	size_t Content_Language_s;
	size_t Content_Length_s;
	size_t Content_Location_s;
	size_t Content_MD5_s;
	size_t Content_Range_s;
	size_t Content_Type_s;
	size_t Expires_s;
	size_t Extension_Header_s;
	size_t Last_Modified_s;
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

int parse_http_request(char *request, size_t request_s, struct HttpRequest *ret);

#endif
