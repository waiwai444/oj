#include <stdio.h>

int n, r;
double buy[21];
double dp[21][21];
double ans[21];

void solve()
{
	int i, j, b;
	double pr;
	dp[0][0] = 1;
	for(i = 1; i <= n; i++)
	{
		dp[i][0] = dp[i-1][0]*(1-buy[i]);
		for(j = 1; j <= i && j <= r; j++)
			dp[i][j] = dp[i-1][j-1]*buy[i]+dp[i-1][j]*(1-buy[i]);
	}
	pr = dp[n][r];
	for(b = 1; b <= n; b++)
	{
		for(i = 1; i < b; i++)
		{
			dp[i][0] = dp[i-1][0]*(1-buy[i]);
			for(j = 1; j <= i && j <= r-1; j++)
				dp[i][j] = dp[i-1][j-1]*buy[i]+dp[i-1][j]*(1-buy[i]);
		}
		dp[b][0] = 0;
		for(j = 1; j <= i && j <= r; j++)
			dp[b][j] = dp[b-1][j-1]*buy[i];
		for(i = b+1; i <= n; i++)
		{
			dp[i][0] = 0;
			for(j = 1; j <= i && j <= r; j++)
				dp[i][j] = dp[i-1][j-1]*buy[i]+dp[i-1][j]*(1-buy[i]);
		}
		ans[b] = dp[n][r]/pr;
	}
}

int main()
{
	int i, tc = 0;
	while(scanf("%d%d", &n, &r), n)
	{
		for(i = 1; i <= n; i++)
			scanf("%lf", &buy[i]);
		solve();
		printf("Case %d:\n", ++tc);
		for(i = 1; i <= n; i++)
			printf("%.6f\n", ans[i]);
	}
	return 0;
}

