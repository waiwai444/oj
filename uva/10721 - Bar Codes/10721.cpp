#include <stdio.h>

long long ans[51][51][51];

void solve()
{
	int i, j, k, l;
	for(k = 0; k <= 50; k++)
		ans[0][0][k] = 1;
	for(i = 1; i <= 50; i++)
	{
		for(j = 1; j <= 50; j++)
		{
			for(k = 1; k <= i; k++)
			{
				for(l = 1; l <= k; l++)
				{
					ans[i][j][k] += ans[i-l][j-1][k];
				}
			}
			for(; k <= 50; k++)
				ans[i][j][k] = ans[i][j][k-1];
		}
	}
}

int main()
{
	int n, k, m;
	solve();
	while(scanf("%d%d%d", &n, &k, &m) != EOF)
	{
		printf("%lld\n", ans[n][k][m]);
	}
	return 0;
}

