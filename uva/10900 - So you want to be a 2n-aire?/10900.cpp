#include <stdio.h>

int n;
int p2[31];
double t;
double ans;

void init()
{
	p2[0] = 1;
	for(int i = 1; i <= 30; i++)
		p2[i] = p2[i-1]*2;
}

void solve()
{
	int i;
	double c;
	ans = p2[n];
	for(i = 1; i <= n; i++)
	{
		c = p2[n-i]/ans;
		if(c > 1)
			c = 1;
		else if(c < t)
			c = t;
		ans = ((c-t)*p2[n-i]+(1-c)*(c+1)*ans/2)/(1-t);
	}
}

int main()
{
	init();
	while(scanf("%d%lf", &n, &t), n)
	{
		solve();
		printf("%.3f\n", ans);
	}
	return 0;
}

