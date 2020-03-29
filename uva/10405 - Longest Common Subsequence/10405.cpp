#include <stdio.h>
#include <string.h>

char str1[1001], str2[1001];
int len1, len2;
int dp[1000][1000];

int main()
{
	int i, j;
	while(fgets(str1, sizeof(str1), stdin))
	{
		fgets(str2, sizeof(str2), stdin);
		len1 = (int)strlen(str1);
		len2 = (int)strlen(str2);
		str1[--len1] = str2[--len2] = 0;
		dp[0][0] = str1[0] == str2[0] ? 1 : 0;
		for(i = 1; i < len1; i++)
			dp[i][0] = dp[i-1][0] == 1 || str1[i] == str2[0] ? 1 : 0;
		for(j = 1; j < len2; j++)
			dp[0][j] = dp[0][j-1] == 1 || str1[0] == str2[j] ? 1 : 0;
		for(i = 1; i < len1; i++)
		{
			for(j = 1; j < len2; j++)
			{
				dp[i][j] = 0;
				if(str1[i] == str2[j])
					dp[i][j] = dp[i-1][j-1]+1;
				if(dp[i][j] < dp[i][j-1])
					dp[i][j] = dp[i][j-1];
				if(dp[i][j] < dp[i-1][j])
					dp[i][j] = dp[i-1][j];
			}
		}
		printf("%d\n", dp[len1-1][len2-1]);
	}
	return 0;
}
