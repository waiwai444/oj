
#include <stdio.h>
#include <string.h>
#include <deque>

#define MAXP 1000
#define MAXC 20
#define MAXV (MAXC + MAXP + 2)

struct Edge
{
	int v;
	int capacity;
	int flow;
};

struct Network
{
	Edge adj_list[MAXV][MAXV];
	int ndegrees[MAXV];
	int nproblems;
	int ncats;
} network;	// bipartite graph from problems to categories

std::deque<int> vqueue;
bool visited[MAXV];

bool bfs(int source, int sink, int *parent)
{
	int i, v;
	vqueue.clear();
	memset(visited, false, sizeof(visited));
	parent[source] = -1;
	visited[source] = true;
	vqueue.push_back(source);
	while(!vqueue.empty())
	{
		v = vqueue.front();
		vqueue.pop_front();
		for(i = 0; i < network.ndegrees[v]; i++)
		{
			Edge &edge = network.adj_list[v][i];
			if(visited[edge.v] || edge.capacity == edge.flow)
				continue;
			parent[edge.v] = v;
			visited[edge.v] = true;
			if(edge.v == sink)
				return true;
			vqueue.push_back(edge.v);
		}
	}
	return false;
}

Edge* find_edge(int v, int w)
{
	for(int i = 0; i < network.ndegrees[v]; i++)
		if(network.adj_list[v][i].v == w)
			return &network.adj_list[v][i];
	return NULL;
}

int path_volume(int start, int end, int* parent)
{
	Edge *edge = find_edge(parent[end], end);
	int vol = edge->capacity - edge->flow;	
	if(start == parent[end])
		return vol;
	int vol2 = path_volume(start, parent[end], parent);
	return vol2 < vol ? vol2 : vol;
}

void augment_path(int start, int end, int vol, int *parent)
{
	find_edge(parent[end], end)->flow += vol;
	find_edge(end, parent[end])->flow -= vol;
	if(start != parent[end])
		augment_path(start, parent[end], vol, parent);
}

void edmonds_karp()
{
	int parent[MAXV];
	while(bfs(0, 1, parent))
		augment_path(0, 1, path_volume(0, 1, parent), parent);
}

int main()
{
	int i, j, k;
	int pro_begin, pro_end, cat_begin, cat_end;
	bool succeeded;
	pro_begin = 2;
	while(scanf("%d%d", &network.ncats, &network.nproblems))
	{
		if(network.ncats == 0)
			break;
		cat_end = (cat_begin = pro_end = 2 + network.nproblems) + network.ncats;
		memset(network.ndegrees, 0, sizeof(network.ndegrees));
		for(i = cat_begin; i < cat_end; i++)
		{
			Edge &edge = network.adj_list[i][network.ndegrees[i]++];
			edge.v = 1;
			scanf("%d", &edge.capacity);
			edge.flow = 0;
			Edge &edge_r = network.adj_list[1][network.ndegrees[1]++];
			edge_r.v = i;
			edge_r.capacity = 0;
			edge_r.flow = 0;
		}
		for(i = pro_begin; i < pro_end; i++)
		{
			scanf("%d", &j);
			while(j-- > 0)
			{
				Edge &edge = network.adj_list[i][network.ndegrees[i]++];
				scanf("%d", &k);
				edge.v = cat_begin + k - 1;
				edge.capacity = 1;
				edge.flow = 0;
				Edge &edge_r = network.adj_list[edge.v][network.ndegrees[edge.v]++];
				edge_r.v = i;
				edge_r.capacity = 0;
				edge_r.flow = 0;
			}
			Edge &edge = network.adj_list[0][network.ndegrees[0]++];
			edge.v = i;
			edge.capacity = 1;
			edge.flow = 0;
			Edge &edge_r = network.adj_list[i][network.ndegrees[i]++];
			edge_r.v = 0;
			edge_r.capacity = 0;
			edge_r.flow = 0;
		}
		
		edmonds_karp();
		
		succeeded = true;
		for(i = cat_begin; i < cat_end; i++)
		{
			Edge* edge = find_edge(i, 1);
			if(edge->capacity != edge->flow)
			{
				succeeded = false;
				break;
			}
		}
		if(succeeded)
		{
			printf("1\n");
			for(i = cat_begin; i < cat_end; i++)
			{
				k = 0;
				for(j = 0; j < network.ndegrees[i]; j++)
				{
					if(network.adj_list[i][j].v != 1 && network.adj_list[i][j].flow != 0)
					{
						if(k++ > 0)
							printf(" ");
						printf("%d", network.adj_list[i][j].v - pro_begin + 1);
					}
				}
				printf("\n");
			}
		}
		else
			printf("0\n");
	}
	return 0;
}
