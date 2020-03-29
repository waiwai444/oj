#include <stdio.h>
#include <string.h>

#define MAXS 351

int n, s;
int hg[39][20];
long long dp[39][20][MAXS+1];

long long solve()
{
	int i, j, k;
	long long tmp;
	memset(dp, 0, sizeof(dp));
	for(j = 0; j < n; j++)
		dp[2*n-2][j][hg[2*n-2][j]] = 1;
	for(i = 2*n-3; i >= n-1; i--)
	{
		for(j = 0; j < i-n+2; j++)
		{
			for(k = hg[i][j]; k <= s; k++)
			{
				tmp = dp[i+1][j][k-hg[i][j]]+dp[i+1][j+1][k-hg[i][j]];
				if(tmp > 0)
					dp[i][j][k] = tmp;
			}
		}
	}
	for(; i >= 0; i--)
	{
		for(j = 0; j < n-i; j++)
		{
			for(k = hg[i][j]; k <= s; k++)
			{
				tmp = (j>0?dp[i+1][j-1][k-hg[i][j]]:0)+(j<n-i-1?dp[i+1][j][k-hg[i][j]]:0);
				if(tmp > 0)
					dp[i][j][k] = tmp;
			}
		}
	}
	tmp = 0;
	for(j = 0; j < n; j++)
		tmp += dp[0][j][s];
	return tmp;
}

void output_path()
{
	int i, j, sum = s;
	char path[39];
	for(j = 0; j < n; j++)
		if(dp[0][j][s] > 0)
		{
			printf("%d ", j);
			break;
		}
	for(i = 0; i < n-1; i++)
	{
		sum -= hg[i][j];
		if(j > 0 && dp[i+1][j-1][sum] > 0)
		{
			path[i] = 'L';
			j--;
		}
		else
			path[i] = 'R';
	}
	for(; i < 2*n-2; i++)
	{
		sum -= hg[i][j];
		if(dp[i+1][j][sum] > 0)
			path[i] = 'L';
		else
		{
			path[i] = 'R';
			j++;
		}
	}
	path[i] = '\0';
	printf("%s\n", path);
}

int main()
{
	int i, j;
	while(scanf("%d%d", &n, &s), n)
	{
		for(i = 0; i < n; i++)
			for(j = 0; j < n-i; j++)
				scanf("%d", &hg[i][j]);
		for(; i < 2*n-1; i++)
			for(j = 0; j < i-n+2; j++)
				scanf("%d", &hg[i][j]);
		if(s > MAXS)
			printf("0\n\n");
		else
		{
			long long np = solve();
			printf("%lld\n", np);
			if(np)
				output_path();
			else
				printf("\n");
		}
	}
	return 0;
}
