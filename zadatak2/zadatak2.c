#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main ()
{
	//tasteri
	FILE *fp1;
	char *str1;
	char tval1, tval2, tval3, tval4;
	size_t num_of_bytes1 = 6;
	int dozvola = 1;

	//prekidaci
	FILE *fp2;
	char *str2;
	char sval1, sval2, sval3, sval4;
	size_t num_of_bytes2 = 6;
	int suma_prekidaca = 0;

	//diode
	FILE *fp3;
	//float percentage;
	//long int period = 20000L;
	int led = 0;
	char buffer[10];

	while(1)
	{

		//Citanje vrednosti tastera
		fp1 = fopen ("/dev/button", "r");
		if(fp1 == NULL)
		{
			puts("Problem pri otvaranju /dev/button");
			return -1;
		}

		str1 = (char *)malloc(num_of_bytes1 + 1);
		getline(&str1, &num_of_bytes1, fp1);

		if(fclose(fp1))
		{
			puts("Problem pri zatvaranju /dev/button");
			return -1;
		}


		//tval1 = str1[2] - 48;
		//tval2 = str1[3] - 48;
		//tval3 = str1[4] - 48;
		tval4 = str1[5] - 48;
		free(str1);

		//printf("Vrednosti tastera: %d %d %d %d \n", tval1, tval2, tval3, tval4);
		//sleep(1);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//Citanje vrednosti prekidac
		fp2 = fopen ("/dev/switch", "r");
		if(fp2 == NULL)
		{
			puts("Problem pri otvaranju /dev/switch");
			return -1;
		}


		str2 = (char *)malloc(num_of_bytes2 + 1);
		getline(&str2, &num_of_bytes2, fp2);

		if(fclose(fp2))
		{
			puts("Problem pri zatvaranju /dev/switch");
			return -1;
		}


		sval1 = str2[2] - 48;
		sval2 = str2[3] - 48;
		sval3 = str2[4] - 48;
		sval4 = str2[5] - 48;
		free(str2);

		//printf("Vrednosti prekidaca: %d %d %d %d \n", sval1, sval2, sval3, sval4);
		//sleep(1);

		if(tval4 && dozvola)
		{
			dozvola = 0;

			suma_prekidaca = sval4 + 2*sval3 + 4*sval2;

			if(!sval1)
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

		}
		if(!tval4)
			dozvola = 1;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Upali diode
		fp3 = fopen("/dev/led", "w");
		if(fp3 == NULL)
		{
			printf("Problem pri otvaranju /dev/led\n");
			return -1;
		}
		sprintf(buffer, "%d", led);
		fputs(buffer, fp3);
		if(fclose(fp3))
		{
			printf("Problem pri zatvaranju /dev/led\n");
			return -1;
		}
		usleep(100000);

	}
}
