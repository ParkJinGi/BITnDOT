#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNUM 9500
#define IP_ADDR "127.0.0.1"

#define COMPLETE "#complete&"
#define QUIT "#quit&"

int main()
{
	char buf[BUFSIZ] = {'\0'};
	struct sockaddr_in sin, cli;
	int sd, ns, clientlen = sizeof(cli);
	int len = 0;
	int fd;

	// socket type : AF_INMET
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

	// BIND (Connect socket to IP address/Port number)
	if(bind(sd, (struct sockaddr *)&sin, sizeof(sin)))
	{
		perror("bind");
		exit(1);
	}

	// LISTEN (Notice to OS that ready to receive the requests, max=5)
	if(listen(sd, 5))
	{
		perror("listen");
		exit(1);
	}

	// accept (wait client's requests)
	if((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1)
	{
		perror("accept");
		exit(1);
	}

	// Convert client's IP address to string
	sprintf(buf, "%s", inet_ntoa(cli.sin_addr));

	printf("*** Connect with [ %s ] ***\n", buf);
	memset(buf, '\0', BUFSIZ);
	
	// Send a message to CLIENT
	sprintf(buf, "%s", "Connect with Server successfully!");
	if(write(ns, buf, strlen(buf)+1) == -1)
	{
		perror("write");
		exit(1);
	}
	
	// RUN SERVER
	while(1)
	{
		// Receive from CLIENT
		memset(buf, '\0', BUFSIZ);
		if((len = read(ns, buf, BUFSIZ)) == -1)
		{
			perror("read");
			exit(1);
		}
		
		buf[len] = '\0';

		if(strncmp(buf, QUIT, strlen(QUIT)) == 0)
		{
			// If receive "#quit&" from CLIENT
			// SERVER also sends QUIT message
			// and terminates the connection with CLIENT
			memset(buf, '\0', BUFSIZ);
			sprintf(buf, "%s", QUIT);
			if(write(ns, buf, strlen(buf)+1) == -1)
			{
				perror("write");
				exit(1);
			}

			printf("Disconnect with client\n");
			break;
		}

		printf("CLIENT : %s\n", buf);
		
		// If receive all messages from CLIENT
		// SERVER sends COMPLETE message to confirm
		memset(buf, '\0', sizeof(buf));
		sprintf(buf, "%s", COMPLETE);
		if(write(ns, buf, strlen(buf)+1) == -1)
		{
			perror("write");
			exit(1);
		}
	}
	
	close(ns);
	close(sd);

	return 0;
}
