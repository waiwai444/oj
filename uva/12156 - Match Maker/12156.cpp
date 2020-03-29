#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 15
#define MAXS (1 << 15)
#define INVALID_ID (-1)

int n;

struct trie_node_t
{
	trie_node_t *next[26];
	int id;
};

trie_node_t men, women;
bool pmap[MAXN][MAXN];
int plist[MAXN][MAXN];
int plist_size[MAXN];
char name_m[MAXN][21];
char name_w[MAXN][21];

long long dp[MAXN][MAXS];
int match[MAXN][MAXS];
int ones[MAXS];

void clear(trie_node_t *node)
{
	node->id = INVALID_ID;
	for(int i = 0; i < 26; i++)
		if(node->next[i])
			clear(node->next[i]);
}

void add_item(trie_node_t *tree, char str[], int id)
{
	trie_node_t *node = tree;
	for(char *ch = str; *ch != '\0'; ++ch)
	{
		if(node->next[*ch-'a'] == NULL)
			node->next[*ch-'a'] = (trie_node_t *)malloc(sizeof(trie_node_t));
		node = node->next[*ch-'a'];
	}
	node->id = id;
}

int find_item(trie_node_t *tree, char str[])
{
	trie_node_t *node = tree;
	for(char *ch = str; *ch != '\0'; ++ch)
	{
		if(node->next[*ch-'a'] == NULL)
			return INVALID_ID;
		node = node->next[*ch-'a'];
	}
	return node->id;
}

void get_line(char *buf, int size)
{
	int len;
	fgets(buf, size, stdin);
	len = strlen(buf);
	while(len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r'))
		--len;
	buf[len] = '\0';
}

void init()
{
	clear(&men);
	clear(&women);
	memset(pmap, false, sizeof(pmap));
	for(int i = 0; i < MAXN; i++)
		plist_size[i] = 0;
}

void solve()
{
	int i, j, k, s, t;
	s = (1 << n);
	memset(dp, 0, sizeof(dp));
	if(n <= 0)
		return;
	for(i = 0; i < n; i++)
	{
		match[n-1][1 << i] = n;
		if(pmap[n-1][i])
		{
			dp[n-1][1 << i] = 1;
			match[n-1][1 << i] = i;
		}
	}
	for(i = n-2; i >= 0; i--)
	{
		for(j = 1; j < s; j++)
		{
			if(n-i != ones[j])
				continue;
			match[i][j] = n;
			for(k = 0; k < plist_size[i]; k++)
			{
				if(j & (1 << plist[i][k]))
				{
					t = j & ~(1 << plist[i][k]);
					dp[i][j] += dp[i+1][t];
					if(dp[i+1][t] > 0 && plist[i][k] < match[i][j])
						match[i][j] = plist[i][k];
				}
			}
		}
	}
}
                
typedef int (*compar_fn_t)(const void *, const void*);
                
int main()
{
	int i, j, c, tc, mid, wid, s;
	char line[400];
	char *ptr;

	for(i = 1; i < MAXS; i++)
	{
		ones[i] = 0;
		for(j = 0; j < MAXN; j++)
			if(i & (1 << j))
				++ones[i];
	}

	scanf("%d", &tc);
	for(c = 1; c <= tc; c++)
	{
		init();

		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%s", name_m[i]);
		for(i = 0; i < n; i++)
			scanf("%s", name_w[i]);
		qsort(name_m, n, sizeof(name_m[0]), (compar_fn_t)strcmp);
		qsort(name_w, n, sizeof(name_w[0]), (compar_fn_t)strcmp);
		for(i = 0; i < n; i++)
		{
			add_item(&men, name_m[i], i);
			add_item(&women, name_w[i], i);
		}
		get_line(line, sizeof(line));
		for(i = 0; i < n; i++)
		{
			get_line(line, sizeof(line));
			ptr = strtok(line, ":");
			mid = find_item(&men, ptr);
			while((ptr = strtok(NULL, " ")))
			{
				wid = find_item(&women, ptr);
				pmap[mid][wid] = true;
				plist[mid][plist_size[mid]++] = wid;
			}
		}

		solve();

		printf("Case %d:\n", c);
		s = (1 << n) - 1;
		if(dp[0][s] > 0)
		{
			printf("%lld\n", dp[0][s]);
			printf("%s %s", name_m[0], name_w[match[0][s]]);
			s &= ~(1 << match[0][s]);
			for(i = 1; i < n; i++)
			{
				printf(" %s %s", name_m[i], name_w[match[i][s]]);
				s &= ~(1 << match[i][s]);
			}
			printf("\n");
		}
		else
			printf("No Way\n");
	}
	return 0;
}
