#include <stdio.h>
#include <string.h>

#define SIMPLE 0
#define FULLY_GROWN 1
#define MUTAGENIC 2
#define MUTANT 3

char chain[1024];
char dp[1024][1024];

int main()
{
	int i, j, n, len;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%s", chain);
		len = strlen(chain);
		for(i = 0; i < len; i++)
			dp[i][i] = chain[i] == 'A' ? SIMPLE : MUTANT;
		for(i = 1; i < len; i++)
			dp[i-1][i] = MUTANT;
		for(i = 3; i <= len; i++)
		{
			for(j = i-1; j < len; j++)
			{
				if(chain[j-1] == 'A' && chain[j] == 'B' && dp[j-i+1][j-2] != MUTANT)
					dp[j-i+1][j] = FULLY_GROWN;
				else if(chain[j-i+1] == 'B' && chain[j] == 'A' && dp[j-i+2][j-1] != MUTANT)
					dp[j-i+1][j] = MUTAGENIC;
				else
					dp[j-i+1][j] = MUTANT;
			}
		}
		switch(dp[0][len-1])
		{
			case SIMPLE:
				printf("SIMPLE\n");
				break;
			case FULLY_GROWN:
				printf("FULLY-GROWN\n");
				break;
			case MUTAGENIC:
				printf("MUTAGENIC\n");
				break;
			default:
				printf("MUTANT\n");
		}
	}
	return 0;
}