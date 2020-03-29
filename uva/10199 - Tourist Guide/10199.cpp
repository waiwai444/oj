
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <string>

#define MAXV 100

struct Graph
{
	char vertex_name[MAXV][32];
	int adj_mat[MAXV][MAXV];
	int nvertices;
	int nedges;
} graph;

std::map<std::string, int> loc_map;

int dfs(int v, bool *visited, int cut)	// return the number of vertices visited
{
	int i, count = 0;
	if(v != cut)
	{
		visited[v] = true;
		count++;
	}
	for(i = 0; i < graph.nvertices; i++)
	{
		if(graph.adj_mat[v][i] == 0 || i == cut || visited[i])
			continue;
		count += dfs(i, visited, cut);
	}
	return count;
}

int find_cut_vertex(int *cut_vertex)
{
	int i, j, ncuts = 0, nsubgraphs, nsubgraphs_new;
	bool visited[MAXV];
	nsubgraphs = 0;
	for(j = 0; j < graph.nvertices; j++)
		visited[j] = false;
	for(j = 0; j < graph.nvertices; j++)
	{
		if(visited[j])
			continue;
		nsubgraphs++;
		dfs(j, visited, -1);
	}
	for(i = 0; i < graph.nvertices; i++)	// delete each vertex
	{
		nsubgraphs_new = 0;
		for(j = 0; j < graph.nvertices; j++)
			visited[j] = false;
		for(j = 0; j < graph.nvertices; j++)
		{
			if(visited[j] || j == i)
				continue;
			nsubgraphs_new++;
			dfs(j, visited, i);
		}
		if(nsubgraphs_new > nsubgraphs)
			cut_vertex[ncuts++] = i;
	}
	return ncuts;
}

int main()
{
	int i, c, d = 1;
	char loc1[32], loc2[32];
	int cut_vertex[MAXV];
	std::string cut_vertex_name[MAXV];
	while(scanf("%d", &graph.nvertices))
	{
		if(graph.nvertices == 0)
			break;
		if(d > 1)
			printf("\n");
		for(i = 0; i < graph.nvertices; i++)
		{
			scanf("%s", loc1);
			strcpy(graph.vertex_name[i], loc1);
			loc_map[loc1] = i;
		}
		scanf("%d", &graph.nedges);
		memset(graph.adj_mat, 0, sizeof(graph.adj_mat));
		for(i = 0; i < graph.nedges; i++)
		{
			scanf("%s%s", loc1, loc2);
			int v = loc_map[loc1];
			int w = loc_map[loc2];
			graph.adj_mat[v][w] = graph.adj_mat[w][v] = 1;
		}
		
		printf("City map #%d: %d camera(s) found\n", d++, c = find_cut_vertex(cut_vertex));
		for(i = 0; i < c; i++)
			cut_vertex_name[i] = graph.vertex_name[cut_vertex[i]];
		std::sort(cut_vertex_name, cut_vertex_name + c);
		for(i = 0; i < c; i++)
			printf("%s\n", cut_vertex_name[i].c_str());
	}
	return 0;
}
