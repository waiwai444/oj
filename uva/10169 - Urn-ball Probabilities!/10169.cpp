#include <stdio.h>

#define MAX 1000000

double prob[MAX];
int czeros[MAX];

void solve()
{
	int i, k = -1, t = 0;
	long long d, m = 1;
	double p = 1, q = 1;
	for(i = 1; i < MAX; i++)
	{
		d = (long long)i*(i+1);
		p *= (1-1.0/d);
		prob[i] = 1-p;

		if(d/m/10)
		{
			m *= 10;
			++t;
		}
		q /= d;
		q *= m;
		k += t;
		if(q < 1)
		{
			q *= 10;
			++k;
		}
		czeros[i] = k;
	}
}

int main()
{
	int n;
	solve();
	while(scanf("%d", &n) != EOF)
	{
		printf("%.6f %d\n", prob[n], czeros[n]);
	}
	return 0;
}

