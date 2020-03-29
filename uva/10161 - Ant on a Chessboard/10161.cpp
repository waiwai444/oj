#include <stdio.h>
#include <math.h>

int main()
{
	int n, level, rem, x, y;
	while(scanf("%d", &n) && n)
	{
		level = (int)sqrt((double)n-1)+1;
		rem = n-(level-1)*(level-1);
		if(rem <= level)
		{
			x = rem;
			y = level;
		}
		else
		{
			x = level;
			y = level+level-rem;
		}
		if((level&1) == 0)
			printf("%d %d\n", x, y);
		else
			printf("%d %d\n", y, x);
	}
	return 0;
}
