#include <stdio.h>
#include <string.h>

int n, m, num[10];
bool dp[1000001];

bool solve()
{
	int i, j, t;
	memset(dp, false, (n+1)*sizeof(bool));
	for(i = 0; i < m; i++)
		dp[num[i]] = true;
	for(i = 2; i <= n; i++)
	{
		if(dp[i])
			continue;
		for(j = 0; j < m; j++)
		{
			t = i-num[j];
			if(t > 0 && !dp[t])
			{
				dp[i] = true;
				break;
			}
		}
	}
	return dp[n];
}

int main()
{
	int i;
	while(scanf("%d%d", &n, &m) != EOF)
	{
		for(i = 0; i < m; i++)
			scanf("%d", &num[i]);
		if(solve())
			printf("Stan wins\n");
		else
			printf("Ollie wins\n");
	}
	return 0;
}