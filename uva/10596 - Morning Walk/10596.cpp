#include <stdio.h>
#include <string.h>

int node_num;
bool adj_matrix[200][200];
int degree[200];

void dfs(int node, bool visited[])
{
	int i;
	visited[node] = true;
	for(i = 0; i < node_num; i++)
		if(i != node && adj_matrix[node][i] && !visited[i])
			dfs(i, visited);
}

bool is_connected()
{
	bool visited[200];
	memset(visited, false, sizeof(visited));
	dfs(0, visited);
	for(int i = 0; i < node_num; i++)
		if(!visited[i] && degree[i] > 0)
			return false;
	return true;
}

int main()
{
	int i, edge_num;
	while(scanf("%d%d", &node_num, &edge_num) != EOF)
	{
		memset(degree, 0, sizeof(degree));
		memset(adj_matrix, false, sizeof(adj_matrix));
		for(i = 0; i < edge_num; i++)
		{
			int n1, n2;
			scanf("%d%d", &n1, &n2);
			adj_matrix[n1][n2] = adj_matrix[n2][n1] = true;
			degree[n1]++;
			degree[n2]++;
		}
		for(i = 0; i < node_num; i++)
			if(degree[i]%2 == 1)
				break;
		if(edge_num > 0 && i == node_num && is_connected())
			printf("Possible\n");
		else
			printf("Not Possible\n");
	}
	return 0;
}
