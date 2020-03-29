#include <cstdio>
#include <cstring>
#include <queue>

#define INF 0x3f3f3f3f

int n, m;
int first[1000], next[2000];
struct edge_t
{
    int u, v, w;
} edge[2000];

int dist[1000];
bool inp[1000];

bool dfs(int u)
{
    int e;
    inp[u] = true;
    for(e = first[u]; e != -1; e = next[e])
    {
        int v = edge[e].v, w = edge[e].w;
        if(dist[v] > dist[u]+w)
        {
            if(!inp[v])
            {
                dist[v] = dist[u]+w;
                if(dfs(v))
                    break;
            }
            else
                break;
        }
    }
    inp[u] = false;
    return e == -1 ? false : true;
}

int main()
{
    int i, c, u, v, w;
    scanf("%d", &c);
    while(c--)
    {
        scanf("%d%d", &n, &m);
        memset(first, -1, sizeof(first));
        for(i = 0; i < m; i++)
        {
            scanf("%d%d%d", &u, &v, &w);
            edge[i].u = u, edge[i].v = v, edge[i].w = w;
            next[i] = first[u];
            first[u] = i;
        }
        memset(dist, INF, sizeof(dist));
        dist[0] = 0;
        if(dfs(0))
            printf("possible\n");
        else
            printf("not possible\n");
    }
    return 0;
}

