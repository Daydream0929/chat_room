#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

const int MAX_LINE = 4096;
const char* IP_ADDR = "139.196.215.162";  // aliyun 轻量级服务器

int main()
{
	int					sockfd, n;
	char				recvline[MAX_LINE + 1];
	struct sockaddr_in	servaddr;

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("socket error\n");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(13);	/* daytime server */
	if (inet_pton(AF_INET, IP_ADDR, &servaddr.sin_addr) <= 0)
		printf("inet_pton error for %s\n", IP_ADDR);

	if (connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0)
		printf("connect error\n");

	while ( (n = read(sockfd, recvline, MAX_LINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			printf("fputs error\n");
	}
	if (n < 0)
		printf("read error\n");

	exit(0);
}
