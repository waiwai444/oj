#include <stdio.h>

long long dp[301][301];	// dp[i][j] means using at most i coins to make value j.

void solve()
{
	int i, j, k;
	dp[0][0] = 1;
	for(i = 1; i <= 300; i++)
	{
		dp[i][0] = 1;
		for(j = 1; j <= i; j++)
			dp[i][j] = dp[i-1][j-1];
	}
	for(k = 2; k <= 300; k++)
	{
		for(i = 1; i <= 300; i++)
		{
			for(j = k; j <= 300; j++)
			{
				dp[i][j] += dp[i-1][j-k];
			}
		}
	}
}

int main()
{
	int n, l1, l2;
	char input[50];
	solve();
	while(fgets(input, 50, stdin))
	{
		switch(sscanf(input, "%d%d%d", &n, &l1, &l2))
		{
			case 1:
				printf("%lld\n", dp[300][n]);
				break;
			case 2:
				printf("%lld\n", dp[l1 > 300 ? 300 : l1][n]);
				break;
			case 3:
				if(l2 > 300)
					l2 = 300;
				if(l1 == 0)
					printf("%lld\n", dp[l2][n]);
				else
					printf("%lld\n", dp[l2][n]-dp[l1-1][n]);
				break;
		}
	}
	return 0;
}
