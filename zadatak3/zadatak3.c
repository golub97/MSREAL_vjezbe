#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

void citanje_prekidaca(char *, char *);
void citanje_tastera(const char *, const char *, float *);
void upali_diode(const long int *, const float *);

int main ()
{
	//tasteri

	//prekidaci
	char sval3, sval4;

	//diode
	float percentage = 0;
	long int period = 20000L;

	while(1)
	{
		upali_diode(&period, &percentage);

		citanje_prekidaca(&sval3, &sval4);

		citanje_tastera(&sval3, &sval4, &percentage);
	}
}
void citanje_prekidaca(char *sval3, char *sval4)
{
		static FILE *fp2;
		static char *str2;
		static int num_of_bytes2 = 6;

		//Citanje vrednosti prekidaca
		fp2 = fopen ("/dev/switch", "r");
		if(fp2 == NULL)
		{
			puts("Problem pri otvaranju /dev/switch");
			exit(-1);
		}


		str2 = (char *)malloc(num_of_bytes2 + 1);
		getline(&str2, &num_of_bytes2, fp2);

		if(fclose(fp2))
		{
			puts("Problem pri zatvaranju /dev/switch");
			exit(-1);
		}

		//sval1 = str2[2] - 48;
		//sval2 = str2[3] - 48;
		*sval3 = str2[4] - 48;
		*sval4 = str2[5] - 48;
		free(str2);
}
void citanje_tastera(const char *sval3, const char *sval4, float *percentage)
{
		static FILE* fp1;
		static char *str1;
		static int num_of_bytes1 = 6;
		static dozvola1 = 1, dozvola2 = 1;
		static char stanje = 0;
		static char tval3, tval4;

		//Citanje vrednosti tastera
		fp1 = fopen ("/dev/button", "r");
		if(fp1 == NULL)
		{
			puts("Problem pri otvaranju /dev/button");
			exit(-1);
		}

		str1 = (char *)malloc(num_of_bytes1 + 1);
		getline(&str1, &num_of_bytes1, fp1);

		if(fclose(fp1))
		{
			puts("Problem pri zatvaranju /dev/button");
			exit(-1);
		}

		//tval1 = str1[2] - 48;
		//tval2 = str1[3] - 48;
		tval3 = str1[4] - 48;
		tval4 = str1[5] - 48;
		free(str1);

		stanje = (*sval4 | (*sval3 << 1));

		if(tval4 && dozvola1)
		{
			dozvola1 = 0;

			switch(stanje)
			{
				case 0:
					break;
				case 1:
					*percentage += 0.1;
					break;
				case 2:
					*percentage += 0.2;
					break;
				case 3:
					*percentage += 0.3;
					break;
				default:
					assert(0);
					break;
			}

			if(*percentage > 1)
				*percentage = 1;

		}if(!tval4) dozvola1 = 1;

		if(tval3 && dozvola2)
		{
			dozvola2 = 0;

			switch(stanje)
			{
				case 0:
					break;
				case 1:
					*percentage -= 0.1;
					break;
				case 2:
					*percentage -= 0.2;
					break;
				case 3:
					*percentage -= 0.3;
					break;
				default:
					assert(0);
					break;
			}

			if(*percentage < 0)
				*percentage = 0;

		}if(!tval3) dozvola2 = 1;
}
void upali_diode(const long int *period, const float *percentage)
{
		static FILE* fp3;

		//upali diode

		fp3 = fopen("/dev/led", "w");

		if(fp3 == NULL)
		{
			printf("Problem pri zatvaranju /dev/led\n");
			exit(-1);
		}

		fputs("0x0F\n", fp3);
		if(fclose(fp3))

		{
			printf("Problem pri zatvaranju /dev/led\n");
			exit(-1);
		}

		usleep((*percentage)*(*period));

		//ugasio diode

		fp3 = fopen("/dev/led", "w");
		if(fp3 == NULL)
		{
			printf("Problem pri otvaranju /dev/led\n");
			exit(-1);
		}

		fputs("0x00\n", fp3);

		if(fclose(fp3))
		{
			printf("Problem pri zatvaranju /dev/led\n");
			exit(-1);
		}
		usleep( (1 -(*percentage)) * (*period) );
}
