#include "http_response.h"
#include "http_headers.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ResponseHeaders init_response_headers() {
	struct ResponseHeaders response_headers = {
		.Accept_Ranges = NULL,
		.Age = 0, // Idk the default values that should be here so 0 for now, TODO change later
		.Etag = NULL,
		.Location = NULL,
		.Proxy_Authenticate = NULL,
		.Retry_After = NULL,
		.Server = NULL,
		.Vary = NULL,
		.WWW_Authenticate = NULL,

		.s_Accept_Ranges = 0,
		.s_Etag = 0,
		.s_Location = 0,
		.s_Proxy_Authenticate = 0,
		.s_Server = 0,
		.s_Vary = 0,
		.s_WWW_Authenticate = 0,
	};

	return response_headers;
}

int create_response(enum STATUS_CODE status_code, char *body,
									size_t s_body, char *out, int out_max_len) {

	struct GeneralHeaders general_headers = init_general_headers();
	struct ResponseHeaders response_headers = init_response_headers();
	struct EntityHeaders entity_headers = init_entity_headers();

	struct HttpResponse response = {
		.http_version = "http/1.1",
		.s_http_version = sizeof("http/1.1"),
		.status_code = status_code,
		.general_headers = general_headers,
		.response_headers = response_headers,
		.entity_headers = entity_headers,

		.body = body,
		.s_body = s_body, // content-length here is also there but this makes stuff more convinent
	};

	char *reason_phrase = "something";
	size_t status_line_len = strlen("HTTP/1.1") + 3 + strlen(reason_phrase);
	char *status_line = (char *)malloc(status_line_len);
	sprintf(status_line, "HTTP/1.1 %d %s\r\n", status_code, reason_phrase);

	return 0;
}

int stringify_response_headers(struct ResponseHeaders headers, char *out, int index, size_t out_max_len) {
	int offset;
	STRINGIFY_KV("Accept-Ranges", headers.Accept_Ranges, headers.s_Accept_Ranges);
	unsigned int Age; // TODO add condition about it later
	STRINGIFY_KV("Etag", headers.Etag, headers.s_Etag);
	STRINGIFY_KV("Location", headers.Location, headers.s_Location);
	STRINGIFY_KV("Proxy-Authenticate", headers.Proxy_Authenticate, headers.s_Proxy_Authenticate);
	STRINGIFY_KV("Retry-After", headers.Retry_After, headers.s_Retry_After);
	STRINGIFY_KV("Server", headers.Server, headers.s_Server);
	STRINGIFY_KV("Vary", headers.Vary, headers.s_Vary);
	STRINGIFY_KV("WWW-Authenticate", headers.WWW_Authenticate, headers.s_WWW_Authenticate);
	return index + 1;
}
