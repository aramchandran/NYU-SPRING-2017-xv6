/* $$$$$$$$$$ THIS PROGRAM WAS CODED BY: $$$$$$$$$$
  -|-|-     NAME: ABHISHEK RAMCHANDRAN 
  -+ +-  	REG NUM: N15073991 
  --|--		NETID: ar4996
  -[~]-     HANDLE: aramchandran  
*/
#include "types.h"
#include "stat.h"
#include "user.h"
char b[1024];
void head(int a, char *fn, int count)
{
	int i = 0, n, ln = 0;
	while((n = read(a, b, sizeof(b))) > 0 && ln < count)
	{
		for(i=0;i<=n && ln<count;i++)
		{
			if(b[i] != '\n')
			{
				printf(1,"%c",b[i]);
			}		
			else
			{
				printf(1,"\n");
				ln++;
			} 
		}
	}
}
int main(int argc, char *argv[])
{
	int fd, i;
	if(argc <= 1)
	{
		head(0, "",10);
		exit();
	}
	else if(argc==2)
	{
		for(i = 1; i < argc; i++)
		{
			if((fd = open(argv[i], 0)) < 0)
				{
					printf(1, "Filename %s does not exist Usage: head [filename].\n", argv[i]);
					exit();
				}
			head(fd, argv[i],10);
			close(fd);
		}
	}
	else if(argc==3)
	{
		char c[1024];
		strcpy(c,argv[1]);
		char *ns = c;
		if (ns[0] != '-')
		{
			printf(1, "Invalid head syntax! Usage: head -[count] [filename].\n");
			exit();
		}
		else
		{
			ns = ns + 1;
			int count = atoi(ns);
			for(i = 2; i < argc; i++)
			{
				if((fd = open(argv[i], 0)) < 0)
				{
					printf(1, "Filename %s does not exist. Usage: head -[count] [filename].\n", argv[i]);
					exit();
				}
				head(fd, argv[i], count);
				close(fd);
			}
		}
	}
	else
	{
		printf(1,"Invalid head syntax! Usage: head -[count] [filename].\n");
	}
	exit();
}