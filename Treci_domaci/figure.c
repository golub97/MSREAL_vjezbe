#include "figure.h"

void crno(int z)
{
    FILE *nesto;
	int x, y;

	for(y = 0; y < (480/z); ++y)
		for(x = 0; x < 640; ++x)
		{
			nesto = fopen("/dev/vga_dma", "w");
			if(nesto == NULL)
				printf("Cannot open /dev/vga_dma for write\n");
			fprintf(nesto,"%d,%d,%#04x\n", x, y, 0x0000);
			fclose(nesto);
			if(nesto == NULL)
				printf("Cannot close /dev/vga_dma\n");
		}
}

void kadar(void)
{
	FILE *nesto;
	int x, y, i, j;

	for(y = 0; y < 2; ++y)
		for(x = 59; x < 580; ++x)
		{
			nesto = fopen("/dev/vga_dma", "w");
			fprintf(nesto,"%d,%d,%#04x\n", x, 119+y*80, 0xFFFF);
			fclose(nesto);
		}
	for(x = 0; x < 2; ++x)
		for(y = 119; y < 200; ++y)
		{
			nesto = fopen("/dev/vga_dma", "w");
			fprintf(nesto,"%d,%d,%#04x\n", 59+x*520, y, 0xFFFF);
			fclose(nesto);
		}
	for(i = 0; i < 5; ++i)
		for(j = 0; j < 2; ++j)
			for(y = 119; y < 200; ++y)
			{
				nesto = fopen("/dev/vga_dma", "w");
				fprintf(nesto,"%d,%d,%#04x\n", 139+8*j+88*i, y, 0xFFFF);
				fclose(nesto);
			}


}

void krug(int xx, int boja)
{
	int cx = xx + 40, cy = 119 + 40, x, y;
	float q;
	FILE *nesto;

	for(x = xx; x <= (xx+80); ++x)
		for(y = 119; y < 200; ++y)
		{
			q = sqrt((float)(pow(cx - x, 2) + pow(cy - y, 2)));
			if((39.6 < q) && (q < 40.4))
			{
				nesto = fopen("/dev/vga_dma", "w");
				fprintf(nesto,"%d,%d,%#04x\n", x, y, boja);
				fclose(nesto);
			}
		}
}
void trougao(int xx, int boja)
{
	int sredina = xx + 40, x, y = 119;
	FILE *nesto;
	for(x = sredina; xx < x; --x)
	{
		nesto = fopen("/dev/vga_dma", "w"); //lijeva kateta
		fprintf(nesto,"%d,%d,%#04x\n", x, y++, boja);
		fclose(nesto);

		nesto = fopen("/dev/vga_dma", "w");
		fprintf(nesto,"%d,%d,%#04x\n", x, y++, boja);
		fclose(nesto);
	}

	y = 119;

	for(x = sredina; x < (sredina + 40); ++x) //desna kateta
	{
			nesto = fopen("/dev/vga_dma", "w");
			fprintf(nesto,"%d,%d,%#04x\n", x, y++, boja);
			fclose(nesto);

			nesto = fopen("/dev/vga_dma", "w");
			fprintf(nesto,"%d,%d,%#04x\n", x, y++, boja);
			fclose(nesto);
	}

	for(x = xx; x <= (xx+80); ++x)
	{
		nesto = fopen("/dev/vga_dma", "w");
		fprintf(nesto,"%d,%d,%#04x\n", x, 199, boja);
		fclose(nesto);
	}

}
void iks(int xx, int boja)
{
	int x, y = 119;
	FILE *nesto;

	for(x = xx; x <= (xx+80); ++x)
	{
		nesto = fopen("/dev/vga_dma", "w");
		fprintf(nesto,"%d,%d,%#04x\n", x, y++, boja);
		fclose(nesto);
	}
	y = 119;
	for(x = xx+80; x >= xx; --x)
	{
		nesto = fopen("/dev/vga_dma", "w");
		fprintf(nesto,"%d,%d,%#04x\n", x, y++, boja);
		fclose(nesto);
	}
}
void kvadrat(int xx, int boja)
{
	int x, i, y = 119;
	FILE *nesto;

	for(i = 0; i < 2; ++i)
		for(x = xx; x <= (xx+80); ++x)
		{
			nesto = fopen("/dev/vga_dma", "w");
			fprintf(nesto,"%d,%d,%#04x\n", x, y+i*80, boja);
			fclose(nesto);
		}

	for(i = 0; i < 2; ++i)
		for(x = y; x <= (y + 80); ++x)
		{
			nesto = fopen("/dev/vga_dma", "w");
			fprintf(nesto,"%d,%d,%#04x\n", xx + 80*i, x, boja);
			fclose(nesto);
		}
}
