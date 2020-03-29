#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <functional>

#define INF 0x3f3f3f3f

int n, m, s, t;
int first[20000], next[100000];
struct edge_t
{
    int u, v, w;
} edge[100000];
bool vis[20000];
int dist[20000];

int dijkstra()
{
    int e;
    typedef std::pair<int, int> pii;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
    pii p;
    memset(vis, false, n*sizeof(bool));
    memset(dist, INF, n*sizeof(int));
    q.push(std::make_pair(0, s));
    dist[s] = 0;
    while(!q.empty())
    {
        p = q.top();
        q.pop();
        if(p.second == t)
            return p.first;
        if(vis[p.second])
            continue;
        vis[p.second] = true;
        for(e = first[p.second]; e != -1; e = next[e])
        {
            if(dist[edge[e].v] > p.first+edge[e].w)
            {
                dist[edge[e].v] = p.first+edge[e].w;
                q.push(std::make_pair(dist[edge[e].v], edge[e].v));
            }
        }
    }
    return -1;
}

int main()
{
    int i, j, k, u, v, w, tc, ans;
    scanf("%d", &tc);
    for(i = 1; i <= tc; i++)
    {
        scanf("%d%d%d%d", &n, &m, &s, &t);
        memset(first, -1, sizeof(first));
        for(j = 0, k = 0; j < m; j++, k += 2)
        {
            scanf("%d%d%d", &u, &v, &w);
            edge[k].u = u, edge[k].v = v, edge[k].w = w;
            edge[k+1].u = v, edge[k+1].v = u, edge[k+1].w = w;
            next[k] = first[u];
            first[u] = k;
            next[k+1] = first[v];
            first[v] = k+1;
        }
        ans = dijkstra();
        if(ans >= 0)
            printf("Case #%d: %d\n", i, ans);
        else
            printf("Case #%d: unreachable\n", i);
    }
    return 0;
}

