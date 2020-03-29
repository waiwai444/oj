#include <stdio.h>
#include <string.h>

int dp[4096];

int solve(int cur)
{
	if(dp[cur] >= 0)
		return dp[cur];
	int i, m = 0, t;
	for(i = 0; i < 12; i++)
		if(cur&(1<<i))
			m++;
	for(i = 0; i < 12; i++)
	{
		if(!(cur&(1<<i)))
		{
			if(i >= 2 && (cur&(1<<(i-1))) && (cur&(1<<(i-2))))
			{
				t = solve(cur+(1<<i)-(1<<(i-2))-(1<<(i-1)));
				if(t < m)
					m = t;
			}
			if(i <= 9 && (cur&(1<<(i+1))) && (cur&(1<<(i+2))))
			{
				t = solve(cur+(1<<i)-(1<<(i+2))-(1<<(i+1)));
				if(t < m)
					m = t;
			}
		}
	}
	return dp[cur] = m;
}

int to_int(char board[])
{
	int ret = 0;
	for(int i = 0; i < 12; i++)
		if(board[i] == 'o')
			ret |= 1<<i;
	return ret;
}

int main()
{
	int	n;
	char input[13];
	memset(dp, -1, sizeof(dp));
	dp[0] = 0;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%s", input);
		printf("%d\n", solve(to_int(input)));
	}
	return 0;
}