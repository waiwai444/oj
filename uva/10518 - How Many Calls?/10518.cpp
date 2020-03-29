#include <stdio.h>

long long n;
int b;
int v[30000];

int solve()
{
	int i, p;
	if(b == 1)
		return 0;
	v[0] = v[1] = 1;
	for(i = 2;; i++)
	{
		v[i] = (v[i-1]+v[i-2]+1)%b;
		if(v[i-1] == v[i] && v[i] == 1)
			break;
	}
	p = i-1;
	return v[n%p];
}

int main()
{
	int c = 0;
	while(scanf("%lld%d", &n, &b), b)
	{
		printf("Case %d: %lld %d %d\n", ++c, n, b, solve());
	}
	return 0;
}

