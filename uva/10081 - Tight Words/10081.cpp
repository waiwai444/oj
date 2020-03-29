#include <stdio.h>

double dp[10][101][11];
double tot[10][101];
double ans[10][101];

void solve()
{
	int i, j, k;
	for(i = 0; i < 10; i++)
	{
		tot[i][0] = 1;
		for(j = 1; j <= 100; j++)
			tot[i][j] = tot[i][j-1]*(i+1);
	}
	for(i = 0; i < 10; i++)
	{
		for(k = 0; k <= i; k++)
			dp[i][1][k] = 1;
		ans[i][1] = (i+1)*100/tot[i][1];
		for(j = 2; j <= 100; j++)
		{
			dp[i][j][0] = dp[i][j-1][0]+dp[i][j-1][1];
			ans[i][j] = dp[i][j][0];
			for(k = 1; k <= i; k++)
			{
				dp[i][j][k] = dp[i][j-1][k-1]+dp[i][j-1][k]+dp[i][j-1][k+1];
				ans[i][j] += dp[i][j][k];
			}
			ans[i][j] = ans[i][j]*100/tot[i][j];
		}
	}
}

int main()
{
	int k, n;
	solve();
	while(scanf("%d%d", &k, &n) != EOF)
	{
		printf("%.5f\n", ans[k][n]);
	}
	return 0;
}

