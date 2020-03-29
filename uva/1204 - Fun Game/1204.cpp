#include <stdio.h>
#include <string.h>
#include <limits.h>

int n;
char str[16][101];
char rev[16][101];
int len[16];
int overlap[16][16][2][2];
int dp[1<<16][16][2];

void init()
{
	int i, j, k;
	bool removed[16];
	for(i = 0; i < n; i++)
	{
		len[i] = strlen(str[i]);
		for(j = 0; j < len[i]; j++)
			rev[i][len[i]-j-1] = str[i][j];
		rev[i][len[i]] = '\0';
		removed[i] = false;
	}
	for(i = k = 0; i < n; i++)
	{
		if(removed[i])
			continue;
		for(j = i+1; j < n; j++)
		{
			if(removed[j])
				continue;
			if(strstr(str[i], str[j]) || strstr(str[i], rev[j]))
				removed[j] = true;
			else if(strstr(str[j], str[i]) || strstr(str[j], rev[i]))
				removed[i] = true;
		}
		if(!removed[i])
		{
			strcpy(str[k], str[i]);
			strcpy(rev[k], rev[i]);
			len[k++] = len[i];
		}
	}
	n = k;
}

int find_first_pos(const char *str1, int len1, const char *str2, int len2)
{
	int i;
	for(i = (len1 < len2 ? 1 : len1-len2+1); i < len1; i++)
		if(strncmp(str1+i, str2, len1-i) == 0)
			break;
	return i;
}

void get_overlap()
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		overlap[i][i][0][0] = len[i]-find_first_pos(str[i], len[i], str[i], len[i]);
		for(j = i+1; j < n; j++)
		{
			overlap[i][j][0][0] = len[i]-find_first_pos(str[i], len[i], str[j], len[j]);
			overlap[j][i][1][1] = overlap[i][j][0][0];
			overlap[i][j][0][1] = len[i]-find_first_pos(str[i], len[i], rev[j], len[j]);
			overlap[j][i][0][1] = overlap[i][j][0][1];
			overlap[i][j][1][0] = len[i]-find_first_pos(rev[i], len[i], str[j], len[j]);
			overlap[j][i][1][0] = overlap[i][j][1][0];
			overlap[i][j][1][1] = len[i]-find_first_pos(rev[i], len[i], rev[j], len[j]);
			overlap[j][i][0][0] = overlap[i][j][1][1];
		}
	}
}

int solve()
{
	int i, j, k, u, v, tmp;
	if(n == 1)
		return (tmp = len[0]-overlap[0][0][0][0]) < 2 ? 2 : tmp;
	dp[1][0][0] = len[0];
	for(i = 3; i < (1<<n); i += 2)
	{
		for(j = 1; j < n; j++)
		{
			if(i&(1<<j))
			{
				if((i&~(1<<j)) == 1)
				{
					dp[i][j][0] = len[0]+len[j]-overlap[0][j][0][0];
					dp[i][j][1] = len[0]+len[j]-overlap[0][j][0][1];
				}
				else
				{
					dp[i][j][0] = dp[i][j][1] = INT_MAX;
					for(k = 1; k < n; k++)
					{
						if(i&(1<<k) && j != k)
						{
							for(u = 0; u < 2; u++)
							{
								for(v = 0; v < 2; v++)
								{
									tmp = dp[i&~(1<<j)][k][v]+len[j]-overlap[k][j][v][u];
									if(dp[i][j][u] > tmp)
										dp[i][j][u] = tmp;
								}
							}
						}
					}
				}
			}
		}
	}
	int ret = INT_MAX;
	for(i = 1; i < n; i++)
	{
		for(j = 0; j < 2; j++)
		{
			tmp = dp[(1<<n)-1][i][j]-overlap[i][0][j][0];
			if(tmp < ret)
				ret = tmp;
		}
	}
	return ret;
}

int main()
{
	int i;
	while(scanf("%d", &n), n)
	{
		for(i = 0; i < n; i++)
			scanf("%s", str[i]);
		init();
		get_overlap();
		printf("%d\n", solve());
	}
	return 0;
}
