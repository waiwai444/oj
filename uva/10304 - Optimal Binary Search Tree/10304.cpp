#include <stdio.h>

int n, freq[250];
int dp[250][250];
int sum[250];
int root[250][250];

void get_sum()
{
	sum[0] = freq[0];
	for(int i = 1; i < n; i++)
		sum[i] = sum[i-1]+freq[i];
}

int solve()
{
	int i, j, k, t;
	get_sum();
	for(i = 0; i < n; i++)
	{
		dp[i][i] = 0;
		root[i][i] = i;
	}
	for(i = 1; i < n; i++)
	{
		for(j = 0; j+i < n; j++)
		{
			dp[j][j+i] = 0x3f3f3f3f;
			for(k = root[j][j+i-1]; k <= root[j+1][j+i]; k++)
			{
				t = 0;
				if(k > 0)
					t += dp[j][k-1]+sum[k-1]-sum[j]+freq[j];
				if(k < j+i)
					t += dp[k+1][j+i]+sum[j+i]-sum[k+1]+freq[k+1];
				if(t < dp[j][j+i])
				{
					dp[j][j+i] = t;
					root[j][j+i] = k;
				}
			}
		}
	}
	return dp[0][n-1];
}

int main()
{
	int i;
	while(scanf("%d", &n) != EOF)
	{
		for(i = 0; i < n; i++)
			scanf("%d", &freq[i]);
		printf("%d\n", solve());
	}
	return 0;
}