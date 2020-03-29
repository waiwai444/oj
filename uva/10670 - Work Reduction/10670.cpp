#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

struct Agency
{
	char name[17];
	int a, b;
	int cost;
};

int n, m, l;
Agency agency[100];

bool cmp(const Agency &a1, const Agency &a2)
{
	if(a1.cost == a2.cost)
		return strcmp(a1.name, a2.name) < 0;
	return a1.cost < a2.cost;
}

void solve()
{
	int i;
	for(i = 0; i < l; i++)
	{
		if(agency[i].a == 0)
		{
			agency[i].cost = 0;
			continue;
		}
		int cur = n, cost = 0, threshold = agency[i].b/agency[i].a;
		while(cur > m)
		{
			int next = cur/2, d;
			if(next >= m)
				d = cur-next;
			else
				d = cur-m;
			if(next >= m && d > threshold)
			{
				cost += agency[i].b;
			}
			else
			{
				cost += agency[i].a*d;
			}
			cur -= d;
		}
		agency[i].cost = cost;
	}
}

int main()
{
	int i, c, tc;
	char line[30];
	scanf("%d", &tc);
	for(c = 1; c <= tc; c++)
	{
		scanf("%d%d%d", &n, &m, &l);
		for(i = 0; i < l; i++)
		{
			scanf("%s", line);
			strcpy(agency[i].name, strtok(line, ":"));
			agency[i].a = atoi(strtok(NULL, ","));
			agency[i].b = atoi(strtok(NULL, "\0"));
		}
		solve();
		std::sort(agency, agency+l, cmp);
		printf("Case %d\n", c);
		for(i = 0; i < l; i++)
			printf("%s %d\n", agency[i].name, agency[i].cost);
	}
	return 0;
}
