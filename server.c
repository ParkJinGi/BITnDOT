#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNUM 8000

#define COMPLETE "#complete&"
#define QUIT "#quit&"

int main()
{
	char buf[256];
	struct sockaddr_in sin, cli;
	int sd, ns, clientlen = sizeof(cli);
	int len = 0;

	// socket type : AF_INMET
	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

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
	
	strcpy(buf, "Connect with Server successfully!");
	if(send(ns, buf, strlen(buf)+1, 0) == -1)
	{
		perror("send");
		exit(1);
	}

	// RUN SERVER
	while(1)
	{
		if(len = recv(ns, buf, strlen(buf), 0) == -1)
		{
			perror("recv");
			exit(1);
		}
		
		buf[len] = '\0';

		if(strncmp(buf, QUIT, strlen(QUIT)) == 0)
		{
			printf("Disconnect with client");
			break;
		}

		printf("CLIENT : %s\n", buf);

		strcpy(buf, COMPLETE);
		if(send(ns, buf, strlen(buf)+1, 0) == -1)
		{
			perror("send");
			exit(1);
		}
	}

	close(ns);
	close(sd);

	return 0;
}
