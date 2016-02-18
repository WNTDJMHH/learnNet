#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_STRING "Server: jdbhttpd/0.1.0\r\n"

/**********************************************************************/
/* Return the informational HTTP headers about a file. */
/* Parameters: the socket to print the headers on
 *             the name of the file */
/**********************************************************************/
void headers(int client, const char *filename)
{
 char buf[1024];
 (void)filename;  /* could use filename to determine file type */

 strcpy(buf, "HTTP/1.0 200 OK\r\n");
 send(client, buf, strlen(buf), 0);
 strcpy(buf, SERVER_STRING);
 send(client, buf, strlen(buf), 0);
 sprintf(buf, "Content-Type: text/html\r\n");
 send(client, buf, strlen(buf), 0);
 strcpy(buf, "\r\n");
 send(client, buf, strlen(buf), 0);
}

int main()
{
	struct sockaddr_in add_in;
	struct sockaddr_in add_peer;

	int socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketFd < 0)
	{
		perror("socket create fail"); exit(EXIT_FAILURE);
	}

	bzero(&add_in, sizeof(struct sockaddr_in));
	add_in.sin_family = AF_INET;
	add_in.sin_port = htons(7777);
	if(bind(socketFd, (struct sockaddr *)&add_in, sizeof(struct sockaddr_in)) < 0)
	{
		perror("bind socket fail");
		exit(EXIT_FAILURE);
	}
	if(listen(socketFd, 100) < 0)
	{
		perror("listen socket fail");
		exit(EXIT_FAILURE);
	}
	socklen_t add_size = sizeof(add_peer);
	while(1)
	{
		printf("wait for client .....\n");
		int newfd = accept(socketFd, (struct sockaddr *) &add_peer, &add_size) ;
		if(newfd < 0)
		{
			perror("accepte fail");
			continue;
		}
		printf("new fd is %d\n",newfd);
		char word[] = "hello, this is from server\n";
		//if(write(newfd, word, strlen(word)) < 0)
		headers(newfd,NULL);
		if(send(newfd, word, strlen(word), 0) < 0)
		{
			perror("write to newfd faile ");
			continue;
		}
		close(newfd);
		printf("send data ok>>>>\n");
	
	
	}		
	
	close(socketFd);
    printf("hello world!\n");
    return 1;
}
