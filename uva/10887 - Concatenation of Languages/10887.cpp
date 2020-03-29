#include <stdio.h>
#include <string.h>

#define HASH_SIZE 2300003
#define MAX_LANG 1500

int m, n;
char lang1[MAX_LANG][11], lang2[MAX_LANG][11];
char concat[MAX_LANG*MAX_LANG][20];
int nc;

int hash_table[HASH_SIZE], hash_next[MAX_LANG*MAX_LANG];

int BKDRhash(const char *word)
{
	const unsigned int seed = 131;
	unsigned int r = 0;
	while(*word != '\0')
		r = r*seed+*word++;
	return (r&0x7fffffff)%HASH_SIZE;
}

int solve()
{
	int i, j, k, result = 0, h;
	memset(hash_table, -1, sizeof(hash_table));
	nc = 0;
	for(i = 0; i < m; i++)
	{
		for(j = 0; j < n; j++)
		{
			strcpy(concat[nc], lang1[i]);
			strcat(concat[nc], lang2[j]);
			h = BKDRhash(concat[nc]);
			for(k = hash_table[h]; k != -1; k = hash_next[k])
				if(strcmp(concat[nc], concat[k]) == 0)
					break;
			if(k == -1)
			{
				hash_next[nc] = hash_table[h];
				hash_table[h] = nc;
				nc++;
				result++;
			}
		}
	}
	return result;
}

int main()
{
	int i, t, c;
	scanf("%d", &t);
	for(c = 1; c <= t; c++)
	{
		scanf("%d%d", &m, &n);
		fgets(lang1[0], sizeof(lang1[0]), stdin);
		for(i = 0; i < m; i++)
		{
			fgets(lang1[i], sizeof(lang1[i]), stdin);
			lang1[i][strlen(lang1[i])-1] = 0;
		}
		for(i = 0; i < n; i++)
		{
			fgets(lang2[i], sizeof(lang2[i]), stdin);
			lang2[i][strlen(lang2[i])-1] = 0;
		}
		
		printf("Case %d: %d\n", c, solve());
	}
	return 0;
}
