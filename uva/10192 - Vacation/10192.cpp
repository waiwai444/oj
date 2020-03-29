#include <stdio.h>
#include <string.h>

char seq1[110], seq2[110];
int len1, len2, dp[110][110];

int main()
{
	int i, j, tc = 0;
	while(fgets(seq1, sizeof(seq1), stdin), seq1[0] != '#')
	{
		fgets(seq2, sizeof(seq1), stdin);
		len1 = (int)strlen(seq1);
		len2 = (int)strlen(seq2);
		seq1[--len1] = seq2[--len2] = 0;
		dp[0][0] = seq1[0] == seq2[0] ? 1 : 0;
		for(i = 1; i < len1; i++)
			dp[i][0] = seq1[i] == seq2[0] ? 1 : dp[i-1][0];
		for(j = 1; j < len2; j++)
			dp[0][j] = seq1[0] == seq2[j] ? 1 : dp[0][j-1];
		for(i = 1; i < len1; i++)
			for(j = 1; j < len2; j++)
			{
				dp[i][j] = 0;
				if(seq1[i] == seq2[j])
					dp[i][j] = dp[i-1][j-1]+1;
				if(dp[i][j] < dp[i-1][j])
					dp[i][j] = dp[i-1][j];
				if(dp[i][j] < dp[i][j-1])
					dp[i][j] = dp[i][j-1];
			}
		printf("Case #%d: you can visit at most %d cities.\n", ++tc, dp[len1-1][len2-1]);
	}
	return 0;
}
