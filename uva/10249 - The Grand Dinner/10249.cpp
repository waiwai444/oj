
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <functional>

#define MAX_TEAM 70
#define MAX_TABLE 50

struct Object
{
	int id;
	int size;
};

int nteams, ntables;
Object team[MAX_TEAM];
Object table[MAX_TABLE];

bool assignment[MAX_TEAM][MAX_TABLE];

bool cmp(const Object& o1, const Object& o2)
{
	return o1.size > o2.size;
}

int main()
{
	int i, j, k;
	while(scanf("%d%d", &nteams, &ntables))
	{
		if(nteams == 0)
			break;
		for(i = 0; i < nteams; i++)
		{
			team[i].id = i;
			scanf("%d", &team[i].size);
		}
		for(i = 0; i < ntables; i++)
		{
			table[i].id = i;
			scanf("%d", &table[i].size);
		}
		std::sort(team, team + nteams, cmp);
		std::sort(table, table + ntables, cmp);
		memset(assignment, false, sizeof(assignment));
		for(i = 0; i < nteams; i++)
		{
			if(team[i].size > ntables)
				goto failed;
			for(j = 0, k = 0; j < team[i].size && k < ntables; k++)
			{
				if(table[k].size > 0)
				{
					assignment[team[i].id][table[k].id] = true;
					table[k].size--;
					j++;
				}
				if(ntables - k - 1 < team[i].size - j)
					goto failed;
			}
		}
		printf("1\n");
		for(i = 0; i < nteams; i++)
		{
			k = 0;
			for(j = 0; j < ntables; j++)
			{
				if(assignment[i][j])
				{
					if(k++ > 0)
						printf(" ");
					printf("%d", j + 1);
				}
			}
			printf("\n");
		}
		continue;
failed:
		printf("0\n");
	}
	return 0;
}
