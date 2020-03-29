#include <stdio.h>
#include <string.h>

char str[61];
long long dp[60][60];

long long solve()
{
	int i, j, d, n = strlen(str);
	dp[0][0] = 1;
	for(i = 1; i < n; i++)
	{
		dp[i][i] = 1;
		dp[i-1][i] = str[i-1]==str[i]?3:2;
	}
	for(d = 2; d < n; d++)
	{
		for(i = 0; (j = i+d) < n; i++)
		{
			if(str[i] != str[j])
				dp[i][j] = dp[i][j-1]+dp[i+1][j]-dp[i+1][j-1];
			else
				dp[i][j] = dp[i][j-1]+dp[i+1][j]+1;
		}
	}
	return dp[0][n-1];
}

int main()
{
	int tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%s", str);
		printf("%lld\n", solve());
	}
	return 0;
}
