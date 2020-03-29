#include <stdio.h>

int dp[7490][5];
const int v[5] = {1, 5, 10, 25, 50};

void solve()
{
	int i, j, k;
	for(i = 1; i < 7490; i++)
	{
		for(j = 0; j < 5; j++)
		{
			dp[i][j] = 0;
			if(i-v[j] > 0)
				for(k = 0; k <= j; k++)
					dp[i][j] += dp[i-v[j]][k];
			else if(i-v[j] == 0)
				dp[i][j] = 1;
			else
				dp[i][j] = 0;
		}
	}
}

int main()
{
	int num, sum, i;
	solve();
	while(scanf("%d", &num) != EOF)
	{
		if(num == 0)
			printf("1\n");
		else
		{
			sum = 0;
			for(i = 0; i < 5; i++)
				sum += dp[num][i];
			printf("%d\n", sum);
		}
	}
	return 0;
}