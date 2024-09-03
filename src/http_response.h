#ifndef _HTTP_RESPONSE_h
#define _HTTP_RESPONSE_h

#include "http_headers.h"
#include <stddef.h>

// Response      = Status-Line               ; Section 6.1
// 			   *(( general-header        ; Section 4.5
// 				| response-header        ; Section 6.2
// 				| entity-header ) CRLF)  ; Section 7.1
// 			   CRLF
// 			   [ message-body ]          ; Section 7.2

struct ResponseHeaders {
	char *Accept_Ranges;
	unsigned int Age;
	char *Etag;
	char *Location;
	char *Proxy_Authenticate;
	char *Retry_After;
	char *Server;
	char *Vary;
	char *WWW_Authenticate;

	size_t s_Accept_Ranges;
	size_t s_Etag;
	size_t s_Location;
	size_t s_Proxy_Authenticate;
	size_t s_Retry_After;
	size_t s_Server;
	size_t s_Vary;
	size_t s_WWW_Authenticate;
};

enum STATUS_CODE {
	STATUS_CODE_CONTINUE = 100,
	STATUS_CODE_SWITCHING_PROTOCOLS = 101,
	STATUS_CODE_OK = 200,
	STATUS_CODE_CREATED = 201,
	STATUS_CODE_ACCEPTED = 202,
	STATUS_CODE_NON_AUTHORITATIVE_INFORMATION = 203,
	STATUS_CODE_NO_CONTENT = 204,
	STATUS_CODE_RESET_CONTENT = 205,
	STATUS_CODE_PARTIAL_CONTENT = 206,
	STATUS_CODE_MULTIPLE_CHOICES = 300,
	STATUS_CODE_MOVED_PERMANENTLY = 301,
	STATUS_CODE_FOUND = 302,
	STATUS_CODE_SEE_OTHER = 303,
	STATUS_CODE_NOT_MODIFIED = 304,
	STATUS_CODE_USE_PROXY = 305,
	STATUS_CODE_TEMPORARY_REDIRECT = 307,
	STATUS_CODE_BAD_REQUEST = 400,
	STATUS_CODE_UNAUTHORIZED = 401,
	STATUS_CODE_PAYMENT_REQUIRED = 402,
	STATUS_CODE_FORBIDDEN = 403,
	STATUS_CODE_NOT_FOUND = 404,
	STATUS_CODE_METHOD_NOT_ALLOWED = 405,
	STATUS_CODE_NOT_ACCEPTABLE = 406,
	STATUS_CODE_PROXY_AUTHENTICATION_REQUIRED = 407,
	STATUS_CODE_REQUEST_TIME_OUT = 408,
	STATUS_CODE_CONFLICT = 409,
	STATUS_CODE_GONE = 410,
	STATUS_CODE_LENGTH_REQUIRED = 411,
	STATUS_CODE_PRECONDITION_FAILED = 412,
	STATUS_CODE_REQUEST_ENTITY_TOO_LARGE = 413,
	STATUS_CODE_REQUEST_URI_TOO_LARGE = 414,
	STATUS_CODE_UNSUPPORTED_MEDIA_TYPE = 415,
	STATUS_CODE_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
	STATUS_CODE_EXPECTATION_FAILED = 417,
	STATUS_CODE_INTERNAL_SERVER_ERROR = 500,
	STATUS_CODE_NOT_IMPLEMENTED = 501,
	STATUS_CODE_BAD_GATEWAY = 502,
	STATUS_CODE_SERVICE_UNAVAILABLE = 503,
	STATUS_CODE_GATEWAY_TIME_OUT = 504,
	STATUS_CODE_HTTP_VERSION_NOT_SUPPORTED = 505
};

struct HttpResponse {
	char *http_version;
	size_t s_http_version;
	enum STATUS_CODE status_code;
	struct GeneralHeaders general_headers;
	struct ResponseHeaders response_headers;
	struct EntityHeaders entity_headers;

	char *body;
	size_t s_body;
};

int create_response(enum STATUS_CODE status_code, char *body, size_t s_body, char *out, int out_max_len);

struct ResponseHeaders init_response_headers();

int stringify_response_headers(struct ResponseHeaders headers, char *out, int index, size_t out_max_len);

#endif
