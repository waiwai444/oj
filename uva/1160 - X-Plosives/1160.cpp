#include <cstdio>
#include <cstring>

int repr[100001];
int rank[100001];

int find(int x)
{
	return repr[x] == x ? x : repr[x] = find(repr[x]);
}

bool union_set(int x, int y)
{
	int rx = find(x), ry = find(y);
	if(rx == ry)
		return false;
	if(rank[rx] >= rank[ry])
	{
		repr[ry] = rx;
		if(rank[rx] == rank[ry])
			++rank[rx];
	}
	else
		repr[rx] = ry;
	return true;
}

int main()
{
	int i, x, y, rx, ry, ans;
	while(scanf("%d%d", &x, &y) != EOF)
	{
		ans = 0;
		for(i = 0; i <= 100000; i++)
		{
			repr[i] = i;
			rank[i] = 0;
		}
		repr[y] = x;
		rank[x] = 1;
		while(scanf("%d", &x), x >= 0)
		{
			scanf("%d", &y);
			if(!union_set(x, y))
				++ans;
		}
		printf("%d\n", ans);
	}
	return 0;
}

