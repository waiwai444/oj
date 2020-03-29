#include <stdio.h>
#include <string.h>

int node_num, edge_num;

struct Edge
{
	int to;
	Edge* reversePtr;
	bool visited;
};

struct Node
{
	int edge_num;
	Edge edge[25];
};

Node node[25];

int dfs(int cur_node)
{
	int i, cur_max, max = 0;
	for(i = 0; i < node[cur_node].edge_num; i++)
	{
		if(!node[cur_node].edge[i].visited)
		{
			node[cur_node].edge[i].visited = true;
			node[cur_node].edge[i].reversePtr->visited = true;
			cur_max = dfs(node[cur_node].edge[i].to)+1;
			if(cur_max > max)
				max = cur_max;
			node[cur_node].edge[i].visited = false;
			node[cur_node].edge[i].reversePtr->visited = false;
		}
	}
	return max;
}

int longest_path()
{
	int i, max = 0, cur_max;
	for(i = 0; i < node_num; i++)
	{
		cur_max = dfs(i);
		if(cur_max > max)
			max = cur_max;
	}
	return max;
}

int main()
{
	int i, node1, node2, result;
	while(scanf("%d%d", &node_num, &edge_num), node_num)
	{
		memset(node, 0, sizeof(node));
		for(i = 0; i < edge_num; i++)
		{
			scanf("%d%d", &node1, &node2);
			node[node1].edge[node[node1].edge_num].to = node2;
			node[node2].edge[node[node2].edge_num].to = node1;
			node[node1].edge[node[node1].edge_num].reversePtr = &node[node2].edge[node[node2].edge_num];
			node[node2].edge[node[node2].edge_num].reversePtr = &node[node1].edge[node[node1].edge_num];
			node[node1].edge_num++;
			if(node1 != node2)
				node[node2].edge_num++;
		}
		result = longest_path();
		printf("%d\n", result);
	}
	return 0;
}
