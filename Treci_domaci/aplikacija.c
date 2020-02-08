#include "figure.h"
#include "smile.h"
#include "sad_smile.h"
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#define crtanje(i) 59+i*88
#define CRVENA 0xF000
#define ZELENA 0x0F00

void kombinacija(int *);

int main(void)
{
	FILE *fp;
	srand(time(NULL));
	char *str;
	char tval1, tval2, tval3, tval4;
	int dozvola1 = 1, dozvola2 = 1, dozvola3 = 1, dozvola4 = 1;
	int i, broj_pogodaka;
	size_t num_of_bytes = 6;
	int niz[6];
	int x, y;

	while(1)
	{
		broj_pogodaka = 0, i = 0;
		crno(1);
		kombinacija(niz);
		sleep(2);
		crno(2);
		while(i != 6)
		{
			//citanje vrijednosti tastera
			fp = fopen("/dev/button", "r");
			if(fp == NULL)
			{
				printf("Problem pri otvaranju /dev/button\n");
				return -1;
			}

			str = (char *)malloc(num_of_bytes+1);
			getline(&str, &num_of_bytes, fp);

			if(fclose(fp))
			{
				printf("problem pri zatvaranju /dev/button");
				return -1;
			}

			tval1 = str[2] - 48;
			tval2 = str[3] - 48;
			tval3 = str[4] - 48;
			tval4 = str[5] - 48;

			free(str);

			if(tval1 && dozvola1)
			{
				dozvola1 = 0;
				printf("%d\t", 1);
				printf("%d\n", niz[i]);
			if(niz[i] == 1) broj_pogodaka++;
			krug(crtanje(i), (niz[i] == 1) ? ZELENA : CRVENA);
			i++;
			}
			if(!tval1)
				dozvola1 = 1;
			if(tval2 && dozvola2)
			{
				dozvola2 = 0;
				printf("%d\t", 2);
				printf("%d\n", niz[i]);
				if(niz[i] == 2) broj_pogodaka++;
				trougao(crtanje(i), (niz[i] == 2) ? ZELENA : CRVENA);
				++i;
			}
			if(!tval2)
				dozvola2 = 1;
			if(tval3 && dozvola3)
			{
				dozvola3 = 0;
				printf("%d\t", 3);
				printf("%d\n", niz[i]);
				if(niz[i] == 3) broj_pogodaka++;
				iks(crtanje(i), (niz[i] == 3) ? ZELENA : CRVENA);
				++i;
			}
			if(!tval3)
				dozvola3 = 1;
			if(tval4 && dozvola4)
			{
				dozvola4 = 0;
				printf("%d\t", 4);
				printf("%d\n", niz[i]);
				if(niz[i] == 4) broj_pogodaka++;
				kvadrat(crtanje(i), (niz[i] == 4) ? ZELENA : CRVENA);
				++i;
			}
			if(!tval4)
				dozvola4 = 1;
			usleep(50000);
		}


		printf("broj pogodaka je: %d\n", broj_pogodaka);

		if(broj_pogodaka == 6)
		{
			for(y = 0; y < 125; y++)
				for(x = 0; x < 200; x++)
				{
					fp = fopen("/dev/vga_dma", "w");
					fprintf(fp,"%d,%d,%#04x\n", x+219, y+299, Smile[y*200+x]);
					fclose(fp);
				}
		}
		else
		{
			for(y = 0; y < 112; y++)
				for(x = 0; x < 200; x++)
				{
					fp = fopen("/dev/vga_dma", "w");
					fprintf(fp,"%d,%d,%#04x\n", x+219, y+299, Sad_smile[y*200+x]);
					fclose(fp);
				}

		}
	}
	return 0;
}
void kombinacija(int *niz)
{
	int i, j;

	for(i = 0; i < 6; ++i)
	{
		j = (rand() % 4) + 1;
		niz[i] = j;

		switch(j)
		{
			case(1):
				krug(crtanje(i), 0xFFFF);
				break;
			case(2):
				trougao(crtanje(i), 0xFFFF);
				break;
			case(3):
				iks(crtanje(i), 0xFFFF);
				break;
			case(4):
				kvadrat(crtanje(i), 0xFFFF);
				break;
			default:
				break;
		}
	}
}
