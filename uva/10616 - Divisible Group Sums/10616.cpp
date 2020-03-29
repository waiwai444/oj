#include <stdio.h>

int n, m, d;
int num[201];
long long dp[201][11][20];

long long solve()
{
	int i, j, k;
	dp[0][0][0] = 1;
	for(i = 1; i <= n; i++)
	{
		dp[i][0][0] = 1;
		for(j = 1; j <= m; j++)
		{
			for(k = 0; k < d; k++)
			{
				dp[i][j][k] = dp[i-1][j][k]+dp[i-1][j-1][(k-num[i]%d+d)%d];
			}
		}
	}
	return dp[n][m][0];
}

int main()
{
	int s = 0, i, q;
	long long ans;
	while(scanf("%d%d", &n, &q), n)
	{
		printf("SET %d:\n", ++s);
		for(i = 1; i <= n; i++)
			scanf("%d", &num[i]);
		for(i = 1; i <= q; i++)
		{
			scanf("%d%d", &d, &m);
			ans = m <= n ? solve() : 0;
			printf("QUERY %d: %lld\n", i, ans);
		}
	}
	return 0;
}

