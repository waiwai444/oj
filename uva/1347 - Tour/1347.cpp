#include <stdio.h>
#include <math.h>

#define MAXN 200

int n;
int x[MAXN], y[MAXN];

double dp[MAXN][MAXN];
double dist[MAXN][MAXN];

void get_dist()
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = i+1; j < n; j++)
		{
			dist[i][j] = dist[j][i] = sqrt((double)(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
		}
	}
}

double solve()
{
	int i, j;
	double tmp;
	if(n <= 1)
		return 0;
	get_dist();
	dp[0][0] = 0;
	dp[1][0] = dist[0][1];
	dp[1][1] = dist[0][1]+dist[0][1];
	for(i = 2; i < n; i++)
	{
		dp[i][0] = dp[i-1][0]+dist[i-1][i];
		dp[i][i-1] = dp[i-1][0]+dist[0][i];
		dp[i][i] = dp[i][0]+dist[0][i];
		for(j = 1; j < i-1; j++)
		{
			dp[i][j] = dp[i-1][j]+dist[i-1][i];
			tmp = dp[i-1][j]+dist[j][i];
			if(tmp < dp[i][i-1])
				dp[i][i-1] = tmp;
			tmp = dp[i][j]+dist[j][i];
			if(tmp < dp[i][i])
				dp[i][i] = tmp;
		}
		tmp = dp[i][i-1]+dist[i-1][i];
		if(tmp < dp[i][i])
			dp[i][i] = tmp;
	}
	return dp[n-1][n-1];
}

int main()
{
	int i;
	while(scanf("%d", &n) != EOF)
	{
		for(i = 0; i < n; i++)
			scanf("%d%d", &x[i], &y[i]);
		printf("%.2lf\n", solve());
	}
	return 0;
}