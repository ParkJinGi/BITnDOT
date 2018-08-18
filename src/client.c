#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNUM 9502
#define IP_ADDR "127.0.0.1"

#define COMPLETE "#complete&"
#define QUIT "#quit&"

int main()
{
	int sd;
	char buf[BUFSIZ] = {'\0'};
	struct sockaddr_in sin;
	int len = 0, q_flag = 0;
	int fd;

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr(IP_ADDR);

	// Make socket (TCP : SOCK_STREAM)
	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	// CONNECT (Request connection to server)
	if(connect(sd, (struct sockaddr *)&sin, sizeof(sin)))
	{
		perror("connect");
		exit(1);
	}
	
	// Read server's message
	if((len = read(sd, buf, BUFSIZ)) == -1)
	{
		perror("read");
		exit(1);
	}
	
	buf[len] = '\0';
	printf("From Server : %s\n", buf);
	
	// RUN CLIENT
	while(1)
	{
		// Send to SERVER
		memset(buf, '\0', BUFSIZ);
		scanf("%s", buf);

		// -----
		if(strncmp(buf, QUIT, strlen(QUIT)) == 0)
		{
			if(write(sd, buf, strlen(buf)) == -1)
			{
				perror("write");
				exit(1);
			}
			break;
		}

		if((fd = open(buf, O_RDONLY)) < 0)
		{
			perror("open");
			exit(1);
		}

		while(0 < (len = read(fd, buf, BUFSIZ-1)))
		{
			buf[len] = '\0';
			if(write(sd, buf, strlen(buf)) == -1)
			{
				perror("write");
				exit(1);
			}
			memset(buf, '\0', BUFSIZ);
		}

		close(fd);
		// -----
		
		/*
		if(write(sd, buf, strlen(buf)+1) == -1)
		{
			perror("write");
			exit(1);
		}
		*/

		// Receive from SERVER
		memset(buf, '\0', BUFSIZ);
		while(1)
		{
			if((len = read(sd, buf, BUFSIZ)) == -1)
			{
				perror("read");
				exit(1);
			}

			buf[len] = '\0';
			printf("%s\n", buf);
			
			if(strncmp(buf, COMPLETE, strlen(COMPLETE)) == 0)
			{
				// If receive "#complete&" from SERVER
				// CLIENT can send the next message to SERVER
				break;
			}
			else if(strncmp(buf, QUIT, strlen(QUIT)) == 0)
			{
				// If receive "#quit&" from SERVER
				// CLIENT terminates the connection with SERVER
				q_flag = 1;
				break;
			}
		}

		if(q_flag == 1)
		{
			// Terminates the connection
			printf("Disconnect with Server\n");
			break;
		}
	}

	close(sd);

	return 0;
}
