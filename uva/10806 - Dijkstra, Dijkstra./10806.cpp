#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f

int n;
struct edge_t
{
    int u, v;
    int cap, cost, flow;
    int rev;
};
std::vector<edge_t> edge[102];

int dist[102];
int prev[102];
int ine[102];
bool inq[102];

int solve()
{
    int i, u, ret = 0;
    std::queue<int> q;
    while(true)
    {
        // SPFA
        memset(dist, INF, sizeof(dist));
        dist[0] = 0;
        q.push(0);
        while(!q.empty())
        {
            u = q.front(); q.pop();
            inq[u] = false;
            for(i = 0; i < edge[u].size(); i++)
            {
                edge_t &e = edge[u][i];
                if(e.cap-e.flow > 0 && dist[e.v] > dist[u]+e.cost)
                {
                    dist[e.v] = dist[u]+e.cost;
                    prev[e.v] = u;
                    ine[e.v] = i;
                    if(!inq[e.v]) q.push(e.v), inq[e.v] = true;
                }
            }
        }
        //
        if(dist[n-1] == INF)
            break;
        for(u = n-1; u != 0; u = prev[u])
        {
            edge_t &e = edge[prev[u]][ine[u]];
            e.flow += 1;
            edge[u][e.rev].flow -= 1;
            ret += e.cost;
        }
    }
    return edge[0][0].flow == 2 ? ret : INF;
}

int main()
{
    int i, u, v, w, m, ans;
    edge_t e, er;
    e.flow = er.flow = 0;
    while(scanf("%d%d", &n, &m), n)
    {
        for(i = 0; i <= n+1; i++)
            edge[i].clear();
        for(i = 0; i < m; i++)
        {
            scanf("%d%d%d", &u, &v, &w);
            e.u = u, e.v = v, e.cap = 1, e.cost = w, e.rev = edge[v].size();
            er.u = v, er.v = u, er.cap = 0, er.cost = -w, er.rev = edge[u].size();
            edge[u].push_back(e);
            edge[v].push_back(er);
            e.u = v, e.v = u, e.cap = 1, e.cost = w, e.rev = edge[u].size();
            er.u = u, er.v = v, er.cap = 0, er.cost = -w, er.rev = edge[v].size();
            edge[v].push_back(e);
            edge[u].push_back(er);
        }
        n += 2;
        e.u = 0, e.v = 1, e.cap = 2, e.cost = 0, e.rev = edge[1].size();
        er.u = 1, er.v = 0, er.cap = 0, er.cost = 0, er.rev = edge[0].size();
        edge[0].push_back(e);
        edge[1].push_back(er);
        e.u = n-2, e.v = n-1, e.cap = 2, e.cost = 0, e.rev = edge[n-1].size();
        er.u = n-1, er.v = n-2, er.cap = 0, er.cost = 0, er.rev = edge[n-2].size();
        edge[n-2].push_back(e);
        edge[n-1].push_back(er);
        ans = solve();
        if(ans != INF)
            printf("%d\n", ans);
        else
            printf("Back to jail\n");
    }
    return 0;
}

