#include "http_headers.h"

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
