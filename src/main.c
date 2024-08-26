#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "char_array.h"
#include "http_parser.h"

#define PORT 4000
#define MSBUF_MXLEN 1048576

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
		// parse_http(buf, msg_size);

		printf("%s\n", buf);
		write(client, "hi", 2);
		close(client);
	}

	close(server);

	return 0;
}
