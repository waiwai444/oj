#include <stdio.h>

int n, num[100];
int sum[100];
int dp[100][100];

void get_sum()
{
	sum[0] = num[0];
	for(int i = 1; i < n; i++)
		sum[i] = sum[i-1]+num[i];
}

int solve()
{
	int i, j, k, d, tmp;
	get_sum();
	for(i = 0; i < n; i++)
		dp[i][i] = num[i];
	for(d = 1; d < n; d++)
	{
		for(i = 0; (j = i+d) < n; i++)
		{
			dp[i][j] = sum[j]-(i>0?sum[i-1]:0);
			for(k = i; k < j; k++)
			{
				tmp = sum[k]-(i>0?sum[i-1]:0)-dp[k+1][j];
				if(tmp > dp[i][j])
					dp[i][j] = tmp;
				tmp = sum[j]-sum[j-k+i-1]-dp[i][j-k+i-1];
				if(tmp > dp[i][j])
					dp[i][j] = tmp;
			}
		}
	}
	return dp[0][n-1];
}

int main()
{
	int i;
	while(scanf("%d", &n), n)
	{
		for(i = 0; i < n; i++)
			scanf("%d", &num[i]);
		printf("%d\n", solve());
	}
	return 0;
}
