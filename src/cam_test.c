#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	FILE *fp;

	while(1)
	{
		printf("press any key to take a picture.\n");
		getchar();
		if(execl("/usr/bin/raspistill", "raspistill","-t", "1000", "-o", "image.jpg", NULL) <0)
		{
			printf("ERROR : Capture error\n");
			exit(1);
		}
		
		if((fp = fopen("./image.jpg", "rb")) == NULL)
		{
			printf("ERROR : Cannot found image.\n");
			exit(1);
		}
		else
			printf("GOOD\n");
	}
	return 0;
}
