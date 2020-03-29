#include <stdio.h>
#include <string.h>

int main()
{
	int i, j, n, k, m, c, r;
	bool dq[20];
	while(scanf("%d%d%d", &n, &k, &m), n)
	{
		memset(dq, false, sizeof(dq));
		i = n-1;
		j = 0;
		r = n;
		while(r > 0)
		{
			c = k;
			while(c > 0)
			{
				if(++i >= n)
					i = 0;
				if(!dq[i])
					c--;
			}
			c = m;
			while(c > 0)
			{
				if(--j < 0)
					j = n-1;
				if(!dq[j])
					c--;
			}

			
			if(i != j)
			{
				r -= 2;
				printf("%3d%3d%c", i+1, j+1, r == 0 ? '\n' : ',');
				dq[i] = dq[j] = true;
			}
			else
			{
				r--;
				printf("%3d%c", i+1, r == 0 ? '\n' : ',');
				dq[i] = true;
			}
		}
	}
	return 0;
}