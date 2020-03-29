#include <stdio.h>

int n;
int a[101], r;
double b, v, e, f;

double dp[101];
double time[10001];
int max_d;

double solve()
{
	int i, j, x;
	double tmp;
	for(x = 1; x <= max_d; x++)
	{
		if(x > r)
			time[x] = time[x-1]+1/(v-e*(x-1-r));
		else
			time[x] = time[x-1]+1/(v-f*(r-x+1));
	}
	for(i = 1; i <= n; i++)
	{
		dp[i] = time[a[i]];
		for(j = 1; j < i; j++)
		{
			tmp = dp[j]+b+time[a[i]-a[j]];
			if(tmp < dp[i])
				dp[i] = tmp;
		}
	}
	return dp[n];
}

int main()
{
	int i;
	while(scanf("%d", &n), n)
	{
		max_d = 0;
		for(i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
			if(a[i] > max_d)
				max_d = a[i];
		}
		scanf("%lf%d%lf%lf%lf", &b, &r, &v, &e, &f);
		printf("%.4f\n", solve());
	}
	return 0;
}
