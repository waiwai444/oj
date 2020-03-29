#include <stdio.h>
#include <limits.h>

int N, k;
int grid[75][75];
int dp[75][75][6];
int la[75][6];	// temp, from left and above
int ra[75][6];	// temp, from right and above

void init()
{
	int i, j, m;
	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++)
			for(m = 0; m <= k; m++)
				dp[i][j][m] = INT_MIN;
}

void solve()
{
	int i, j, m, d, sum;
	init();
	j = grid[0][0] >= 0 ? 0 : 1;
	dp[0][0][j] = grid[0][0];
	for(i = 1; i < N; i++)
	{
		sum = dp[0][i-1][j]+grid[0][i];
		if(grid[0][i] < 0 && ++j > k)
			break;
		dp[0][i][j] = sum;
	}
	for(i = 1; i < N; i++)
	{
		for(j = 0; j < N; j++)
			for(m = 0; m <= k; m++)
				la[j][m] = ra[j][m] = INT_MIN;
		for(j = 0; j < N; j++)
		{
			d = grid[i][j] >= 0 ? 0 : 1;
			if(d > 0)
				la[j][0] = ra[j][0] = INT_MIN;
			for(m = d; m <= k; m++)
				if(dp[i-1][j][m-d] != INT_MIN)
					dp[i][j][m] = la[j][m] = ra[j][m] = dp[i-1][j][m-d]+grid[i][j];
		}
		for(j = 1; j < N; j++)
		{
			d = grid[i][j] >= 0 ? 0 : 1;
			for(m = d; m <= k; m++)
			{
				if(la[j-1][m-d] != INT_MIN)
				{
					sum = la[j-1][m-d]+grid[i][j];
					if(sum > dp[i][j][m])
						dp[i][j][m] = sum;
					if(sum > la[j][m])
						la[j][m] = sum;
				}
			}
		}
		for(j = N-2; j >= 0; j--)
		{
			d = grid[i][j] >= 0 ? 0 : 1;
			for(m = d; m <= k; m++)
			{
				if(ra[j+1][m-d] != INT_MIN)
				{
					sum = ra[j+1][m-d]+grid[i][j];
					if(sum > dp[i][j][m])
						dp[i][j][m] = sum;
					if(sum > ra[j][m])
						ra[j][m] = sum;
				}
			}
		}
	}
}

int main()
{
	int i, j, tc = 0, res;
	while(scanf("%d%d", &N, &k), N)
	{
		for(i = 0; i < N; i++)
			for(j = 0; j < N; j++)
				scanf("%d", &grid[i][j]);
		solve();
		printf("Case %d: ", ++tc);
		res = INT_MIN;
		for(i = 0; i <= k; i++)
			if(dp[N-1][N-1][i] > res)
				res = dp[N-1][N-1][i];
		
		if(res != INT_MIN)
			printf("%d\n", res);
		else
			printf("impossible\n");
	}
	return 0;
}
