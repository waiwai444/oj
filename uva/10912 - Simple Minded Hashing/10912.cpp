#include <stdio.h>

int dp[27][352][27];

void solve()
{
	int i, j, k, u;
	for(k = 0; k <= 26; k++)
		dp[0][0][k] = 1;
	for(i = 1; i <= 26; i++)
	{
		for(j = 1; j <= 351; j++)
		{
			u = j > 26 ? 26 : j;
			for(k = 1; k <= u; k++)
				dp[i][j][k] = dp[i][j][k-1]+dp[i-1][j-k][k-1];
			for(; k <= 26; k++)
				dp[i][j][k] = dp[i][j][k-1];
		}
	}
}

int main()
{
	int l, s;
	int tc = 0;
	solve();
	while(scanf("%d%d", &l, &s), l)
	{
		printf("Case %d: %d\n", ++tc, l <= 26 && s <= 351 ? dp[l][s][26] : 0);
	}
	return 0;
}

