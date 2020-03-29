#include <stdio.h>
#include <math.h>

unsigned int n;

unsigned int solve()
{
	int i, c = 0, b;
	unsigned int n0 = n, sum = 0, m;
	bool flag = false;
	if(n == 1)
		return 2;
	if((n&1) == 0)
	{
		++c;
		flag = true;
		m = 1;
		while(n > 1 && (n&1) == 0)
		{
			n /= 2;
			m *= 2;
		}
		sum += m;
	}
	b = sqrt(n0+0.5);
	for(i = 3; (flag || i <= b) && n > 1; i += 2)
	{
		if(n%i == 0)
		{
			flag = true;
			++c;
			m = 1;
			while(n > 1 && n%i == 0)
			{
				n /= i;
				m *= i;
			}
			sum += m;
		}
	}
	if(c <= 1)
		sum = n0+1;
	return sum;
}

int main()
{
	int c = 0;
	while(scanf("%d", &n), n)
	{
		printf("Case %d: %u\n", ++c, solve());
	}
	return 0;
}
