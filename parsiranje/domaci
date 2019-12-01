#include <stdio.h>

#define MAX_INPUT_STRING 50
#define MAX_SIZE 16

int main()
{
    char p[MAX_INPUT_STRING];
    unsigned char buffer[MAX_SIZE] = {0};
    unsigned char i = 0, j, k, z = 0;
    
    scanf("%s", p);

    while(p[i] != '\0')
    {
        j = i;
        k = 0;
        while(p[j] != ',' && p[j] != '\0')
            ++j, ++k;
        
        if(p[j-1] >= 'A' && p[j-1] <= 'F')
            buffer[z] |= (p[j-1] - 55);
        else if(p[j-1] >= 'a' && p[j-1] <= 'f')
            buffer[z] |= (p[j-1] - 87);
        else
            buffer[z] |= (p[j-1] - 48);
            
        if(k > 1)
        {
            if(p[j-2] >= 'A' && p[j-2] <= 'F')
                buffer[z] |= (p[j-2] - 55) << 4;
            else if(p[j-2] >= 'a' && p[j-2] <= 'f')
                buffer[z] |= (p[j-2] - 87) << 4;
            else
                buffer[z] |= (p[j-2] - 48) << 4;    
        }
            
        ++z;
        i = j + 1;
    }
    
    printf("%d\n", z);
    
    for(k = 0; k < z; ++k)
        printf("%x ", buffer[k]);
    
    return 0;
}
