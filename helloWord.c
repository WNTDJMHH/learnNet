#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

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
		if(send(newfd, word, strlen(word), 0) < 0)
		{
			perror("write to newfd faile ");
			continue;
		}
		close(newfd);
	
	
	}		
	
	close(socketFd);
    printf("hello world!\n");
    return 1;
}
