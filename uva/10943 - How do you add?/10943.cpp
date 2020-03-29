#include <stdio.h>

#define MOD 1000000

int ans[101][101];

void solve()
{
	int i, j, k;
	for(j = 1; j <= 100; j++)
		ans[0][j] = 1;
	for(i = 1; i <= 100; i++)
	{
		ans[i][1] = 1;
		for(j = 2; j <= 100; j++)
		{
			for(k = 0; k <= i; k++)
			{
				ans[i][j] = (ans[i][j]+ans[i-k][j-1])%MOD;
			}
		}
	}
}

int main()
{
	int n, k;
	solve();
	while(scanf("%d%d", &n, &k), n)
	{
		printf("%d\n", ans[n][k]);
	}
	return 0;
}

