#include <stdio.h>

struct edge_t
{
	int to;
	int len;
	edge_t *next;
} edge_set[20000], *edge_list[10001];

int nv, ne;
int res;

void init()
{
	for(int i = 1; i <= nv; i++)
		edge_list[i] = NULL;
	nv = ne = res = 0;
}

void insert_edge(const char *line)
{
	int v1, v2, len;
	sscanf(line, "%d%d%d", &v1, &v2, &len);

	edge_t *edge = &edge_set[ne++];
	edge->to = v2;
	edge->len = len;
	edge->next = edge_list[v1];
	edge_list[v1] = edge;

	edge = &edge_set[ne++];
	edge->to = v1;
	edge->len = len;
	edge->next = edge_list[v2];
	edge_list[v2] = edge;

	if(v1 > nv)
		nv = v1;
	if(v2 > nv)
		nv = v2;
}

int dfs(int cur, int pre)
{
	int rl, mrl = 0;
	edge_t *edge;
	for(edge = edge_list[cur]; edge != NULL; edge = edge->next)
	{
		if(edge->to == pre)
			continue;
		rl = edge->len + dfs(edge->to, cur);
		if(rl + mrl > res)
			res = rl + mrl;
		if(rl > mrl)
			mrl = rl;
	}
	return mrl;
}

int main()
{
	char line[100];
	while(!feof(stdin))
	{
		init();
		while(fgets(line, sizeof(line), stdin))
		{
			if(line[0] == '\n' || line[0] == '\r')
				break;
			insert_edge(line);
		}
		dfs(1, 0);
		printf("%d\n", res);
	}
	return 0;
}