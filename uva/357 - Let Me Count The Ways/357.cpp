#include <stdio.h>
#include <string.h>

const int value[5] = {50, 25, 10, 5, 1};
long long dp[30001][5];

void init()
{
	memset(dp, -1, sizeof(dp));
	for(int i = 0; i < 5; i++)
		dp[0][i] = 1;
}

long long recur(int amount, int idx)
{
	if(dp[amount][idx] == -1)
	{
		dp[amount][idx] = 0;
		if(idx < 4)
			dp[amount][idx] += recur(amount, idx+1);
		if(amount-value[idx] >= 0)
			dp[amount][idx] += recur(amount-value[idx], idx);
	}
	return dp[amount][idx];
}

int main()
{
	int target;
	long long result;
	init();
	while(scanf("%d", &target) != EOF)
	{
		result = recur(target, 0);
		if(result == 1)
			printf("There is only 1 way to produce %d cents change.\n", target);
		else
			printf("There are %lld ways to produce %d cents change.\n", result, target);
	}
	return 0;
}