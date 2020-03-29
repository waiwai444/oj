#include <stdio.h>
#include <string.h>

#define INF 0x3f3f3f3f

int width;
int word_num;
char word[10000][81];
int len[10000];
int dp[10000][80];

void solve()
{
	int i, j, k, p, sp, tmp;
	if(word_num == 1)
		return;
	// place the last word
	p = width-len[word_num-1];
	for(j = width-1; j > p; j--)
		dp[word_num-1][j] = INF;
	dp[word_num-1][p] = 0;
	if(p > 0)
	{
		for(j = p-1; j > 0; j--)
			dp[word_num-1][j] = INF;
		dp[word_num-1][0] = 500;
	}
	// place middle words
	for(i = word_num-2; i > 0; i--)
	{
		p = width-len[i];
		for(j = width-1; j > p; j--)
			dp[i][j] = INF;
		dp[i][p] = dp[i+1][0];
		if(p > 0)
		{
			for(j = p-1; j >= 0; j--)
			{
				dp[i][j] = INF;
				for(k = width-len[i+1], sp = k-(j+len[i]); sp > 0; k--, sp--)
					if((tmp = dp[i+1][k]+(sp-1)*(sp-1)) < dp[i][j])
						dp[i][j] = tmp;
			}
			if(dp[i][0] > dp[i+1][0]+500)
				dp[i][0] = dp[i+1][0]+500;
		}
	}
	// place the first word, only considering placing on the first position
	dp[0][0] = INF;
	for(k = width-len[1], sp = k-len[0]; sp > 0; k--, sp--)
		if((tmp = dp[1][k]+(sp-1)*(sp-1)) < dp[0][0])
			dp[0][0] = tmp;
	tmp = dp[1][0]+(len[0] == width ? 0 : 500);
	if(dp[0][0] > tmp)
		dp[0][0] = tmp;
}

void output()
{
	if(word_num == 1)
	{
		printf("%s\n", word[0]);
		return;
	}
	int i, j, k, cb;
	printf("%s", word[0]);
	cb = dp[0][0];
	k = len[0];
	for(i = 1; i < word_num; i++)
	{
		for(j = k+1; j < width; j++)
			if(dp[i][j] == cb-(j-k-1)*(j-k-1))
			{
				printf("%*s", len[i]+(j-k), word[i]);
				cb = dp[i][j];
				k = j+len[i];
				break;
			}
		if(j < width)
			continue;
		printf("\n%s", word[i]);
		cb = dp[i][0];
		k = len[i];
	}
	printf("\n");
}

int main()
{
	char line[500], *pw;
	while(scanf("%d", &width), width)
	{
		word_num = 0;
		fgets(line, sizeof(line), stdin);
		fgets(line, sizeof(line), stdin);
		line[strlen(line)-1] = 0;
		while(line[0] != '\0')
		{
			strcpy(word[word_num], strtok(line, " "));
			len[word_num] = strlen(word[word_num]);
			++word_num;
			while(pw = strtok(NULL, " "))
			{
				strcpy(word[word_num], pw);
				len[word_num] = strlen(word[word_num]);
				++word_num;
			}
			fgets(line, sizeof(line), stdin);
			line[strlen(line)-1] = 0;
		}
		solve();
		output();
		printf("\n");
	}
	return 0;
}
