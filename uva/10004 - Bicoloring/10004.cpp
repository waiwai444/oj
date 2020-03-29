
#include <stdio.h>
#include <string.h>
#include <queue>

#define MAX_NODE 200

struct Graph
{
	char adj_mat[MAX_NODE][MAX_NODE];
	int nvertices;
	int nedges;
};

Graph graph;
signed char color[MAX_NODE];	// -1, 0, 1

bool bfs()
{
	int x, y;
	std::queue<int> node_queue;
	color[0] = -1;
	node_queue.push(0);
	while(!node_queue.empty())
	{
		x = node_queue.front();
		node_queue.pop();
		for(y = 0; y < graph.nvertices; y++)
		{
			if(graph.adj_mat[x][y] == 1)
			{
				if(color[y] == 0)
				{
					color[y] = -color[x];
					node_queue.push(y);
				}
				else if(color[x] * color[y] > 0)
					return false;
			}
		}
	}
	return true;
}

int main()
{
	int i, x, y;
	scanf("%d", &graph.nvertices);
	while(graph.nvertices != 0)
	{
		scanf("%d", &graph.nedges);
		memset(graph.adj_mat, 0, MAX_NODE * MAX_NODE * sizeof(char));
		memset(color, 0, MAX_NODE * sizeof(char));
		for(i = 0; i < graph.nedges; i++)
		{
			scanf("%d %d", &x, &y);
			graph.adj_mat[x][y] = graph.adj_mat[y][x] = 1;
		}
		if(bfs())
			printf("BICOLORABLE.\n");
		else
			printf("NOT BICOLORABLE.\n");
		scanf("%d", &graph.nvertices);
	}
	return 0;
}