#include <stdio.h>
#include <math.h>

int main()
{
	int n, k, r, denom, num;
	while(scanf("%d", &n) != EOF)
	{
		k = (int)ceil((sqrt(8*(double)n+1)-1)/2);
		r = n-k*(k-1)/2;
		if(k%2 == 0)
		{
			num = r;
			denom = k-r+1;
		}
		else
		{
			num = k-r+1;
			denom = r;
		}
		printf("TERM %d IS %d/%d\n", n, num, denom);
	}
	return 0;
}
