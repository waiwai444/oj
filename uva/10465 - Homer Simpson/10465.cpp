#include <stdio.h>

int m, n, t;

int main()
{
	int x, y, r, b, tmp;
	while(scanf("%d%d%d", &m, &n, &t) != EOF)
	{
		if(m == n)
		{
			r = t%m;
			if(r)
				printf("%d %d\n", t/m, r);
			else
				printf("%d\n", t/m);
		}
		else
		{
			r = t;
			b = 0;
			x = t/m;
			y = 0;
			tmp = x*m;
			do
			{
				while(tmp+n <= t)
				{
					y++;
					tmp += n;
				}
				if(t-tmp < r)
				{
					r = t-tmp;
					b = x+y;
				}
				else if(t-tmp == r && x+y > b)
					b = x+y;
				x--;
				tmp -= m;
			} while(x >= 0);
			if(r)
				printf("%d %d\n", b, r);
			else
				printf("%d\n", b);
		}
	}
	return 0;
}