#include "http_headers.h"
#include <stdio.h>
#include <string.h>

struct GeneralHeaders init_general_headers() {
	struct GeneralHeaders general_headers = {
		.Cache_Control = NULL,
		.Connection = NULL,
		.Date = NULL,
		.Pragma = NULL,
		.Trailer = NULL,
		.Transfer_Encoding = NULL,
		.Upgrade = NULL,
		.Via = NULL,
		.Warning = NULL,
		.s_Cache_Control = 0,
		.s_Connection = 0,
		.s_Date = 0,
		.s_Pragma = 0,
		.s_Trailer = 0,
		.s_Transfer_Encoding = 0,
		.s_Upgrade = 0,
		.s_Via = 0,
		.s_Warning = 0,
	};
	return general_headers;
}

struct EntityHeaders init_entity_headers() {
	struct EntityHeaders entity_headers = {
		.Allow = NULL,
		.Content_Encoding = NULL,
		.Content_Language = NULL,
		.Content_Length = 0,
		.Content_Location = NULL,
		.Content_MD5 = NULL,
		.Content_Range = NULL,
		.Content_Type = NULL,
		.Expires = NULL,
		.Last_Modified = NULL,
		.Extension_Header = NULL,
		.s_Allow = 0,
		.s_Content_Encoding = 0,
		.s_Content_Language = 0,
		.s_Content_Location = 0,
		.s_Content_MD5 = 0,
		.s_Content_Range = 0,
		.s_Content_Type = 0,
		.s_Expires = 0,
		.s_Last_Modified = 0,
		.s_Extension_Header = 0,
	};
	return entity_headers;
}

int stringify_general_headers(struct GeneralHeaders headers, char *out,
							  int index, size_t out_max_len) {
	int offset;
	STRINGIFY_KV("Cache-Control", headers.Cache_Control,
				 headers.s_Cache_Control);
	STRINGIFY_KV("Connection", headers.Connection, headers.s_Connection);
	STRINGIFY_KV("Date", headers.Date, headers.s_Date);
	STRINGIFY_KV("Pragma", headers.Pragma, headers.s_Pragma);
	STRINGIFY_KV("Trailer", headers.Trailer, headers.s_Trailer);
	STRINGIFY_KV("Transfer_Encoding", headers.Transfer_Encoding,
				 headers.s_Transfer_Encoding);
	STRINGIFY_KV("Upgrade", headers.Upgrade, headers.s_Upgrade);
	STRINGIFY_KV("Via", headers.Via, headers.s_Via);
	STRINGIFY_KV("Warning", headers.Warning, headers.s_Warning);

	return index + 1;
}

int stringify_entity_headers(struct EntityHeaders headers, char *out, int index,
							 size_t out_max_len) {
	int offset;
	STRINGIFY_KV("Allow", headers.Allow, headers.s_Allow);
	STRINGIFY_KV("Content-Encoding", headers.Content_Encoding,
				 headers.s_Content_Encoding);
	STRINGIFY_KV("Content-Language", headers.Content_Language,
				 headers.s_Content_Language);
	if (headers.Content_Length != 0) {
		if (index + sizeof("Content-Length: \r\n") + 4 > out_max_len) {
			return -1;
		}
		offset = sprintf(&out[index], "%s: %d\r\n", "Content-Length", headers.Content_Length);
		index += offset;
	}
	STRINGIFY_KV("Content-Location", headers.Content_Location,
				 headers.s_Content_Location);
	STRINGIFY_KV("Content-MD5", headers.Content_MD5, headers.s_Content_MD5);
	STRINGIFY_KV("Content-Range", headers.Content_Range,
				 headers.s_Content_Range);
	STRINGIFY_KV("Content-Type", headers.Content_Type, headers.s_Content_Type);
	STRINGIFY_KV("Expires", headers.Expires, headers.s_Expires);
	STRINGIFY_KV("Last-Modified", headers.Last_Modified,
				 headers.s_Last_Modified);
	STRINGIFY_KV("Extension_Header", headers.Extension_Header,
				 headers.s_Extension_Header);
	return index + 1;
}
