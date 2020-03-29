#include <stdio.h>
#include <string.h>

struct Comb
{
	int b, s;
} comb[81];

int n;
bool conflict[81][81];

void check_conflict()
{
	int i, j;
	memset(conflict, false, sizeof(conflict));
	for(i = 0; i < n; i++)
		for(j = i+1; j < n; j++)
			if(comb[i].b&comb[j].b)
				conflict[i][j] = true;
}

int solve()
{
	int i, j, k, sc, max_sc(-1);
	for(i = 0; i < n; i++)
	{
		for(j = i+1; j < n; j++)
		{
			for(k = j+1; k < n; k++)
			{
				if(!conflict[i][j] && !conflict[i][k] && !conflict[j][k])
				{
					sc = comb[i].s+comb[j].s+comb[k].s;
					if(sc > max_sc)
						max_sc = sc;
				}
			}
		}
	}
	return max_sc;
}

int main()
{
	int i, a, b, c, sc, tc(0);
	while(scanf("%d", &n), n)
	{
		memset(comb, 0, sizeof(comb));
		for(i = 0; i < n; i++)
		{
			scanf("%d%d%d%d", &a, &b, &c, &comb[i].s);
			comb[i].b = 1<<a|1<<b|1<<c;
		}
		check_conflict();
		printf("Case %d: %d\n", ++tc, solve());
	}
	return 0;
}

