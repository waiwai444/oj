#include <stdio.h>

// disjoint-set
int parent[50000];
int rank[50000];
int nsets;

inline void make_set(int n)
{
	for(int i = 0; i < n; i++)
	{
		parent[i] = i;
		rank[i] = 1;
	}
	nsets = n;
}

int find(int x)
{
	return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void union_set(int x, int y)
{
	int px, py;
	px = find(x);
	py = find(y);
	if(px == py)
		return;
	if(rank[px] >= rank[py])
	{
		parent[py] = px;
		rank[px] += rank[py];
	}
	else
	{
		parent[px] = py;
		rank[py] += rank[px];
	}
	nsets--;
}

int main()
{
	int n, m, tc = 0, x, y;
	while(scanf("%d%d", &n, &m), n)
	{
		make_set(n);
		while(m--)
		{
			scanf("%d%d", &x, &y);
			union_set(x, y);
		}
		printf("Case %d: %d\n", ++tc, nsets);
	}
	return 0;
}
