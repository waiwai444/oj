#include <stdio.h>
#include <string.h>

char gene1[35];
char gene2[35];
int len1, len2;
int min_len[31][31];
unsigned int count[31][31];

void solve()
{
	int i, j, tmp;
	for(i = 0; i <= len1; i++)
	{
		min_len[i][0] = i;
		count[i][0] = 1;
	}
	for(j = 1; j <= len2; j++)
	{
		min_len[0][j] = j;
		count[0][j] = 1;
	}
	for(i = 1; i <= len1; i++)
	{
		for(j = 1; j <= len2; j++)
		{
			if(gene1[i] == gene2[j])
			{
				min_len[i][j] = min_len[i-1][j-1]+1;
				count[i][j] = count[i-1][j-1];
			}
			else
			{
				min_len[i][j] = min_len[i-1][j]+1;
				count[i][j] = count[i-1][j];
				
				tmp = min_len[i][j-1]+1;
				if(tmp < min_len[i][j])
				{
					min_len[i][j] = tmp;
					count[i][j] = count[i][j-1];
				}
				else if(tmp == min_len[i][j])
				{
					count[i][j] += count[i][j-1];
				}
			}
		}
	}
}

int main()
{
	int tc, c;
	scanf("%d", &tc);
	fgets(gene1, sizeof(gene1), stdin);
	for(c = 1; c <= tc; c++)
	{
		fgets(&gene1[1], sizeof(gene1)-1, stdin);
		fgets(&gene2[1], sizeof(gene2)-1, stdin);
		len1 = strlen(&gene1[1]);
		len2 = strlen(&gene2[1]);
		gene1[len1--] = gene2[len2--] = 0;
		solve();
		printf("Case #%d: %d %u\n", c, min_len[len1][len2], count[len1][len2]);
	}
	return 0;
}
