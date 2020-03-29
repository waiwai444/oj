#include <stdio.h>
#include <string.h>

#define HASH_SIZE 500

int len1, len2, seq1[100], seq2[100];
char hash_map[HASH_SIZE][30];
int dp[100][100], last[100][100];

int bkdr_hash(const char *str)
{
	int h = 0;
	while(*str != '\0')
		h = h*131+*str++;
	return h&0x7fffffff;
}

int get_hash_value(const char *str)
{
	int h = bkdr_hash(str)%HASH_SIZE;
	while(hash_map[h][0] != '\0')
		if(strcmp(hash_map[h], str) == 0)
			break;
		else if(++h >= HASH_SIZE)
			h = 0;
	return h;
}

void solve()
{
	int i, j;
	memset(dp, 0, sizeof(dp));
	memset(last, -1, sizeof(last));
	if(seq1[0] == seq2[0])
	{
		dp[0][0] = 1;
		last[0][0] = seq1[0];
	}
	for(i = 1; i < len1; i++)
	{
		if(seq1[i] == seq2[0])
		{
			dp[i][0] = 1;
			last[i][0] = seq1[i];
		}
		else
		{
			dp[i][0] = dp[i-1][0];
			last[i][0] = last[i-1][0];
		}
	}
	for(j = 1; j < len2; j++)
	{
		if(seq1[0] == seq2[j])
		{
			dp[0][j] = 1;
			last[0][j] = seq1[0];
		}
		else
		{
			dp[0][j] = dp[0][j-1];
			last[0][j] = last[0][j-1];
		}
	}
	for(i = 1; i < len1; i++)
	{
		for(j = 1; j < len2; j++)
		{
			dp[i][j] = dp[i-1][j];
			last[i][j] = last[i-1][j];
			if(dp[i][j-1] > dp[i][j])
			{
				dp[i][j] = dp[i][j-1];
				last[i][j] = last[i][j-1];
			}
			if(seq1[i] == seq2[j] && dp[i-1][j-1]+1 > dp[i][j])
			{
				dp[i][j] = dp[i-1][j-1]+1;
				last[i][j] = seq1[i];
			}
		}
	}
}

void output()
{
	int result[100];
	int l = last[len1-1][len2-1], p = dp[len1-1][len2-1]-1, i = len1-1, j = len2-1;
	while(p >= 0)
	{
		result[p--] = l;
		while(seq1[i--] != l);
		while(seq2[j--] != l);
		if(i >= 0 && j >= 0)
			l = last[i][j];
	}
	p = dp[len1-1][len2-1];
	if(p > 0)
		printf("%s", hash_map[result[0]]);
	for(i = 1; i < p; i++)
		printf(" %s", hash_map[result[i]]);
	printf("\n");
}

int main()
{
	int h;
	char word[30];
	while(scanf("%s", word) != EOF)
	{
		memset(hash_map, 0, sizeof(hash_map));
		len1 = len2 = 0;
		while(word[0] != '#')
		{
			h = get_hash_value(word);
			if(hash_map[h][0] == '\0')
				strcpy(hash_map[h], word);
			seq1[len1++] = h;
			scanf("%s", word);
		}
		scanf("%s", word);
		while(word[0] != '#')
		{
			h = get_hash_value(word);
			if(hash_map[h][0] == '\0')
				strcpy(hash_map[h], word);
			seq2[len2++] = h;
			scanf("%s", word);
		}
		solve();
		output();
	}
	return 0;
}
