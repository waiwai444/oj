#include <stdio.h>

int n, t, p;
int ans[71][71][71];

void solve()
{
	int i, j, k, l, u;
	for(i = 1; i <= 70; i++)
	{
		for(k = i; k <= 70; k++)
		{
			ans[i][1][k] = 1;
		}
		for(j = 2; j <= 70; j++)
		{
			for(k = i*j; k <= 70; k++)
			{
				u = k-i*(j-1);
				for(l = i; l <= u; l++)
				{
					ans[i][j][k] += ans[i][j-1][k-l];
				}
			}
		}
	}
}

int main()
{
	int tc;
	solve();
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d%d", &n, &t, &p);
		printf("%d\n", ans[p][n][t]);
	}
	return 0;
}

