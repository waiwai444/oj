#include <stdio.h>
#include <string.h>

#define MATCH 0
#define LEFT 1
#define RIGHT 2

char str[1001], pal[2000];
int len;
int dp[1000][1000];
int ch[1000][1000];

void solve()
{
	int i, j, s;
	len = strlen(str);
	for(i = 0; i < len; i++)
	{
		dp[i][i] = 0;
		ch[i][i] = MATCH;
	}
	for(s = 1; s < len; s++)
	{
		for(i = 0; (j=i+s) < len; i++)
		{
			dp[i][j] = dp[i+1][j]+1;
			ch[i][j] = LEFT;
			if(dp[i][j-1]+1 < dp[i][j])
			{
				dp[i][j] = dp[i][j-1]+1;
				ch[i][j] = RIGHT;
			}
			if(str[i] == str[j] && dp[i+1][j-1] < dp[i][j])
			{
				dp[i][j] = dp[i+1][j-1];
				ch[i][j] = MATCH;
			}
		}
	}
}

void output()
{
	int i, j, k;
	i = k = 0;
	j = len-1;
	while(i <= j)
	{
		if(ch[i][j] == MATCH)
		{
			pal[k] = str[i];
			i++;
			j--;
		}
		else if(ch[i][j] == LEFT)
		{
			pal[k] = str[i];
			i++;
		}
		else if(ch[i][j] == RIGHT)
		{
			pal[k] = str[j];
			j--;
		}
		k++;
	}
	i = i-2 == j ? k-2 : k-1;
	while(i >= 0)
	{
		pal[k++] = pal[i--];
	}
	pal[k] = '\0';
	printf("%d %s\n", dp[0][len-1], pal);
}

int main()
{
	while(scanf("%s", str) != EOF)
	{
		solve();
		output();
	}
	return 0;
}
