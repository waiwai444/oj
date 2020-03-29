#include <cstdio>
#include <vector>
#include <utility>

int k, n;
std::vector<int> v;
std::vector<std::pair<int, int> > e;

int add_vertex(int d)
{
	int i, c = ++n, t;
	for(i = 1; i < d; i++)
	{
		t = add_vertex(i);
		e.push_back(std::make_pair(c, t));
	}
	v.push_back(c);
	return c;
}

void solve()
{
	n = 0;
	v.clear();
	e.clear();
	add_vertex(k);
}

int main()
{
	int i;
	while(scanf("%d", &k) != EOF)
	{
		solve();
		printf("%lu %lu\n", v.size(), e.size());
		for(i = 0; i < e.size(); i++)
			printf("%d %d\n", e[i].first, e[i].second);
		printf("%d", v[0]);
		for(i = 1; i < v.size(); i++)
			printf(" %d", v[i]);
		printf("\n");
	}
	return 0;
}

