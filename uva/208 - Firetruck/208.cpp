#include <stdio.h>
#include <string.h>

int node_num;
bool graph[22][22];
int target;

bool visited[22];
int path_num, cur_path[22];

bool dfs_check_reachable(int cur_node)
{
    if(cur_node == target)
        return true;
    visited[cur_node] = true;
    for(int i = 1; i <= node_num; i++)
    {
        if((graph[cur_node][i] || graph[i][cur_node]) && !visited[i])
        {
            if(dfs_check_reachable(i))
                return true;
        }
    }
    return false;
}

void output(int depth)
{
    for(int i = 0; i < depth; i++)
        printf("%d ", cur_path[i]);
    printf("%d\n", target);
}

void dfs_enum_path(int cur_node, int depth)
{
    visited[cur_node] = true;
    cur_path[depth] = cur_node;
    
    if(cur_node == target)
    {
        path_num++;
        output(depth);
    }
    else
    {
        for(int i = 1; i <= node_num; i++)
        {
            if((graph[cur_node][i] || graph[i][cur_node]) && !visited[i])
            {
                dfs_enum_path(i, depth+1);
            }
        }
    }
    
    visited[cur_node] = false;
}

int main()
{
    int v1, v2, tc(0);
    while(scanf("%d", &target) != EOF)
    {
        memset(graph, false, sizeof(graph));
        node_num = target;
        while(scanf("%d%d", &v1, &v2))
        {
            if(v1 == 0 && v2 == 0)
                break;
            graph[v1][v2] = graph[v2][v1] = true;
            if(v1 > node_num)
                node_num = v1;
            if(v2 > node_num)
                node_num = v2;
        }
        
        memset(visited, false, sizeof(visited));
        bool reachable = dfs_check_reachable(1);
        
        memset(visited, false, sizeof(visited));
        path_num = 0;
        printf("CASE %d:\n", ++tc);
        if(reachable)
            dfs_enum_path(1, 0);
        printf("There are %d routes from the firestation to streetcorner %d.\n", path_num, target);
    }
    return 0;
}