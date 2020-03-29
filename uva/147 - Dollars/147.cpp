#include <stdio.h>
#include <string.h>

const int value[11] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5};
long long dp[30001][11];

void init()
{
	memset(dp, -1, sizeof(dp));
	for(int i = 0; i < 11; i++)
		dp[0][i] = 1;
}

long long recur(int amount, int idx)
{
	if(dp[amount][idx] == -1)
	{
		dp[amount][idx] = 0;
		if(idx < 10)
			dp[amount][idx] += recur(amount, idx+1);
		if(amount-value[idx] >= 0)
			dp[amount][idx] += recur(amount-value[idx], idx);
	}
	return dp[amount][idx];
}

int main()
{
	double tmp;
	int target;
	init();
	while(scanf("%lf", &tmp))
	{
		target = tmp*100+0.5;
		if(target == 0)
			break;
		printf("%6.2lf%17lld\n", tmp, recur(target, 0));
	}
	return 0;
}