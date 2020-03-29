#include <stdio.h>
#include <string.h>

char str[1001];
int dp[1000][1000];

int solve()
{
	int len = strlen(str);
	int i, j, t, min;
	dp[0][0] = 0;
	for(i = 1; i < len; i++)
	{
		dp[i][i] = 0;
		dp[i-1][i] = str[i-1]==str[i]?0:1;
	}
	for(i = 2; i < len; i++)
	{
		for(j = 0; j+i < len; j++)
		{
			min = dp[j+1][j+i-1]+(str[j]==str[j+i]?0:1);
			if((t = dp[j+1][j+i]+1) < min)
				min = t;
			if((t = dp[j][j+i-1]+1) < min)
				min = t;
			dp[j][j+i] = min;
		}
	}
	return dp[0][len-1];
}

int main()
{
	int c, tc;
	scanf("%d", &tc);
	for(c = 1; c <= tc; c++)
	{
		scanf("%s", str);
		printf("Case %d: %d\n", c, solve());
	}
	return 0;
}