
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXV 50
#define MAXE 1000

struct Graph
{
	int adj_mat[MAXV][MAXV];
	int degree[MAXV];
	int nedges;
	int nvertices;
} graph;

int path[MAXE];
int path_len;

bool euler(int v)
{
	if((graph.degree[v] & 1) == 1)	// odd degree
		return false;
	for(int w = 0; w < MAXV; ++w)
	{
		if(graph.adj_mat[v][w] == 0)
			continue;
		if(v != w)
		{
			graph.adj_mat[v][w]--;
			graph.adj_mat[w][v]--;
			if(!euler(w))
				return false;
			path[path_len++] = w;
		}
		else	// loop
		{
			int nloops = graph.adj_mat[v][v];
			graph.adj_mat[v][v] = 0;
			if(!euler(v))
				return false;
			for(int i = 0; i < nloops; ++i)
				path[path_len++] = v;
		}
	}
	return true;
}

int main()
{
	int i, t, T, v, w;
	scanf("%d", &T);
	for(t = 1; t <= T; ++t)
	{
		memset(graph.adj_mat, 0, sizeof(graph.adj_mat));
		memset(graph.degree, 0, sizeof(graph.degree));
		scanf("%d", &graph.nedges);
		graph.nvertices = 0;
		int min_v = MAXV;
		for(i = 0; i < graph.nedges; ++i)
		{
			scanf("%d%d", &v, &w);
			v -= 1; w -= 1;
			
			if(graph.degree[v] == 0)
				graph.nvertices++;
			graph.degree[v]++;
			if(graph.degree[w] == 0)
				graph.nvertices++;
			graph.degree[w]++;
			
			graph.adj_mat[v][w]++;
			if(v != w)
				graph.adj_mat[w][v]++;
			
			if(v < min_v)
				min_v = v;
			if(w < min_v)
				min_v = w;
		}
		printf("Case #%d\n", t);
		path_len = 0;
		if(euler(min_v) && path_len == graph.nedges)
		{				
			for(i = 0; i < graph.nedges - 1; ++i)
				printf("%d %d\n", path[i] + 1, path[i + 1] + 1);
			printf("%d %d\n", path[graph.nedges - 1] + 1, path[0] + 1);
		}
		else
		{
			printf("some beads may be lost\n");
		}
		if(t < T)
			printf("\n");
	}
	return 0;
}
