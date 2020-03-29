#include <cstdio>

using namespace std;

int p, q;

long long solve()
{
	long long sum = 0;
	if(p == 0)
		++p;
	while(p <= q)
	{
		int a = p%10;
		int b = q%10;
		p /= 10;
		q /= 10;
		sum += (long long)(q-p)*45;
		if(a > b)
		{
			for(int i = b+1; i < a; i++)
				sum -= i;
		}
		else
		{
			for(int i = a; i <= b; i++)
				sum += i;
		}
		if(a)
			++p;
	}
	return sum;
}

int main()
{
	while(scanf("%d%d", &p, &q), p >= 0)
	{
		printf("%lld\n", solve());
	}
	return 0;
}

