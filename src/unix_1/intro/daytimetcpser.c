#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

const int MAX_LINE = 4096;
const char* IP_ADDR = "139.196.215.162";  // aliyun 轻量级服务器
const int LISTENQ = 1024;

int Socket(int family, int type, int protocol)
{
    int n;
    if ((n = socket(family, type, protocol)) < 0)
        printf("socket error\n");
    return(n);
}

int Accept(int fd, struct sockaddr *sa, socklen_t *salenptr)
{
	int	n;

again:
	if ( (n = accept(fd, sa, salenptr)) < 0) {
#ifdef	EPROTO
		if (errno == EPROTO || errno == ECONNABORTED)
#else
		if (errno == ECONNABORTED)
#endif
			goto again;
		else
			printf("accept error\n");
	}
	return(n);
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (bind(fd, sa, salen) < 0)
		printf("bind error\n");    
}

void Listen(int fd, int backlog)
{
	char *ptr;

	if ( (ptr = getenv("LISTENQ")) != NULL)
		backlog = atoi(ptr);

	if (listen(fd, backlog) < 0)
		printf("listen error\n");
}

void Write(int fd, void *ptr, size_t nbytes)
{
	if (write(fd, ptr, nbytes) != nbytes)
		printf("write error\n");
}

void Close(int fd)
{
	if (close(fd) == -1)
		printf("close error\n");
}

int main()
{
	int listenfd, connfd;
	struct sockaddr_in	servaddr;
    char buff[MAX_LINE];
    time_t ticks;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port   = htons(13);	/* daytime server */

    Bind(listenfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

	for ( ; ; ) {
        connfd = Accept(listenfd, (struct sockaddr*) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));

        Close(connfd);
    } 
}
