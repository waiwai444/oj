#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 0x3f3f3f3f
#define MAXN 100
#define MAXNODE (2*MAXN+1)

int n, nn;
double md;
double x[MAXN+1], y[MAXN+1];
int np[MAXN+1], mj[MAXN+1], sum_np;

struct arc_t
{
    int u, v, cap, flow;
};
std::vector<arc_t> arcs;
std::vector<int> adj[MAXNODE];
std::vector<int> ans;

void add_arc_pair(int u, int v, int c)
{
    arc_t a;
    a.u = u, a.v = v, a.cap = c, a.flow = 0;
    adj[u].push_back(arcs.size());
    arcs.push_back(a);
    a.u = v, a.v = u, a.cap = 0;
    adj[v].push_back(arcs.size());
    arcs.push_back(a);
}

void create_network()
{
    int i, j;
    arcs.clear();
    for(i = 0; i < MAXNODE; i++)
        adj[i].clear();
    nn = 2*n+1;
    for(i = 1; i <= n; i++)
    {
        add_arc_pair(2*i-1, 2*i, mj[i]);
        if(np[i] > 0)
            add_arc_pair(0, 2*i-1, np[i]);
    }
    for(i = 1; i < n; i++)
    {
        for(j = i+1; j <= n; j++)
        {
            if((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]) <= md*md)
            {
                add_arc_pair(2*i, 2*j-1, INF);
                add_arc_pair(2*j, 2*i-1, INF);
            }
        }
    }
}

std::queue<int> q;
int dist[MAXNODE];
int next[MAXNODE];

bool bfs(int src, int sink)
{
    int i, u;
    memset(dist, INF, sizeof(dist));
    dist[src] = 0;
    q.push(src);
    while(!q.empty())
    {
        u = q.front(), q.pop();
        for(i = 0; i < adj[u].size(); i++)
        {
            arc_t &a = arcs[adj[u][i]];
            if(a.cap > a.flow && dist[a.v] == INF)
            {
                dist[a.v] = dist[u]+1;
                q.push(a.v);
            }
        }
    }
    return dist[sink] < INF;
}

int send_flow(int cur, int sink, int flow)
{
    if(cur == sink)
        return flow;
    for(; next[cur] != adj[cur].size(); ++next[cur])
    {
        arc_t &a = arcs[adj[cur][next[cur]]];
        if(a.cap > a.flow && dist[a.v] > dist[cur])
        {
            int f = std::min(flow, a.cap-a.flow);
            int r = send_flow(a.v, sink, f);
            if(r > 0)
            {
                a.flow += r;
                arcs[adj[cur][next[cur]]^1].flow -= r;
                return r;
            }
        }
    }
    return 0;
}

int maxflow(int src, int sink)
{
    int tot = 0, f;
    while(bfs(src, sink))
    {
        memset(next, 0, nn*sizeof(int));
        while(f = send_flow(src, sink, INF))
            tot += f;
    }
    return tot;
}

void solve()
{
    int i, j, f;
    ans.clear();
    for(i = 1; i <= n; i++)
    {
        for(j = 0; j < arcs.size(); j++)
            arcs[j].flow = 0;
        if(maxflow(0, 2*i-1) == sum_np)
            ans.push_back(i-1);
    }
}

int main()
{
    int i, tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d%lf", &n, &md);
        sum_np = 0;
        for(i = 1; i <= n; i++)
        {
            scanf("%lf%lf%d%d", &x[i], &y[i], &np[i], &mj[i]); 
            sum_np += np[i];
        }
        create_network();
        solve();
        if(ans.size() == 0)
            printf("-1\n");
        else
        {
            for(i = 0; i < ans.size()-1; i++)
                printf("%d ", ans[i]);
            printf("%d\n", ans[ans.size()-1]);
        }
    }
    return 0;
}

