#include <stdio.h>

int main()
{
	int ncows, ncars, nshow, n;
	while(scanf("%d%d%d", &ncows, &ncars, &nshow) != EOF)
	{
		n = ncows+ncars;
		printf("%.5f\n", (double)ncars*(n-1)/n/(n-1-nshow));
	}
	return 0;
}

