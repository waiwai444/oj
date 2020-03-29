#include <stdio.h>
#include <string.h>

#define MOD 10007

char str1[62], str2[62], str3[62];
int len1, len2, len3;

int dp[61][61][61][2];
int prev1[61][26], prev2[61][26];
int sum[61][61][61][2];

void init()
{
	int i, j;
	len1 = strlen(str1+1);
	len2 = strlen(str2+1);
	len3 = strlen(str3+1);
	memset(prev1, 0, sizeof(prev1));
	memset(prev2, 0, sizeof(prev2));
	memset(sum, -1, sizeof(sum));
	for(i = 1; i <= len1; i++)
	{
		prev1[i][str1[i]-'a'] = i;
		for(j = i+1; j <= len1 && str1[i] != str1[j]; j++)
		{
			prev1[j][str1[i]-'a'] = i;
		}
	}
	for(i = 1; i <= len2; i++)
	{
		prev2[i][str2[i]-'a'] = i;
		for(j = i+1; j <= len2 && str2[i] != str2[j]; j++)
		{
			prev2[j][str2[i]-'a'] = i;
		}
	}
}

int solve()
{
	int i, j, k, p, q, s;
	for(j = 0; j <= len1; j++)
	{
		for(k = 0; k <= len2; k++)
		{
			dp[1][j][k][0] = (str3[1] == str1[j]) ? 1 : 0;
			dp[1][j][k][1] = (str3[1] == str2[k]) ? 1 : 0;
		}
	}
	for(i = 2; i <= len3; i++)
	{
		for(j = 0; j <= len1; j++)
		{
			for(k = 0; k <= len2; k++)
			{
				dp[i][j][k][0] = 0;
				if(str3[i] == str1[j])
				{
					for(s = 0, q = p = prev1[j-1][str3[i-1]-'a']; p >= 1; p = prev1[p-1][str3[i-1]-'a'])
					{
						if(sum[i-1][p][k][0] >= 0)
						{
							s = (s+sum[i-1][p][k][0])%MOD;
							break;
						}
						s = (s+dp[i-1][p][k][0])%MOD;
					}
					dp[i][j][k][0] = (dp[i][j][k][0]+s)%MOD;
					sum[i-1][q][k][0] = s;
					for(s = 0, q = p = prev2[k][str3[i-1]-'a']; p >= 1; p = prev2[p-1][str3[i-1]-'a'])
					{
						if(sum[i-1][j-1][p][1] >= 0)
						{
							s = (s+sum[i-1][j-1][p][1])%MOD;
							break;
						}
						s = (s+dp[i-1][j-1][p][1])%MOD;
					}
					dp[i][j][k][0] = (dp[i][j][k][0]+s)%MOD;
					sum[i-1][j-1][q][1] = s;
				}
				dp[i][j][k][1] = 0;
				if(str3[i] == str2[k])
				{
					for(s = 0, q = p = prev1[j][str3[i-1]-'a']; p >= 1; p = prev1[p-1][str3[i-1]-'a'])
					{
						if(sum[i-1][p][k-1][0] >= 0)
						{
							s = (s+sum[i-1][p][k-1][0])%MOD;
							break;
						}
						s = (s+dp[i-1][p][k-1][0])%MOD;
					}
					dp[i][j][k][1] = (dp[i][j][k][1]+s)%MOD;
					sum[i-1][q][k-1][0] = s;
					for(s = 0, q = p = prev2[k-1][str3[i-1]-'a']; p >= 1; p = prev2[p-1][str3[i-1]-'a'])
					{
						if(sum[i-1][j][p][1] >= 0)
						{
							s = (s+sum[i-1][j][p][1])%MOD;
							break;
						}
						s = (s+dp[i-1][j][p][1])%MOD;
					}
					dp[i][j][k][1] = (dp[i][j][k][1]+s)%MOD;
					sum[i-1][j][q][1] = s;
				}
			}
		}
	}

	int ret = 0;
	for(p = prev1[len1][str3[i-1]-'a']; p >= 1; p = prev1[p-1][str3[i-1]-'a'])
		ret = (ret+dp[len3][p][len2][0])%MOD;
	for(p = prev2[len2][str3[i-1]-'a']; p >= 1; p = prev2[p-1][str3[i-1]-'a'])
		ret = (ret+dp[len3][len1][p][1])%MOD;
	return ret;
}

int main()
{
	int tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%s%s%s", &str1[1], &str2[1], &str3[1]);
		init();
		printf("%d\n", solve());
	}
	return 0;
}
