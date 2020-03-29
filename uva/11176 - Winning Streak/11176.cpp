#include <stdio.h>

int n;
double p;
double pw[501];
double dp[501][501];
double ans;

void solve()
{
	int i, j;
	ans = 0;
	pw[0] = 1;
	for(i = 1; i <= n; i++)
		pw[i] = pw[i-1]*p;
	for(j = 0; j <= n; j++)
		dp[0][j] = 1;
	for(i = 1; i <= n; i++)
	{
		dp[i][0] = dp[i-1][0]*(1-p);
		for(j = 1; j < i; j++)
		{
			if(i-1 == j)
				dp[i][j] = dp[i-1][j]-pw[j+1];
			else
				dp[i][j] = dp[i-1][j]-dp[i-2-j][j]*(1-p)*pw[j+1];
		}
		for(j = i; j <= n; j++)
			dp[i][j] = 1;
	}
	for(j = 1; j <= n; j++)
		ans += j*(dp[n][j]-dp[n][j-1]);
}

int main()
{
	while(scanf("%d%lf", &n, &p), n)
	{
		solve();
		printf("%.6f\n", ans);
	}
	return 0;
}

