#include <stdio.h>
#include <string.h>

char str[202];
int len;
const int max = ((unsigned int)1<<31)-1;
long long dp[201];

void solve()
{
	int i, j;
	long long d, tmp, cur;
	dp[0] = 0;
	for(i = 1; i <= len; i++)
	{
		cur = str[i]-'0';
		dp[i] = dp[i-1]+cur;
		for(j = i-1, d = 10; j > 0; j--, d*=10)
		{
			if(str[j] == '0')
				continue;
			cur += (str[j]-'0')*d;
			if(cur > max)
				break;
			tmp = dp[j-1]+cur;
			if(tmp > dp[i])
				dp[i] = tmp;
		}
	}
}

int main()
{
	int test_case;
	scanf("%d", &test_case);
	while(test_case--)
	{
		scanf("%s", &str[1]);
		len = strlen(&str[1]);
		solve();
		printf("%lld\n", dp[len]);
	}
	return 0;
}
