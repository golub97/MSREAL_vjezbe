#include <stdio.h>
#include <string.h>
#define BUFF_SIZE 17
 
unsigned char fifo[BUFF_SIZE];
int hex_or_dec = 16;
int glava = 0;
int rep = 0;
int broj_ispisa = 1;
 
int main()
{
	char buff[50];
	char *p;
	unsigned int z;
 
	scanf("%s", buff);
 
    	p = buff;

	if(!strncmp("num=", buff, 4))
	{
		sscanf(buff, "num=%d", &broj_ispisa);
		printf("Broj ispisa clanova promjenjen na: %d\n", broj_ispisa); 
	}
	else if(!strcmp("hex", buff))
	{
		hex_or_dec = 16;
		printf("Ispis u hex.\n");
	}
	else if(!strcmp("dec", buff))
	{
		hex_or_dec = 10;
		printf("Ispis u dec.\n");
	}
	else
	{
		while(1)
		{
        		sscanf(p, "%x,", &z);
			//ovde blokiraj pisanje
        		if(((glava + 1) % BUFF_SIZE) == rep)
        		{
        	    		printf("Fifo je pun\n");
        	    		printf("Broj %d nije uspjesno upisan\n", z);
        	    		break;
			}
        		else
        		{
        	    		fifo[glava++] = z;
        	    		printf("Uspjesno upisan broj %d u bafer\n", z);
 	
        	    		while(p[0] != ',' && p[0] != '\0')
        	        		++p;
			        if(*p == ',')
        	        		++p;
        	    		else
        	        		break;
        		}
			//ovde odblokiraj citanje
    		}
	}
 
    return 0;
}
