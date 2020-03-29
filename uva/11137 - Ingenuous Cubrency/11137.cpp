#include <stdio.h>

#define NCUBE 21
const int cube[NCUBE] = {1, 8, 27, 64, 125, 216, 343, 512, 729, 1000, 1331, 1728, 2197, 2744, 3375, 4096, 4913, 5832, 6859, 8000, 9261};
long long dp[10000][NCUBE];

long long solve(int n, int ci)
{
	if(dp[n][ci] > 0)
		return dp[n][ci];
	for(int i = ci; i >= 0; i--)
	{
		if(n-cube[i] >= 0)
			dp[n][ci] += solve(n-cube[i], i);
	}
	return dp[n][ci];
}

int main()
{
	int n;
	for(int i = 0; i < NCUBE; i++)
		dp[0][i] = dp[1][i] = 1;
	while(scanf("%d", &n) != EOF)
	{
		printf("%lld\n", solve(n, NCUBE-1));
	}
	return 0;
}
