#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

void crno(void);
void kadar(void);

void krug(int);
void trougao(int);
void iks(int);
void kvadrat(int);

int main(void)
{
        int x,y;
        FILE* fp;

        crno();

        //kadar();

        for(x = 1; x < 6; x+=3)
                krug(59 + x*88);
        for(x = 2; x < 6; x+=3)
                trougao(59 + x*88);
        for(x = 0; x < 6; x+=3)
                iks(59 + x*88);


        /*for(y=0; y<480; y++)
        {
                for(x=0; x<640; x++)
                {
                        fp = fopen("/dev/vga_dma", "w");
                        if(fp == NULL)
                        {
                                printf("Cannot open /dev/vga for write\n");
                                return -1;
                        }
                        //fprintf(fp,"%d,%d,%#04x\n",x,y,image[y*640+x]);
                        fprintf(fp,"%d,%d,%#04x\n",x,y,0x0000);
                        fclose(fp);
                        if(fp == NULL)
                        {
                                printf("Cannot close /dev/vga\n");
                                return -1;
                        }
                }
        }*/
        return 0;
}

void crno(void)
{
        FILE *nesto;
        int x, y;

        for(y = 0; y < 480; ++y)
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

void crno(void)
{
        FILE *nesto;
        int x, y;

        for(y = 0; y < 480; ++y)
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


