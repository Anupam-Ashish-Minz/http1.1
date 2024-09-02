#include "http_response.h"
#include <stdio.h>

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

struct HttpResponse create_response(enum STATUS_CODE status_code, char *body,
									size_t s_body) {
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

	return response;
}
