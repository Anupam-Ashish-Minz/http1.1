#ifndef _HTTP_HEADERS_H
#define _HTTP_HEADERS_H

#include <stddef.h>

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

struct EntityHeaders {
	char *Allow;
	char *Content_Encoding;
	char *Content_Language;
	int Content_Length;
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
	size_t s_Content_Location;
	size_t s_Content_MD5;
	size_t s_Content_Range;
	size_t s_Content_Type;
	size_t s_Expires;
	size_t s_Extension_Header;
	size_t s_Last_Modified;
};

struct GeneralHeaders init_general_headers();
struct EntityHeaders init_entity_headers();

#endif

