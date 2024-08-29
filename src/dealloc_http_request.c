#include "http_parser.h"
#include "char_array.h"
#include <stdlib.h>

int dealloc_general_headers(struct GeneralHeaders *general_headers) {
	if (general_headers == NULL) {
		return -1;
	}
	if (general_headers->Cache_Control != NULL) {
		free(general_headers->Cache_Control);
		general_headers->Cache_Control = NULL;
		general_headers->s_Cache_Control = 0;
	}
	if (general_headers->Connection != NULL) {
		free(general_headers->Connection);
		general_headers->Connection = NULL;
		general_headers->s_Connection = 0;
	}
	if (general_headers->Date != NULL) {
		free(general_headers->Date);
		general_headers->Date = NULL;
		general_headers->s_Date = 0;
	}
	if (general_headers->Pragma != NULL) {
		free(general_headers->Pragma);
		general_headers->Pragma = NULL;
		general_headers->s_Pragma = 0;
	}
	if (general_headers->Trailer != NULL) {
		free(general_headers->Trailer);
		general_headers->Trailer = NULL;
		general_headers->s_Trailer = 0;
	}
	if (general_headers->Transfer_Encoding != NULL) {
		free(general_headers->Transfer_Encoding);
		general_headers->Transfer_Encoding = NULL;
		general_headers->s_Transfer_Encoding = 0;
	}
	if (general_headers->Upgrade != NULL) {
		free(general_headers->Upgrade);
		general_headers->Upgrade = NULL;
		general_headers->s_Upgrade = 0;
	}
	if (general_headers->Via != NULL) {
		free(general_headers->Via);
		general_headers->Via = NULL;
		general_headers->s_Via = 0;
	}
	if (general_headers->Warning != NULL) {
		free(general_headers->Warning);
		general_headers->Warning = NULL;
		general_headers->s_Warning = 0;
	}
	return 0;
}

int dealloc_request_headers(struct RequestHeaders *request_headers) {
	if (request_headers == NULL) {
		return -1;
	}
	if (request_headers->Accept) {
		free(request_headers->Accept);
		request_headers->Accept = NULL;
		request_headers->s_Accept = 0;
	}
	if (request_headers->Accept_Charset) {
		free(request_headers->Accept_Charset);
		request_headers->Accept_Charset = NULL;
		request_headers->s_Accept_Charset = 0;
	}
	if (request_headers->Accept_Encoding) {
		free(request_headers->Accept_Encoding);
		request_headers->Accept_Encoding = NULL;
		request_headers->s_Accept_Encoding = 0;
	}
	if (request_headers->Accept_Language) {
		free(request_headers->Accept_Language);
		request_headers->Accept_Language = NULL;
		request_headers->s_Accept_Language = 0;
	}
	if (request_headers->Authorization) {
		free(request_headers->Authorization);
		request_headers->Authorization = NULL;
		request_headers->s_Authorization = 0;
	}
	if (request_headers->Expect) {
		free(request_headers->Expect);
		request_headers->Expect = NULL;
		request_headers->s_Expect = 0;
	}
	if (request_headers->From) {
		free(request_headers->From);
		request_headers->From = NULL;
		request_headers->s_From = 0;
	}
	if (request_headers->Host) {
		free(request_headers->Host);
		request_headers->Host = NULL;
		request_headers->s_Host = 0;
	}
	if (request_headers->If_Match) {
		free(request_headers->If_Match);
		request_headers->If_Match = NULL;
		request_headers->s_If_Match = 0;
	}
	if (request_headers->If_Modified_Since) {
		free(request_headers->If_Modified_Since);
		request_headers->If_Modified_Since = NULL;
		request_headers->s_If_Modified_Since = 0;
	}
	if (request_headers->If_None_Match) {
		free(request_headers->If_None_Match);
		request_headers->If_None_Match = NULL;
		request_headers->s_If_None_Match = 0;
	}
	if (request_headers->If_Range) {
		free(request_headers->If_Range);
		request_headers->If_Range = NULL;
		request_headers->s_If_Range = 0;
	}
	if (request_headers->If_Unmodified_Since) {
		free(request_headers->If_Unmodified_Since);
		request_headers->If_Unmodified_Since = NULL;
		request_headers->s_If_Unmodified_Since = 0;
	}
	if (request_headers->Max_Forwards) {
		free(request_headers->Max_Forwards);
		request_headers->Max_Forwards = NULL;
		request_headers->s_Max_Forwards = 0;
	}
	if (request_headers->Proxy_Authorization) {
		free(request_headers->Proxy_Authorization);
		request_headers->Proxy_Authorization = NULL;
		request_headers->s_Proxy_Authorization = 0;
	}
	if (request_headers->Range) {
		free(request_headers->Range);
		request_headers->Range = NULL;
		request_headers->s_Range = 0;
	}
	if (request_headers->Referer) {
		free(request_headers->Referer);
		request_headers->Referer = NULL;
		request_headers->s_Referer = 0;
	}
	if (request_headers->TE) {
		free(request_headers->TE);
		request_headers->TE = NULL;
		request_headers->s_TE = 0;
	}
	if (request_headers->User_Agent) {
		free(request_headers->User_Agent);
		request_headers->User_Agent = NULL;
		request_headers->s_User_Agent = 0;
	}
	return 0;
}

int dealloc_entity_headers(struct EntityHeaders *entity_headers) {
	if (entity_headers == NULL) {
		return -1;
	}
	if (entity_headers->Allow) {
		free(entity_headers->Allow);
		entity_headers->Allow = NULL;
		entity_headers->s_Allow = 0;
	}
	if (entity_headers->Content_Encoding) {
		free(entity_headers->Content_Encoding);
		entity_headers->Content_Encoding = NULL;
		entity_headers->s_Content_Encoding = 0;
	}
	if (entity_headers->Content_Language) {
		free(entity_headers->Content_Language);
		entity_headers->Content_Language = NULL;
		entity_headers->s_Content_Language = 0;
	}
	if (entity_headers->Content_Length) {
		free(entity_headers->Content_Length);
		entity_headers->Content_Length = NULL;
		entity_headers->s_Content_Length = 0;
	}
	if (entity_headers->Content_Location) {
		free(entity_headers->Content_Location);
		entity_headers->Content_Location = NULL;
		entity_headers->s_Content_Location = 0;
	}
	if (entity_headers->Content_MD5) {
		free(entity_headers->Content_MD5);
		entity_headers->Content_MD5 = NULL;
		entity_headers->s_Content_MD5 = 0;
	}
	if (entity_headers->Content_Range) {
		free(entity_headers->Content_Range);
		entity_headers->Content_Range = NULL;
		entity_headers->s_Content_Range = 0;
	}
	if (entity_headers->Content_Type) {
		free(entity_headers->Content_Type);
		entity_headers->Content_Type = NULL;
		entity_headers->s_Content_Type = 0;
	}
	if (entity_headers->Expires) {
		free(entity_headers->Expires);
		entity_headers->Expires = NULL;
		entity_headers->s_Expires = 0;
	}
	if (entity_headers->Last_Modified) {
		free(entity_headers->Last_Modified);
		entity_headers->Last_Modified = NULL;
		entity_headers->s_Last_Modified = 0;
	}
	if (entity_headers->Extension_Header) {
		free(entity_headers->Extension_Header);
		entity_headers->Extension_Header = NULL;
		entity_headers->s_Extension_Header = 0;
	}
	return 0;
}

int dealloc_request(struct HttpRequest *request) {
	dealloc_general_headers(&(request->general_headers));
	dealloc_request_headers(&(request->request_headers));
	dealloc_entity_headers(&(request->entity_headers));
	if (request->requri != NULL) {
		free(request->requri);
		request->requri_s = 0;
	}
	return 0;
}
