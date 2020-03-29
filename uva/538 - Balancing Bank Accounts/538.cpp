#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <algorithm>

int n;
struct person_t
{
	char name[20];
	int acc;
} ps[20];
std::map<std::string, int> idx;

bool cmp_ps(const person_t &p1, const person_t &p2)
{
	return p1.acc >= p2.acc;
}

void solve()
{
	int i, j, v;
	std::sort(&ps[0], &ps[n], cmp_ps);
	i = 0, j = n-1;
	while(i < j)
	{
		v = ps[i].acc > -ps[j].acc ? -ps[j].acc : ps[i].acc;
		if(v > 0)
			printf("%s %s %d\n", ps[i].name, ps[j].name, v);
		if(ps[i].acc > -ps[j].acc)
		{
			ps[i].acc -= -ps[j].acc;
			--j;
		}
		else if(ps[i].acc < -ps[j].acc)
		{
			ps[j].acc += ps[i].acc;
			++i;
		}
		else
		{
			++i, --j;
		}
	}
}

int main()
{
	int i, t, v, p, q, c = 0;
	char name1[20], name2[20];
	while(scanf("%d%d", &n, &t), n)
	{
		idx.clear();
		for(i = 0; i < n; i++)
		{
			scanf("%s", ps[i].name);
			ps[i].acc = 0;
			idx[ps[i].name] = i;
		}
		for(i = 0; i < t; i++)
		{
			scanf("%s%s%d", name1, name2, &v);
			if(v == 0)
				continue;
			p = idx[name1];
			q = idx[name2];
			ps[p].acc -= v;
			ps[q].acc += v;
		}
		printf("Case #%d\n", ++c);
		solve();
		printf("\n");
	}
	return 0;
}

