#include <stdio.h>

int main()
{
	int tc = 0, a, l, m, c, tmp;
	while(scanf("%d%d", &a, &l), a > 0)
	{
		tc++;
		m = a;
		c = 1;
		while(true)
		{
			if(m == 1)
				break;
			if((m&1) == 0)
			{
				m >>= 1;
				c++;
			}
			else
			{
				tmp = m+m;
				if(tmp < 0 || tmp > l)
					break;
				tmp += m;
				if(tmp < 0 || tmp > l)
					break;
				tmp++;
				if(tmp < 0 || tmp > l)
					break;
				m = tmp;
				c++;
			}
		}
		printf("Case %d: A = %d, limit = %d, number of terms = %d\n", tc, a, l, c);
	}
	return 0;
}
