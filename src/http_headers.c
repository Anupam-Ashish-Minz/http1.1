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

int stringify_general_headers(struct GeneralHeaders headers, char *out, int index, size_t out_max_len) {
	int offset;
	if (headers.Cache_Control != NULL) {
		offset = sprintf(&out[index], "Cache-Control: %s\r\n", headers.Cache_Control);
		index += offset;
	}
	if (headers.Connection != NULL) {
		offset = sprintf(&out[index], "Connection: %s\r\n", headers.Connection);
		index += offset;
	}
	if (headers.Date != NULL) {
		offset = sprintf(&out[index], "Date: %s\r\n", headers.Date);
		index += offset;
	}
	if (headers.Pragma != NULL) {
		offset = sprintf(&out[index], "Pragma: %s\r\n", headers.Pragma);
		index += offset;
	}
	if (headers.Trailer != NULL) {
		offset = sprintf(&out[index], "Trailer: %s\r\n", headers.Trailer);
		index += offset;
	}
	if (headers.Transfer_Encoding != NULL) {
		offset = sprintf(&out[index], "Transfer_Encoding: %s\r\n", headers.Transfer_Encoding);
		index += offset;
	}
	if (headers.Upgrade != NULL) {
		offset = sprintf(&out[index], "Upgrade: %s\r\n", headers.Upgrade);
		index += offset;
	}
	if (headers.Via != NULL) {
		offset = sprintf(&out[index], "Via: %s\r\n", headers.Via);
		index += offset;
	}
	if (headers.Warning != NULL) {
		offset = sprintf(&out[index], "Warning: %s\r\n", headers.Warning);
		index += offset;
	}
	return index + 1; 
}
