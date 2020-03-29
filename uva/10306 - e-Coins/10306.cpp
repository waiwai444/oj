#include <stdio.h>
#include <string.h>
#include <math.h>

#define INF 0x3f3f3f3f
#define UNKNOWN -1

int m, s;
struct _coin_type {int v, e;} coin[40];
int dp[301][301];

int recur(int a, int b, int cur)
{
	if(dp[a][b] != UNKNOWN)
		return dp[a][b];
	int a1, b1, ret;
	dp[a][b] = INF;
	for(int i = cur; i < m; i++)
	{
		a1 = a-coin[i].v;
		b1 = b-coin[i].e;
		if(a1 < 0 || b1 < 0)
			continue;
		ret = recur(a1, b1, i);
		if(dp[a][b] > ret+1)
			dp[a][b] = ret+1;
	}
	return dp[a][b];
}

int solve()
{
	int a, b, t, min = INF;
	memset(dp, UNKNOWN, sizeof(dp));
	dp[0][0] = 0;
	for(a = s; a >= 0; a--)
	{
		t = s*s-a*a;
		b = sqrt((double)t);
		if(b*b == t)
		{
			t = recur(a, b, 0);
			if(t < min)
				min = t;
		}
	}
	return min;
}

int main()
{
	int i, tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d", &m, &s);
		for(i = 0; i < m; i++)
			scanf("%d%d", &coin[i].v, &coin[i].e);
		int ret = solve();
		if(ret < INF)
			printf("%d\n", ret);
		else
			printf("not possible\n");
	}
	return 0;
}
