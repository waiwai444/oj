
#include <string.h>
#include <stdio.h>
#include <algorithm>

#define MAXV 100

struct Graph
{
	unsigned int adj_mat[MAXV + 1][MAXV + 1];
	int nvertices;
} graph;

unsigned int max_cap[MAXV + 1];	// max capacity
bool processed[MAXV + 1];

unsigned int dijkstra(int src, int dest)
{
	int i, j, k, t;
	unsigned int maxc;
	memset(processed, false, sizeof(bool) * (graph.nvertices + 1));
	max_cap[src] = (unsigned int)-1;
	for(i = 1; i <= graph.nvertices; i++)
		if(i != src)
			max_cap[i] = graph.adj_mat[src][i];
	processed[src] = true;
	for(i = 1; i < graph.nvertices; i++)
	{
		maxc = 0;
		for(j = 1; j <= graph.nvertices; j++)
			if(!processed[j] && max_cap[j] > maxc)	// connected graph
			{
				maxc = max_cap[j];
				t = j;
			}
		for(j = 1; j <= graph.nvertices; j++)
			if(!processed[j] && max_cap[j] < (k = std::min(max_cap[t], graph.adj_mat[t][j])))
				max_cap[j] = k;
		processed[t] = true;
	}
	return max_cap[dest];
}

int main()
{
	int i, c, N, R, C1, C2, P;
	unsigned int cap, res;
	c = 0;
	while(1)
	{
		scanf("%d %d", &N, &R);
		if(N == 0)
			break;
		memset(graph.adj_mat, 0, sizeof(unsigned int) * (MAXV + 1) * (MAXV + 1));
		graph.nvertices = N;
		for(i = 0; i < R; i++)
		{
			scanf("%d %d %d", &C1, &C2, &P);
			graph.adj_mat[C1][C2] = graph.adj_mat[C2][C1] = P;
		}
		scanf("%d %d %d", &C1, &C2, &P);
		cap = dijkstra(C1, C2);
		--cap;
		if(P % cap == 0)
			res = P / cap;
		else
			res = P / cap + 1;
		printf("Scenario #%d\nMinimum Number of Trips = %d\n\n", ++c, res);
	}
	return 0;
}
