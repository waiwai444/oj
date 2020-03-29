#include <stdio.h>
#include <string.h>

int node_num, edge_num;
struct node_link
{
    node_link *next;
} topo_order[100];
bool adj_mat[100][100];

bool dfs(int node, bool visited[], bool on_path[], node_link **plink)
{
    int i;
    visited[node] = true;
    on_path[node] = true;
    for(i = 0; i < node_num; i++)
    {
        if(adj_mat[node][i])
        {
            if(!visited[i])
            {
                if(dfs(i, visited, on_path, plink) == false)
                    return false;
            }
            else if(on_path[i])
                return false;
        }
    }
    topo_order[node].next = *plink;
    *plink = &topo_order[node];
    on_path[node] = false;
    return true;
}

node_link *toposort()
{
    int i;
    bool visited[100];
    bool on_path[100];
    node_link *link = 0;
    memset(visited, false, sizeof(visited));
    memset(on_path, false, sizeof(on_path));
    memset(topo_order, 0, sizeof(topo_order));
    for(i = 0; i < node_num; i++)
    {
        if(!visited[i])
        {
            if(dfs(i, visited, on_path, &link) == false)
                return 0;
        }
    }
    return link;
}

int main()
{
    int i, j, k;
    node_link *link;
    while(scanf("%d%d", &node_num, &edge_num), node_num)
    {
        memset(adj_mat, false, sizeof(adj_mat));
        for(k = 0; k < edge_num; k++)
        {
            scanf("%d%d", &i, &j);
            adj_mat[i-1][j-1] = true;
        }
        link = toposort();
        while(link != 0)
        {
            printf("%d", (int)(link-&topo_order[0])+1);
            link = link->next;
            if(link != 0)
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}