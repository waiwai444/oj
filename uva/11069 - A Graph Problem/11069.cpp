#include <stdio.h>

int n;
int dp[77];

void solve()
{
	int i;
	dp[0] = 0;
	dp[1] = dp[2] = 1;
	for(i = 3; i <= 76; i++)
	{
		dp[i] = dp[i-2]+dp[i-3];
	}
}

int main()
{
	solve();
	while(scanf("%d", &n) != EOF)
	{
		printf("%d\n", dp[n]+dp[n-1]);
	}
	return 0;
}

