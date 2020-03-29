#include <stdio.h>
#include <string.h>

char str[1001];
int dp[1000][1000];

int solve()
{
	int i, j, d, len = strlen(str);
	if(len == 0)
		return 0;
	for(i = 0; i < len; i++)
		dp[i][i] = 1;
	for(d = 1; d < len; d++)
	{
		for(i = 0; (j = i+d) < len; i++)
		{
			if(str[i] == str[j])
				dp[i][j] = dp[i+1][j-1]+2;
			else
			{
				dp[i][j] = dp[i+1][j];
				if(dp[i][j-1] > dp[i][j])
					dp[i][j] = dp[i][j-1];
			}
		}
	}
	return dp[0][len-1];
}

int main()
{
	int tc;
	scanf("%d", &tc);
	fgets(str, sizeof(str), stdin);
	while(tc--)
	{
		fgets(str, sizeof(str), stdin);
		str[strlen(str)-1] = 0;
		printf("%d\n", solve());
	}
	return 0;
}
