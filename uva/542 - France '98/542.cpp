#include <stdio.h>

char team[16][11];
int prob[16][16];
double ans[16][5];

void solve()
{
	int i, j, k, n = 1, g, b, e;
	for(i = 0; i < 16; i++)
		ans[i][0] = 1;
	for(i = 1; i <= 4; i++)
	{
		for(j = 0; j < 16; j++)
		{
			g = j/n;
			if((g&1) == 0)
			{
				b = n*(g+1);
				e = n*(g+2)-1;
			}
			else
			{
				b = n*g-n;
				e = n*g-1;
			}
			ans[j][i] = 0;
			for(k = b; k <= e; k++)
			{
				ans[j][i] += ans[k][i-1]*prob[j][k]/100;
			}
			ans[j][i] *= ans[j][i-1];
		}
		n *= 2;
	}
}

int main()
{
	int i, j;
	for(i = 0; i < 16; i++)
		scanf("%s", team[i]);
	for(i = 0; i < 16; i++)
		for(j = 0; j < 16; j++)
			scanf("%d", &prob[i][j]);
	solve();
	for(i = 0; i < 16; i++)
		printf("%-10s p=%.2f%%\n", team[i], ans[i][4]*100);
	return 0;
}

