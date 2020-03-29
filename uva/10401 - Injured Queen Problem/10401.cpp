#include <stdio.h>
#include <string.h>

char input[16];
int n;
long long dp[15][15];

int to_index(char ch)
{
	if(ch >= '1' && ch <= '9')
		return ch-'1';
	return 9+ch-'A';
}

void solve()
{
	int i, j, k;
	memset(dp, 0, sizeof(dp));
	if(input[0] != '?')
		dp[0][to_index(input[0])] = 1;
	else
		for(i = 0; i < n; i++)
			dp[0][i] = 1;
	for(i = 1; i < n; i++)
	{
		if(input[i] != '?')
		{
			k = to_index(input[i]);
			for(j = 0; j < n; j++)
				if(j < k-1 || j > k+1)
					dp[i][k] += dp[i-1][j];
		}
		else
		{
			for(k = 0; k < n; k++)
			{
				for(j = 0; j < n; j++)
				{
					if(j < k-1 || j > k+1)
						dp[i][k] += dp[i-1][j];
				}
			}
		}
	}
}

void output()
{
	long long sum = 0;
	for(int i = 0; i < n; i++)
		sum += dp[n-1][i];
	printf("%lld\n", sum);
}

int main()
{
	while(scanf("%s", input) != EOF)
	{
		n = strlen(input);
		solve();
		output();
	}
	return 0;
}
