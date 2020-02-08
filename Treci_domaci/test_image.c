#include "figure.h"

#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

int citanje_tastera(char *, char *, char *, char *);

int main(void)
{
	/*int i, j;
	FILE* fp;
	srand(time(NULL));

	crno();
	//kadar();

	for(i = 0; i < 6; ++i)
	{
		j = rand() % 4;

		printf("%d\n", j);

		switch(j)
		{
			case(0):
				krug(59 + i*88);
				break;
			case(1):
				trougao(59 + i*88);
				break;
			case(2):
				iks(59 + i*88);
				break;
			case(3):
				kvadrat(59 + i*88);
				break;
			default:
				break;
		}
	}

	/*for(x = 1; x < 6; x+=3)
		krug(59 + x*88);*/
	char tval[4];
	int dozvola[4] = {1, 1, 1, 1};
	int i = 0;
	while(i != 6)
	{
		citanje_tastera(tval, tval+1, tval+2, tval+3);
		if(tval[0] && dozvola[0])
		{
			dozvola[0] = 0;
			printf("%d\n", 1);
			++i;
		}
		if(!tval[0])
			dozvola[0] = 1;
		if(tval[1] && dozvola[1])
		{
			dozvola[1] = 0;
			printf("%d\n", 2);
			++i;
		}
		if(!tval[1])
			dozvola[1] = 1;
		if(tval[2] && dozvola[2])
		{
			dozvola[2] = 0;
			printf("%d\n", 3);
			++i;
		}
		if(!tval[2])
			dozvola[2] = 1;
		if(tval[3] && dozvola[3])
		{
			dozvola[3] = 0;
			printf("%d\n", 4);
			++i;
		}
		if(!tval[3])
			dozvola[3] = 1;

	}
	return 0;
}

int citanje_tastera(char *tval1, char *tval2, char *tval3, char *tval4)
{
	FILE *fp;
	char *str;
	size_t num_of_bytes = 6;
	int temp = 0;
	do
	{
		//Citanje vrednosti tastera
		fp = fopen("/dev/button", "r");
		if(fp==NULL)
		{
			puts("Problem pri otvaranju /dev/button");
			return -1;
		}
		str = (char *)malloc(num_of_bytes+1);
		getline(&str, &num_of_bytes, fp);
		if(fclose(fp))
		{
			puts("Problem pri zatvaranju /dev/button");
			return -1;
		}
		*tval1 = str[2] - 48;
		*tval2 = str[3] - 48;
		*tval3 = str[4] - 48;
		*tval4 = str[5] - 48;
		free(str);
		//printf("Vrednosti tastera: %d %d %d %d\n", tval1, tval2, tval3, tval4);
		usleep(10000);
	}while(!(*tval1 || *tval2 || *tval3 || *tval4));
}
