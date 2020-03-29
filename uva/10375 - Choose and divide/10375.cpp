#include <stdio.h>

int p, q, r, s;

double solve()
{
	int i = 0, j = 0, k = 0, l = 0;
	long double res = 1;
	while(i < q || j < q || k < s || l < s)
	{
		if(i < q && (l >= s || p-i >= s-l))
		{
			res *= p-i;
			++i;
		}
		else
		{
			res *= s-l;
			++l;
		}
		if(j < q && (k >= s || q-j >= r-k))
		{
			res /= q-j;
			++j;
		}
		else
		{
			res /= r-k;
			++k;
		}
	}
	return (double)res;
}

int main()
{
	while(scanf("%d%d%d%d", &p, &q, &r, &s) != EOF)
	{
		printf("%.5f\n", solve());
	}
	return 0;
}

