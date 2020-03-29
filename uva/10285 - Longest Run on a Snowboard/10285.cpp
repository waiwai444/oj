#include <stdio.h>
#include <string.h>

int r, c, h[100][100], dp[100][100];

int dfs(int i, int j)
{
	int ret;
	if(dp[i][j] > 0)
		return dp[i][j];
	dp[i][j] = 1;
	if(i > 0 && h[i-1][j] < h[i][j])
		if((ret = dfs(i-1, j)+1) > dp[i][j])
			dp[i][j] = ret;
	if(i < r-1 && h[i+1][j] < h[i][j])
		if((ret = dfs(i+1, j)+1) > dp[i][j])
			dp[i][j] = ret;
	if(j > 0 && h[i][j-1] < h[i][j])
		if((ret = dfs(i, j-1)+1) > dp[i][j])
			dp[i][j] = ret;
	if(j < c-1 && h[i][j+1] < h[i][j])
		if((ret = dfs(i, j+1)+1) > dp[i][j])
			dp[i][j] = ret;
	return dp[i][j];
}

int main()
{
	int i, j, tc, max, ret;
	char name[100];
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%s%d%d", name, &r, &c);
		for(i = 0; i < r; i++)
			for(j = 0; j < c; j++)
			{
				scanf("%d", &h[i][j]);
				dp[i][j] = 0;
			}
		max = 0;
		for(i = 0; i < r; i++)
			for(j = 0; j < c; j++)
				if(dp[i][j] == 0)
				{
					ret = dfs(i, j);
					if(ret > max)
						max = ret;
				}
		printf("%s: %d\n", name, max);
	}
	return 0;
}