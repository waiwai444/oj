#include <stdio.h>

inline int gcd(int x, int y)
{
	return y == 0 ? x : gcd(y, x%y);
}

int main()
{
	int i, j, k, n, cherry[100][2], c1, c2, c3, c4;
	bool cut_thru1, cut_thru2;
	while(scanf("%d", &n) && n)
	{
		n <<= 1;
		c1 = c2 = c3 = c4 = 0;
		cut_thru1 = cut_thru2 = false;
		for(i = 0; i < n; i++)
		{
			scanf("%d%d", &cherry[i][0], &cherry[i][1]);
			if(cherry[i][1] == 0)
				cut_thru1 = true;
			if(cherry[i][0] == 0)
				cut_thru2 = true;
			if(!cut_thru1)
			{
				if(cherry[i][1] > 0)
					c1++;
				else
					c2++;
			}
			if(!cut_thru2)
			{
				if(cherry[i][0] > 0)
					c3++;
				else
					c4++;
			}
		}
		if(!cut_thru1 && c1 == c2)
		{
			printf("0 1\n");
			continue;
		}
		else if(!cut_thru2 && c3 == c4)
		{
			printf("1 0\n");
			continue;
		}
		for(i = 1; i <= 500; i++)
		{
			for(j = 1; j <= 500; j++)
			{
				if(gcd(i, j) > 1)
					continue;
				c1 = c2 = c3 = c4 = 0;
				cut_thru1 = cut_thru2 = false;
				for(k = 0; k < n; k++)
				{
					int d = cherry[k][0]*i+cherry[k][1]*j;
					if(d == 0)
						cut_thru1 = true;
					else if(d > 0)
						c1++;
					else
						c2++;
					d = cherry[k][0]*i-cherry[k][1]*j;
					if(d == 0)
						cut_thru2 = true;
					else if(d > 0)
						c3++;
					else
						c4++;
				}
				if(!cut_thru1 && c1 == c2)
				{
					printf("%d %d\n", i, j);
					goto finished;
				}
				else if(!cut_thru2 && c3 == c4)
				{
					printf("%d %d\n", i, -j);
					goto finished;
				}
			}
		}
		finished:;
	}
	return 0;
}
