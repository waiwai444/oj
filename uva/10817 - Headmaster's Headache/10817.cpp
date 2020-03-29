#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF 0x3f3f3f3f
#define INF8 0x3f

int sub_num, serv_num, app_num;
struct teacher_t
{
	int cost;
	unsigned char subs;
} serv[20], app[100];

int cost[65536];

void get_subs(char subs[], teacher_t *t)
{
	int i;
	char *s;
	t->subs = 0;
	s = strtok(subs, " \n");
	while(s)
	{
		i = atoi(s);
		t->subs |= 1 << (i - 1);
		s = strtok(NULL, " \n");
	}
}

unsigned short add_teacher(unsigned short subs, unsigned char t)
{
	int i;
	for(i = 0; i < sub_num; i++)
	{
		if((t & (1 << i)) && (subs & (1 << sub_num + i)) == 0)
		{
			if((subs & (1 << i)) == 0)
				subs |= (1 << i);
			else
			{
				subs &= ~(1 << i);
				subs |= (1 << sub_num + i);
			}
		}
	}
	return subs;
}

unsigned short handle_serving_teachers()
{
	int i, sum = 0;
	unsigned short subs = 0;
	for(i = 0; i < serv_num; i++)
	{
		sum += serv[i].cost;
		subs = add_teacher(subs, serv[i].subs);
	}
	cost[subs] = sum;
	return subs;
}

int solve()
{
	int i, j, k;
	unsigned short min_idx, max_idx;
	memset(cost, INF8, sizeof(cost));
	min_idx = handle_serving_teachers();
	max_idx = ((1 << sub_num) - 1) << sub_num;
	for(i = 0; i < app_num; i++)
	{
		for(j = max_idx - 1; j >= min_idx; j--)
		{
			if(cost[j] < INF)
			{
				k = add_teacher(j, app[i].subs);
				if(k != j && cost[j] + app[i].cost < cost[k])
					cost[k] = cost[j] + app[i].cost;
			}
		}
	}
	return cost[max_idx];
}

int main()
{
	int i;
	char subs[30];
	while(scanf("%d%d%d", &sub_num, &serv_num, &app_num), sub_num)
	{
		for(i = 0; i < serv_num; i++)
		{
			scanf("%d", &serv[i].cost);
			fgets(subs, sizeof(subs), stdin);
			get_subs(subs, &serv[i]);
		}
		for(i = 0; i < app_num; i++)
		{
			scanf("%d", &app[i].cost);
			fgets(subs, sizeof(subs), stdin);
			get_subs(subs, &app[i]);
		}
		printf("%d\n", solve());
	}
	return 0;
}
