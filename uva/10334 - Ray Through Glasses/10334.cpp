#include <stdio.h>

int n;
struct biguint
{
	char d[500];
	int len;
} ans[1001], dp[1001][2];

void solve()
{
	int i, j;
	char c;
	dp[0][0].d[0] = 1;
	dp[0][0].len = 1;
	dp[0][1].len = 1;
	for(i = 1; i <= 1000; i++)
	{
		for(j = 0; j < dp[i-1][0].len; j++)
		{
			dp[i][0].d[j] = dp[i-1][0].d[j];
			dp[i][1].d[j] = dp[i-1][0].d[j];
			dp[i][0].len = dp[i][1].len = dp[i-1][0].len;
		}
		c = 0;
		for(j = 0; j < dp[i][0].len; j++)
		{
			dp[i][0].d[j] += dp[i-1][1].d[j]+c;
			if(dp[i][0].d[j] >= 10)
			{
				c = dp[i][0].d[j]/10;
				dp[i][0].d[j] %= 10;
			}
			else
				c = 0;
		}
		if(c > 0)
			dp[i][0].d[dp[i][0].len++] = c;
	}
	for(i = 0; i <= 1000; i++)
	{
		c = 0;
		for(j = 0; j < dp[i][0].len; j++)
		{
			ans[i].d[j] = dp[i][0].d[j]+dp[i][1].d[j]+c;
			if(ans[i].d[j] >= 10)
			{
				c = ans[i].d[j]/10;
				ans[i].d[j] %= 10;
			}
			else
				c = 0;
		}
		if(c > 0)
			ans[i].d[j++] = c;
		ans[i].len = j;
	}
}

void print_ans()
{
	int i;
	char buf[500];
	for(i = 0; i < ans[n].len; i++)
	{
		buf[i] = ans[n].d[ans[n].len-i-1]+'0';
	}
	buf[i] = '\0';
	printf("%s\n", buf);
}

int main()
{
	solve();
	while(scanf("%d", &n) != EOF)
	{
		print_ans();
	}
	return 0;
}

