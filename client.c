#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORTNUM 8000

#define COMPLETE "#complete&"
#define QUIT "#quit&"

int main()
{
	int sd;
	char buf[256];
	struct sockaddr_in sin;
	int len = 0;

	memset((char *)&sin, '\0', sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORTNUM);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	if(connect(sd, (struct sockaddr *)&sin, sizeof(sin)))
	{
		perror("connect");
		exit(1);
	}

	if(recv(sd, buf, sizeof(buf), 0) == -1)
	{
		perror("recv");
		exit(1);
	}

	printf("From Server : %s\n", buf);

	while(1)
	{
		memset(buf, '\0', sizeof(buf));
		scanf("%s", buf);

		if(send(sd, buf, strlen(buf)+1, 0) == -1)
		{
			perror("send");
			exit(1);
		}

		while(1)
		{
			if(len = recv(sd, buf, sizeof(buf), 0) == -1)
			{
				perror("recv");
				exit(1);
			}

			buf[len] = '\0';
			
			if(strncmp(buf, COMPLETE, strlen(COMPLETE)) == 0)
			{
				break;
			}
		}
	}

	close(sd);

	return 0;
}
