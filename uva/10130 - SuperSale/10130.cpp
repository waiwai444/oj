#include <stdio.h>
#include <string.h>

#define MAXW 30

int nobj, price[1000], weight[1000];
int dp[MAXW+1];

void solve()
{
	int i, j, p;
	memset(dp, 0, sizeof(dp));
	for(i = 0; i < nobj; i++)
	{
		for(j = MAXW; j >= weight[i]; j--)
		{
			p = dp[j-weight[i]]+price[i];
			if(p > dp[j])
				dp[j] = p;
		}
	}
}

int main()
{
	int i, tc, g, tot, mw;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d", &nobj);
		for(i = 0; i < nobj; i++)
			scanf("%d%d", &price[i], &weight[i]);
		scanf("%d", &g);
		solve();
		tot = 0;
		for(i = 0; i < g; i++)
		{
			scanf("%d", &mw);
			tot += dp[mw];
		}
		printf("%d\n", tot);
	}
	return 0;
}
