#include "figure.h"

#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
	int i, j;
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
	return 0;
}
