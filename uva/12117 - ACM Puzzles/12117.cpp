#include <stdio.h>

#define MAX 1000000000000LL

int n;
const int nleft[22] = {7, 7, 2, 2, 1, 7, 1, 1, 1, 2, 2, 7, 2, 7, 3, 2, 2, 7, 3, 3, 3, 7};
const int left[22][7] = {
	{0, 2, 3, 6, 12, 14, 18},
	{0, 2, 3, 6, 12, 14, 18},
	{1, 4},
	{13, 19},
	{5},
	{0, 2, 3, 6, 12, 14, 18},
	{5},
	{15},
	{16},
	{13, 19},
	{17, 20},
	{0, 2, 3, 6, 12, 14, 18},
	{17, 20},
	{0, 2, 3, 6, 12, 14, 18},
	{8, 10, 21},
	{13, 19},
	{17, 20},
	{0, 2, 3, 6, 12, 14, 18},
	{7, 9, 11},
	{8, 10, 21},
	{7, 9, 11},
	{0, 2, 3, 6, 12, 14, 18}
};
const int start[] = {0, 1, 5, 11, 13, 17, 21};
const int end[] = {0, 2, 3, 6, 12, 14, 18};
const int width[] = {1, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 2};

long long dp[2000][22];
long long res[2000];

void solve()
{
	int i, j, k, w;
	for(i = 0; i < 7; i++)
	{
		j = start[i];
		dp[width[j]-1][j] = 1;
	}
	dp[1][0] = 1;
	res[0] = res[1] = 1;
	for(i = 2; i < 2000; i++)
	{
		for(j = 0; j < 22; j++)
		{
			dp[i][j] = 0;
			w = width[j];
			for(k = 0; k < nleft[j]; k++)
			{
				dp[i][j] += dp[i-w][left[j][k]];
				if(dp[i][j] >= MAX)
					dp[i][j] -= MAX;
			}
		}
		for(j = 0; j < 7; j++)
		{
			res[i] += dp[i][end[j]];
			if(res[i] >= MAX)
				res[i] -= MAX;
		}
	}
}

int main()
{
	int c = 0;
	solve();
	while(scanf("%d", &n), n)
		printf("Case %d: %lld\n", ++c, res[n-1]);
	return 0;
}
