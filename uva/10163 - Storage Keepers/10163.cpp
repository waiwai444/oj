#include <stdio.h>
#include <string.h>

#define INF 0x3f3f3f3f 

int stor_num, kp_num;
int ability[30];

unsigned int dp[30][100];
int safe_line, total_cost;

void solve()
{
	int i, j, k, avg, sn;
	// calculate safe line
	for(j = 0; j < stor_num; j++)
		dp[0][j] = ability[0]/(j+1);
	for(i = 1; i < kp_num; i++)
	{
		for(j = 0; j < stor_num; j++)
		{
			dp[i][j] = ability[i]/(j+1);
			for(k = 0; k < j; k++)
			{
				avg = ability[i]/(j-k);
				sn = dp[i-1][k];
				if(sn > avg)
					sn = avg;
				if(dp[i][j] < sn)
					dp[i][j] = sn;
			}
			if(dp[i][j] < dp[i-1][j])
				dp[i][j] = dp[i-1][j];
		}
	}
	safe_line = dp[kp_num-1][stor_num-1];
	if(safe_line == 0)
	{
		total_cost = 0;
		return;
	}
	// calculate total cost with the safe line
	memset(dp, 0x3f, sizeof(dp));
	for(j = 0; j < stor_num; j++)
		if(ability[0]/(j+1) >= safe_line)	// must look after all storages since safe line > 0 here
			dp[0][j] = ability[0];
	for(i = 1; i < kp_num; i++)
	{
		for(j = 0; j < stor_num; j++)
		{
			dp[i][j] = dp[i-1][j];
			for(k = j-1; k >= 0; k--)
			{
				avg = ability[i]/(j-k);
				if(avg < safe_line)
					break;
				if(dp[i][j] > dp[i-1][k]+ability[i])
					dp[i][j] = dp[i-1][k]+ability[i];
			}
			if(k < 0)
			{
				avg = ability[i]/(j+1);
				if(avg >= safe_line && dp[i][j] > ability[i])
					dp[i][j] = ability[i];
			}
		}
	}
	total_cost = dp[kp_num-1][stor_num-1];
}

int main()
{
	int i;
	while(scanf("%d%d", &stor_num, &kp_num), stor_num)
	{
		for(i = 0; i < kp_num; i++)
			scanf("%d", &ability[i]);
		solve();
		printf("%d %d\n", safe_line, total_cost);
	}
	return 0;
}
