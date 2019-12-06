#include <stdio.h>

#define MAX 3

void meni(int *);
void upis(void);
void citanje(void);

unsigned char fifo[MAX];
int glava = 0;
int rep = 0;

int main()
{
    int n;
    
    while(1)
    {
        meni(&n);
        
        if(n == 1)
        {
            upis();
        }
        else if(n == 2)
        {
            citanje();
        }
        else if(n == 4)
            break;
    }
    return 0;
}

void meni(int *n)
{
    printf("1.Upis\n");    
    printf("2.Citanje\n");  
    printf("3.Ispis\n");  
    printf("4.Kraj\n");  
    
    scanf("%d", n);
}
void upis(void)
{
    int temp;
    printf("Upisi broj u bafer: ");
    scanf("%d", &temp);
        
    if(((glava + 1) % MAX) == rep)
    {
        printf("Bafer je pun.\n");
    }
    else
    {
        fifo[glava] = temp;
        glava = (glava + 1) % MAX;
        printf("Uspjesno upisan broj u bafer.\n");
        printf("------------------------------\n");
    }    
    
}
void citanje(void)
{
    if(glava == rep)
        printf("Bafer je prazan.\n");
    else
    {
        printf("Citanje: %d\n", fifo[rep]);
        rep = (rep + 1) % MAX;
    }

}
