#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 4000
#define MSBUF_MXLEN 1048576

struct CharArray {
	char *line;
	unsigned int size;
};

struct CharArray *new_char_array(char *line, unsigned int size) {
	struct CharArray *arr = (struct CharArray *)malloc(sizeof(struct CharArray));
	arr->line = line;
	arr->size = size;
	return arr;
}

int set_char_array(struct CharArray *arr, char *line, unsigned int size) {
	arr = (struct CharArray *)malloc(sizeof(struct CharArray));
	arr->line = line;
	arr->size = size;
	return 0;
}

struct VecCharArray {
	struct CharArray **arr;
	unsigned int len;
};

void push_char_array(struct CharArray **vec, struct CharArray *arr) {
	vec[0] = arr;
}

struct HttpPacket {
	char *method;
	char *path;
	char *protocol;
	char **headers;
};

void parse_http(char *buf, size_t buflen) {
// GET / HTTP/1.1
// Host: localhost:4000
// User-Agent: curl/8.6.0
// Accept: */*
	int split_at = -1;
	struct CharArray *filelines[5];

	int prev = 0;
	for (int i=0; i<buflen-1; i++) {
		if (buf[i] == '\r' && buf[i+1] == '\n') {
			split_at = i;
			char *line = (char *)malloc(i-1-prev); 
			strncpy(line, &buf[prev], i-1);
			push_char_array(filelines, new_char_array(line, i-1-prev));
		}
	}
}

int main() {
	int server, client;
	struct sockaddr_in addr;
	unsigned int addrlen = sizeof(addr);
	int opt = 1;
	char *buf = (char *)malloc(MSBUF_MXLEN);

	if ((server = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("creating socket");
		return -1;
	}

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htons(INADDR_ANY);
	addr.sin_port = htons(PORT);

	setsockopt(server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

	if ((bind(server, (struct sockaddr *)&addr, addrlen)) == -1) {
		perror("bind");
		return -1;
	}

	if ((listen(server, 15)) == -1) {
		perror("listen");
		return -1;
	}

	while (1) {
		if ((client = accept(server, (struct sockaddr *)&addr, &addrlen)) == -1) {
			perror("accept");
		}
		size_t msg_size = read(client, buf, MSBUF_MXLEN);
		parse_http(buf, msg_size);

		printf("%s\n", buf);
		write(client, "hi", 2);
		close(client);
	}

	close(server);

	return 0;
}
