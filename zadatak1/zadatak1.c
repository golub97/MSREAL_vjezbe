#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void citanje_tastera(char *);
void citanje_prekidaca(char *, char *, char *, char *);
void odluci_koje_ces_paliti(const char *, const char *, const int *, int *);
void upali_diode(const int *);

int main ()
{
	//za tastere
	char tval4;

	//prekidaci
	char sval1, sval2, sval3, sval4;
	int suma_prekidaca = 0;

	//diode
	int led = 0;

	while(1)
	{

		citanje_tastera(&tval4);

		citanje_prekidaca(&sval1, &sval2, &sval3, &sval4);

		suma_prekidaca = sval4 + 2*sval3 + 4*sval2;

		/*if(sval1)
		{
			if(tval4 && dozvola)
			{
				dozvola = 0;

				if(sabiranje)
					sabiranje = 0;
				else
					sabiranje = 1;
			}
			if(!tval4)
				dozvola = 1;

			if(sabiranje)
			{
				led += suma_prekidaca;
				if(led > 15)
					led = 15;
			}
			else
			{
				led -= suma_prekidaca;
				if(led < 0)
					led = 0;
			}

		}*/

		odluci_koje_ces_paliti(&tval4, &sval1, &suma_prekidaca, &led);

		upali_diode(&led);

		usleep(20*100000);

	}
}

void citanje_tastera(char *tval4)
{
		//tasteri
		static FILE *fp1;
		static char *str1;
		static char tval1, tval2, tval3;
		static size_t num_of_bytes1 = 6;

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
		//tval3 = str1[4] - 48;
		*tval4 = str1[5] - 48;
		free(str1);
}
void citanje_prekidaca(char *sval1, char *sval2, char *sval3, char *sval4)
{
		//prekidaci
		static FILE *fp2;
		static char *str2;
		static size_t num_of_bytes2 = 6;


		//Citanje vrednosti prekidac
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


		*sval1 = str2[2] - 48;
		*sval2 = str2[3] - 48;
		*sval3 = str2[4] - 48;
		*sval4 = str2[5] - 48;
		free(str2);
}
void odluci_koje_ces_paliti(const char *tval4,const char *sval1, const int *suma_prekidaca, int *led)
{
		static char dozvola = 1;
		static char sabiranje = 1;

		if(*sval1)
		{
			if(*tval4 && dozvola)
			{
				dozvola = 0;

				if(sabiranje)
					sabiranje = 0;
				else
					sabiranje = 1;
			}
			if(!(*tval4))
				dozvola = 1;

			if(sabiranje)
			{
				*led += *suma_prekidaca;
				if(*led > 15)
					*led = 15;
			}
			else
			{
				*led -= *suma_prekidaca;
				if(*led < 0)
					*led = 0;
			}

		}
}
void upali_diode(const int *led)
{
		static FILE *fp3;
		static char buffer[10];

		// Upali diode
		fp3 = fopen("/dev/led", "w");
		if(fp3 == NULL)
		{
			printf("Problem pri otvaranju /dev/led\n");
			exit(-1);
		}
		sprintf(buffer, "%d", *led);
		fputs(buffer, fp3);
		if(fclose(fp3))
		{
			printf("Problem pri zatvaranju /dev/led\n");
			exit(-1);
		}
}
