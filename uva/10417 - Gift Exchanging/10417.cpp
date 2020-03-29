#include <stdio.h>

int n;
int gift[5];
double pr[12][5];
double pn[5], pd;
int ans_ch;
double ans_pr;

void dfs(int g, double p)
{
	double q;
	for(int i = 0; i < 5; i++)
	{
		if(gift[i] > 0 && pr[g][i] > 0)
		{
			q = p*pr[g][i];
			if(g == 0)
			{
				pn[i] += q;
				pd += q;
				return;
			}
			gift[i]--;
			dfs(g-1, q);
			gift[i]++;
		}
	}
}

void solve()
{
	int i;
	pd = 0;
	for(i = 0; i < 5; i++)
		pn[i] = 0;
	dfs(n-1, 1);
	ans_pr = 0;
	for(i = 0; i < 5; i++)
	{
		double t = pn[i]/pd/gift[i];
		if(t > ans_pr)
		{
			ans_ch = i+1;
			ans_pr = t;
		}
	}
}

int main()
{
	int i, j, k, tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d", &n);
		for(i = 0, j = 0; i < 5; i++)
			scanf("%d", &gift[i]);
		for(i = 0; i < n; i++)
			for(j = 0; j < 5; j++)
				scanf("%lf", &pr[i][j]);
		solve();
		printf("%d %.3f\n", ans_ch, ans_pr);
	}
	return 0;
}

