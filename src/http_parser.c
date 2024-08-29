#include "http_parser.h"
#include "char_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_http_request(char *raw, size_t raw_s, struct HttpRequest *out) {
	int line_count = get_line_count(raw, raw_s);
	char **lines = (char **)malloc(line_count * sizeof(char **));
	int *lines_index = (int *)malloc(line_count * sizeof(int *));
	line_count = split_lines2(raw, raw_s, lines, lines_index);
	if (line_count == 0) {
		fprintf(stderr, "incorrect http package incorrect number of line: %d",
				line_count);
		return -1;
	}

	int word_count = get_word_count(lines[0], lines_index[0]);
	char **words = (char **)malloc(word_count * sizeof(char **));
	int *words_index = (int *)malloc(word_count * sizeof(int *));
	word_count = split_by_words(lines[0], lines_index[0], words, words_index);
	if (word_count == 0) {
		fprintf(stderr, "incorrect word count should be 3, is %d\n",
				word_count);
		return -1;
	}

	if (strncmp(words[0], "get", words_index[0]) == 0 ||
		strncmp(words[0], "Get", words_index[0]) == 0 ||
		strncmp(words[0], "GET", words_index[0]) == 0) {
		out->method = GET;
	} else if (strncmp(words[0], "post", words_index[0]) == 0 ||
			   strncmp(words[0], "Post", words_index[0]) == 0 ||
			   strncmp(words[0], "POST", words_index[0]) == 0) {
		out->method = POST;
	} else if (strncmp(words[0], "put", words_index[0]) == 0 ||
			   strncmp(words[0], "Put", words_index[0]) == 0 ||
			   strncmp(words[0], "PUT", words_index[0]) == 0) {
		out->method = PUT;
	} else if (strncmp(words[0], "delete", words_index[0]) == 0 ||
			   strncmp(words[0], "Delete", words_index[0]) == 0 ||
			   strncmp(words[0], "DELETE", words_index[0]) == 0) {
		out->method = DELETE;
	} else {
		fprintf(stderr, "invalid method type parsing failed\n");
		return -1;
	}
	out->requri = (char *)malloc(words_index[1] + 1);
	strncpy(out->requri, words[1], words_index[1]);
	out->requri += '\0';
	out->requri_s = words_index[1] + 1;

	free(words);
	free(words_index);
	free(lines);
	free(lines_index);

	return 0;
}

int parse_header(char *header, size_t s_header,
				 struct GeneralHeaders *general_headers,
				 struct RequestHeaders *request_headers,
				 struct EntityHeaders *entity_headers) {

	int split_count = get_split_count(header, s_header, ':');
	char **out = (char **)malloc(s_header * sizeof(char **));
	int *out_lens = (int *)malloc(split_count * sizeof(int *));

	int word_count = split_by(header, s_header, ':', out, out_lens);
	char *header_name = out[0];
	size_t s_header_name = out_lens[0];
	char *header_body = out[1];
	size_t s_header_body = out_lens[1];

	if (word_count == 0) {
		return -1;
	}
	if (general_headers != NULL) {
		if (strncmp(header_name, "Cache-Control", s_header_name) == 0) {
			general_headers->Cache_Control = (char *)malloc(s_header_body);
			strncpy(general_headers->Cache_Control, header_body, s_header_body);
			general_headers->Cache_Control += '\0';
			general_headers->s_Cache_Control = s_header_body + 1;
		}
		if (strncmp(header_name, "Connection", s_header_name) == 0) {
			general_headers->Connection = (char *)malloc(s_header_body);
			strncpy(general_headers->Connection, header_body, s_header_body);
			general_headers->Connection += '\0';
			general_headers->s_Connection = s_header_body + 1;
		}
		if (strncmp(header_name, "Date", s_header_name) == 0) {
			general_headers->Date = (char *)malloc(s_header_body);
			strncpy(general_headers->Date, header_body, s_header_body);
			general_headers->Date += '\0';
			general_headers->s_Date = s_header_body + 1;
		}
		if (strncmp(header_name, "Pragma", s_header_name) == 0) {
			general_headers->Pragma = (char *)malloc(s_header_body);
			strncpy(general_headers->Pragma, header_body, s_header_body);
			general_headers->Pragma += '\0';
			general_headers->s_Pragma = s_header_body + 1;
		}
		if (strncmp(header_name, "Trailer", s_header_name) == 0) {
			general_headers->Trailer = (char *)malloc(s_header_body);
			strncpy(general_headers->Trailer, header_body, s_header_body);
			general_headers->Trailer += '\0';
			general_headers->s_Trailer = s_header_body + 1;
		}
		if (strncmp(header_name, "Transfer-Encoding", s_header_name) == 0) {
			general_headers->Transfer_Encoding = (char *)malloc(s_header_body);
			strncpy(general_headers->Transfer_Encoding, header_body,
					s_header_body);
			general_headers->Transfer_Encoding += '\0';
			general_headers->s_Transfer_Encoding = s_header_body + 1;
		}
		if (strncmp(header_name, "Upgrade", s_header_name) == 0) {
			general_headers->Upgrade = (char *)malloc(s_header_body);
			strncpy(general_headers->Upgrade, header_body, s_header_body);
			general_headers->Upgrade += '\0';
			general_headers->s_Upgrade = s_header_body + 1;
		}
		if (strncmp(header_name, "Via", s_header_name) == 0) {
			general_headers->Via = (char *)malloc(s_header_body);
			strncpy(general_headers->Via, header_body, s_header_body);
			general_headers->Via += '\0';
			general_headers->s_Via = s_header_body + 1;
		}
		if (strncmp(header_name, "Warning", s_header_name) == 0) {
			general_headers->Warning = (char *)malloc(s_header_body);
			strncpy(general_headers->Warning, header_body, s_header_body);
			general_headers->Warning += '\0';
			general_headers->s_Warning = s_header_body + 1;
		}
	}
	if (request_headers != NULL) {
		if (strncmp(header_name, "Accept", s_header_name) == 0) {
			request_headers->Accept = (char *)malloc(s_header_body);
			strncpy(request_headers->Accept, header_body, s_header_body);
			request_headers->Accept += '\0';
			request_headers->s_Accept = s_header_body + 1;
		}
		if (strncmp(header_name, "Accept-Charset", s_header_name) == 0) {
			request_headers->Accept_Charset = (char *)malloc(s_header_body);
			strncpy(request_headers->Accept_Charset, header_body,
					s_header_body);
			request_headers->Accept_Charset += '\0';
			request_headers->s_Accept_Charset = s_header_body + 1;
		}
		if (strncmp(header_name, "Accept-Encoding", s_header_name) == 0) {
			request_headers->Accept_Encoding = (char *)malloc(s_header_body);
			strncpy(request_headers->Accept_Encoding, header_body,
					s_header_body);
			request_headers->Accept_Encoding += '\0';
			request_headers->s_Accept_Encoding = s_header_body + 1;
		}
		if (strncmp(header_name, "Accept-Language", s_header_name) == 0) {
			request_headers->Accept_Language = (char *)malloc(s_header_body);
			strncpy(request_headers->Accept_Language, header_body,
					s_header_body);
			request_headers->Accept_Language += '\0';
			request_headers->s_Accept_Language = s_header_body + 1;
		}
		if (strncmp(header_name, "Authorization", s_header_name) == 0) {
			request_headers->Authorization = (char *)malloc(s_header_body);
			strncpy(request_headers->Authorization, header_body, s_header_body);
			request_headers->Authorization += '\0';
			request_headers->s_Authorization = s_header_body + 1;
		}
		if (strncmp(header_name, "Expect", s_header_name) == 0) {
			request_headers->Expect = (char *)malloc(s_header_body);
			strncpy(request_headers->Expect, header_body, s_header_body);
			request_headers->Expect += '\0';
			request_headers->s_Expect = s_header_body + 1;
		}
		if (strncmp(header_name, "From", s_header_name) == 0) {
			request_headers->From = (char *)malloc(s_header_body);
			strncpy(request_headers->From, header_body, s_header_body);
			request_headers->From += '\0';
			request_headers->s_From = s_header_body + 1;
		}
		if (strncmp(header_name, "Host", s_header_name) == 0) {
			request_headers->Host = (char *)malloc(s_header_body);
			strncpy(request_headers->Host, header_body, s_header_body);
			request_headers->Host += '\0';
			request_headers->s_Host = s_header_body + 1;
		}
		if (strncmp(header_name, "If-Match", s_header_name) == 0) {
			request_headers->If_Match = (char *)malloc(s_header_body);
			strncpy(request_headers->If_Match, header_body, s_header_body);
			request_headers->If_Match += '\0';
			request_headers->s_If_Match = s_header_body + 1;
		}
		if (strncmp(header_name, "If-Modified-Since", s_header_name) == 0) {
			request_headers->If_Modified_Since = (char *)malloc(s_header_body);
			strncpy(request_headers->If_Modified_Since, header_body,
					s_header_body);
			request_headers->If_Modified_Since += '\0';
			request_headers->s_If_Modified_Since = s_header_body + 1;
		}
		if (strncmp(header_name, "If-None-Match", s_header_name) == 0) {
			request_headers->If_None_Match = (char *)malloc(s_header_body);
			strncpy(request_headers->If_None_Match, header_body, s_header_body);
			request_headers->If_None_Match += '\0';
			request_headers->s_If_None_Match = s_header_body + 1;
		}
		if (strncmp(header_name, "If-Range", s_header_name) == 0) {
			request_headers->If_Range = (char *)malloc(s_header_body);
			strncpy(request_headers->If_Range, header_body, s_header_body);
			request_headers->If_Range += '\0';
			request_headers->s_If_Range = s_header_body + 1;
		}
		if (strncmp(header_name, "If-Unmodified-Since", s_header_name) == 0) {
			request_headers->If_Unmodified_Since =
				(char *)malloc(s_header_body);
			strncpy(request_headers->If_Unmodified_Since, header_body,
					s_header_body);
			request_headers->If_Unmodified_Since += '\0';
			request_headers->s_If_Unmodified_Since = s_header_body + 1;
		}
		if (strncmp(header_name, "Max-Forwards", s_header_name) == 0) {
			request_headers->Max_Forwards = (char *)malloc(s_header_body);
			strncpy(request_headers->Max_Forwards, header_body, s_header_body);
			request_headers->Max_Forwards += '\0';
			request_headers->s_Max_Forwards = s_header_body + 1;
		}
		if (strncmp(header_name, "Proxy-Authorization", s_header_name) == 0) {
			request_headers->Proxy_Authorization =
				(char *)malloc(s_header_body);
			strncpy(request_headers->Proxy_Authorization, header_body,
					s_header_body);
			request_headers->Proxy_Authorization += '\0';
			request_headers->s_Proxy_Authorization = s_header_body + 1;
		}
		if (strncmp(header_name, "Range", s_header_name) == 0) {
			request_headers->Range = (char *)malloc(s_header_body);
			strncpy(request_headers->Range, header_body, s_header_body);
			request_headers->Range += '\0';
			request_headers->s_Range = s_header_body + 1;
		}
		if (strncmp(header_name, "Referer", s_header_name) == 0) {
			request_headers->Referer = (char *)malloc(s_header_body);
			strncpy(request_headers->Referer, header_body, s_header_body);
			request_headers->Referer += '\0';
			request_headers->s_Referer = s_header_body + 1;
		}
		if (strncmp(header_name, "TE", s_header_name) == 0) {
			request_headers->TE = (char *)malloc(s_header_body);
			strncpy(request_headers->TE, header_body, s_header_body);
			request_headers->TE += '\0';
			request_headers->s_TE = s_header_body + 1;
		}
		if (strncmp(header_name, "User-Agent", s_header_name) == 0) {
			request_headers->User_Agent = (char *)malloc(s_header_body);
			strncpy(request_headers->User_Agent, header_body, s_header_body);
			request_headers->User_Agent += '\0';
			request_headers->s_User_Agent = s_header_body + 1;
		}
	}
	if (entity_headers != NULL) {
		if (strncmp(header_name, "Allow", s_header_name) == 0) {
			entity_headers->Allow = (char *)malloc(s_header_body);
			strncpy(entity_headers->Allow, header_body, s_header_body);
			entity_headers->Allow += '\0';
			entity_headers->s_Allow = s_header_body + 1;
		}
		if (strncmp(header_name, "Content-Encoding", s_header_name) == 0) {
			entity_headers->Content_Encoding = (char *)malloc(s_header_body);
			strncpy(entity_headers->Content_Encoding, header_body,
					s_header_body);
			entity_headers->Content_Encoding += '\0';
			entity_headers->s_Content_Encoding = s_header_body + 1;
		}
		if (strncmp(header_name, "Content-Language", s_header_name) == 0) {
			entity_headers->Content_Language = (char *)malloc(s_header_body);
			strncpy(entity_headers->Content_Language, header_body,
					s_header_body);
			entity_headers->Content_Language += '\0';
			entity_headers->s_Content_Language = s_header_body + 1;
		}
		if (strncmp(header_name, "Content-Length", s_header_name) == 0) {
			entity_headers->Content_Length = (char *)malloc(s_header_body);
			strncpy(entity_headers->Content_Length, header_body, s_header_body);
			entity_headers->Content_Length += '\0';
			entity_headers->s_Content_Length = s_header_body + 1;
		}
		if (strncmp(header_name, "Content-Location", s_header_name) == 0) {
			entity_headers->Content_Location = (char *)malloc(s_header_body);
			strncpy(entity_headers->Content_Location, header_body,
					s_header_body);
			entity_headers->Content_Location += '\0';
			entity_headers->s_Content_Location = s_header_body + 1;
		}
		if (strncmp(header_name, "Content-MD5", s_header_name) == 0) {
			entity_headers->Content_MD5 = (char *)malloc(s_header_body);
			strncpy(entity_headers->Content_MD5, header_body, s_header_body);
			entity_headers->Content_MD5 += '\0';
			entity_headers->s_Content_MD5 = s_header_body + 1;
		}
		if (strncmp(header_name, "Content-Range", s_header_name) == 0) {
			entity_headers->Content_Range = (char *)malloc(s_header_body);
			strncpy(entity_headers->Content_Range, header_body, s_header_body);
			entity_headers->Content_Range += '\0';
			entity_headers->s_Content_Range = s_header_body + 1;
		}
		if (strncmp(header_name, "Content-Type", s_header_name) == 0) {
			entity_headers->Content_Type = (char *)malloc(s_header_body);
			strncpy(entity_headers->Content_Type, header_body, s_header_body);
			entity_headers->Content_Type += '\0';
			entity_headers->s_Content_Type = s_header_body + 1;
		}
		if (strncmp(header_name, "Expires", s_header_name) == 0) {
			entity_headers->Expires = (char *)malloc(s_header_body);
			strncpy(entity_headers->Expires, header_body, s_header_body);
			entity_headers->Expires += '\0';
			entity_headers->s_Expires = s_header_body + 1;
		}
		if (strncmp(header_name, "Last-Modified", s_header_name) == 0) {
			entity_headers->Last_Modified = (char *)malloc(s_header_body);
			strncpy(entity_headers->Last_Modified, header_body, s_header_body);
			entity_headers->Last_Modified += '\0';
			entity_headers->s_Last_Modified = s_header_body + 1;
		}
		if (strncmp(header_name, "extension-header", s_header_name) == 0) {
			entity_headers->Extension_Header = (char *)malloc(s_header_body);
			strncpy(entity_headers->Extension_Header, header_body,
					s_header_body);
			entity_headers->Extension_Header += '\0';
			entity_headers->s_Extension_Header = s_header_body + 1;
		}
	}

	free(out);
	free(out_lens);
	return 0;
}

int dealloc_general_headers(struct GeneralHeaders *general_headers) {
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
	dealloc_general_headers(&request->general_headers);
	dealloc_request_headers(&request->request_headers);
	dealloc_entity_headers(&request->entity_headers);
	if (request->requri != NULL) {
		free(request->requri);
		request->requri_s = 0;
	}
	return 0;
}
