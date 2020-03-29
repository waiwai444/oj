#include <stdio.h>

int main()
{
	int i, j, n, c2, c5, f;
	while(scanf("%d", &n) != EOF)
	{
		c2 = c5 = 0;
		f = 1;
		for(i = 2; i <= n; i++)
		{
			j = i;
			while(j%5 == 0)
			{
				j /= 5;
				c5++;
			}
			while(j%2 == 0)
			{
				j /= 2;
				c2++;
			}
			f = f*j%10;
		}
		if(c2 > c5)
			for(i = c5; i < c2; i++)
				f = f*2%10;
		else if(c2 > c5)
			for(i = c2; i < c5; i++)
				f = f*5%10;
		printf("%5d -> %d\n", n, f);
	}
	return 0;
}
