#include <stdio.h>
#include <string.h>
#include <math.h>

int n;
int x[16], y[16];
double dist[16][16];
struct _state_type { double sum; bool valid; } dp[65536];

void get_dist()
{
	for(int i = 0; i < n; i++)
		for(int j = i+1; j < n; j++)
			dist[i][j] = sqrt((double)((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])));
}

double recur(int cur)
{
	if(dp[cur].valid)
		return dp[cur].sum;
	int i, j;
	for(i = 0; i < n; i++)
		if(cur&(1<<i))
			break;
	for(j = i+1; j < n; j++)
	{
		if(!(cur&(1<<j)))
			continue;
		double tmp = dist[i][j]+recur(cur&~(1<<i)&~(1<<j));
		if(!dp[cur].valid || tmp < dp[cur].sum)
		{
			dp[cur].sum = tmp;
			dp[cur].valid = true;
		}
	}
	return dp[cur].sum;
}

double solve()
{
	get_dist();
	memset(dp, 0, sizeof(dp));
	dp[0].sum = 0;
	dp[0].valid = true;
	return recur((1<<n)-1);
}

int main()
{
	int i, tc = 0;
	while(scanf("%d", &n), n)
	{
		n <<= 1;
		for(i = 0; i < n; i++)
			scanf("%*s%d%d", &x[i], &y[i]);
		printf("Case %d: %.2lf\n", ++tc, solve());
	}
	return 0;
}
