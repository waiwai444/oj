#include <stdio.h>
#include <string.h>

#define WHITE 0
#define BLACK 1

int n, k;
bool graph[101][101];
bool isolated[101];

int res_color[101], cur_color[101];
int max_black_num;

bool black_colorable(int node)
{
	for(int i = 1; i < node; i++)
		if(graph[i][node] && cur_color[i] == BLACK)
			return false;
	return true;
}

void dfs(int cur_node, int cur_black_num)
{
	if(cur_node > n)
	{
		if(cur_black_num > max_black_num)
		{
			memcpy(res_color, cur_color, sizeof(res_color));
			max_black_num = cur_black_num;
		}
		return;
	}
	
	if(isolated[cur_node])
	{
		cur_color[cur_node] = BLACK;
		dfs(cur_node+1, cur_black_num+1);
	}
	else if(black_colorable(cur_node))
	{
		cur_color[cur_node] = BLACK;
		dfs(cur_node+1, cur_black_num+1);
		
		if(cur_node < n || cur_black_num+(n-cur_node) > max_black_num)
		{
			cur_color[cur_node] = WHITE;
			dfs(cur_node+1, cur_black_num);
		}
	}
	else if(cur_black_num+(n-cur_node) > max_black_num)
	{
		cur_color[cur_node] = WHITE;
		dfs(cur_node+1, cur_black_num);
	}
}

int main()
{
	int m, i, j;
	scanf("%d", &m);
	while(m--)
	{
		scanf("%d%d", &n, &k);
		int v1, v2;
        for(i = 0; i <= 100; i++)
        {
            for(j = 0; j <= 100; j++)
                graph[i][j] = false;
            isolated[i] = true;
        }
		for(i = 0; i < k; i++)
		{
			scanf("%d%d", &v1, &v2);
			graph[v1][v2] = graph[v2][v1] = true;
			isolated[v1] = isolated[v2] = false;
		}
		
		max_black_num = 0;
		dfs(1, 0);
		
		printf("%d\n", max_black_num);
		int cnt = 0;
		for(i = 1; i <= n; i++)
			if(res_color[i] == BLACK)
			{
				if(++cnt < max_black_num)
					printf("%d ", i);
				else
					printf("%d\n", i);
			}
	}
	return 0;
}
