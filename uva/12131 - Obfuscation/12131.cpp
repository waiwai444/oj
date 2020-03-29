#include <stdio.h>
#include <string.h>

#define R 1001LL
const int ch_idx[26] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4};
const long long ch_rad[26] = {0, R, R*R, R*R*R, R*R*R*R, R*R*R*R*R,
							0, R, R*R, R*R*R, R*R*R*R, R*R*R*R*R,
							0, R, R*R, R*R*R, R*R*R*R, R*R*R*R*R,
							0, R, R*R, R*R*R, R*R*R*R, R*R*R*R*R,
							0, R};

char sentence[1002];
int slen;
long long sch[1001][5];

int n;
char words[10000][101];
int wlen[10000];
long long wch[10000][5];

int widx[26][10000];
int widx_len[26];

long long dp[1001];
int decipher[1001];

long long solve()
{
	int i, j, k, l, ch, w;
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	for(i = 0; i < slen; i++)
	{
		if(dp[i] > 0)
		{
			ch = sentence[i+1]-'a';
			for(j = 0; j < widx_len[ch]; j++)
			{
				w = widx[ch][j];
				l = wlen[w];
				if(i+l > slen || words[w][l-1] != sentence[i+l])
					continue;
				for(k = 0; k < 5; k++)
					if(wch[w][k] != sch[i+l][k]-sch[i][k])
						break;
				if(k == 5)
				{
					dp[i+l] += dp[i];
					decipher[i+l] = w;
				}
			}
		}
	}
	return dp[slen];
}

void init()
{
	int i, j, k, ch;
	long long t;
	slen = strlen(&sentence[1]);
	for(i = 1; i <= slen; i++)
	{
		for(j = 0; j < 5; j++)
			sch[i][j] = sch[i-1][j];
		sch[i][ch_idx[sentence[i]-'a']] += ch_rad[sentence[i]-'a'];
	}
	for(i = 0; i < 26; i++)
		widx_len[i] = 0;
	memset(wch, 0, sizeof(wch));
	for(i = 0; i < n; i++)
	{
		wlen[i] = strlen(words[i]);
		ch = words[i][0]-'a';
		widx[ch][widx_len[ch]++] = i;
		for(j = 0; j < wlen[i]; j++)
			wch[i][ch_idx[words[i][j]-'a']] += ch_rad[words[i][j]-'a'];
	}
}

void output_result_recur(int idx)
{
	if(idx <= 0)
		return;
	int w = decipher[idx];
	int l = wlen[w];
	output_result_recur(idx-l);
	printf("%s ", words[w]);
}

void output_result()
{
	int w = decipher[slen];
	int l = wlen[w];
	output_result_recur(slen-l);
	printf("%s\n", words[w]);
}

int main()
{
	int i, j, tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%s%d", &sentence[1], &n);
		for(i = 0; i < n; i++)
			scanf("%s", words[i]);
		init();
		long long ret = solve();
		if(ret == 0)
			printf("impossible\n");
		else if(ret == 1)
			output_result();
		else
			printf("ambiguous\n");
	}
	return 0;
}
