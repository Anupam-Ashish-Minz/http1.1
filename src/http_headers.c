#include "http_headers.h"

struct GeneralHeaders init_general_headers() {
	struct GeneralHeaders general_headers;
	general_headers.Cache_Control = NULL;
	general_headers.Connection = NULL;
	general_headers.Date = NULL;
	general_headers.Pragma = NULL;
	general_headers.Trailer = NULL;
	general_headers.Transfer_Encoding = NULL;
	general_headers.Upgrade = NULL;
	general_headers.Via = NULL;
	general_headers.Warning = NULL;
	general_headers.s_Cache_Control = 0;
	general_headers.s_Connection = 0;
	general_headers.s_Date = 0;
	general_headers.s_Pragma = 0;
	general_headers.s_Trailer = 0;
	general_headers.s_Transfer_Encoding = 0;
	general_headers.s_Upgrade = 0;
	general_headers.s_Via = 0;
	general_headers.s_Warning = 0;
	return general_headers;
}

struct EntityHeaders init_entity_headers() {
	struct EntityHeaders entity_headers;
	entity_headers.Allow = NULL;
	entity_headers.Content_Encoding = NULL;
	entity_headers.Content_Language = NULL;
	entity_headers.Content_Length = 0;
	entity_headers.Content_Location = NULL;
	entity_headers.Content_MD5 = NULL;
	entity_headers.Content_Range = NULL;
	entity_headers.Content_Type = NULL;
	entity_headers.Expires = NULL;
	entity_headers.Last_Modified = NULL;
	entity_headers.Extension_Header = NULL;
	entity_headers.s_Allow = 0;
	entity_headers.s_Content_Encoding = 0;
	entity_headers.s_Content_Language = 0;
	entity_headers.s_Content_Location = 0;
	entity_headers.s_Content_MD5 = 0;
	entity_headers.s_Content_Range = 0;
	entity_headers.s_Content_Type = 0;
	entity_headers.s_Expires = 0;
	entity_headers.s_Last_Modified = 0;
	entity_headers.s_Extension_Header = 0;
	return entity_headers;
}

