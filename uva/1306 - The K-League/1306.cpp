#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

#define INF 0x3f3f3f3f
#define MAXN 25
#define MAXPAIR (25*24/2)
#define MAXNODE (MAXPAIR+MAXN+2)
#define MAXARC ((MAXPAIR+MAXPAIR*2+MAXN)*2)

int n, nn, na, np;
int cwin[MAXN];
int rem[MAXN][MAXN];
struct arc_t
{
    int u, v, cap, flow;
} arcs[MAXARC];
int first_arc[MAXNODE], next_arc[MAXARC];

int dist[MAXNODE], cur_arc[MAXNODE];
std::queue<int> q;
int ans[MAXN], nans;

void add_arc_pair(int u, int v, int cap)
{
    arc_t a;
    a.u = u, a.v = v, a.cap = cap, a.flow = 0;
    next_arc[na] = first_arc[u], first_arc[u] = na;
    arcs[na++] = a;
    a.u = v, a.v = u, a.cap = 0;
    next_arc[na] = first_arc[v], first_arc[v] = na;
    arcs[na++] = a;
}

void create_network(int cur_team, int win_lim)
{
    int i, j, k;
    na = 0;
    memset(first_arc, -1, sizeof(first_arc));
    for(i = 0, k = 1; i < n; i++)
    {
        for(j = i+1; j < n; j++)
        {
            if(i != cur_team && j != cur_team)
            {
                add_arc_pair(0, k, rem[i][j]);
                add_arc_pair(k, np+i+1, rem[i][j]);
                add_arc_pair(k, np+j+1, rem[i][j]);
            }
            ++k;
        }
    }
    for(i = 0; i < n; i++)
        if(i != cur_team && win_lim > cwin[i])
            add_arc_pair(np+i+1, np+n+1, win_lim-cwin[i]);
}

bool bfs(int src, int sink)
{
    int i, u;
    memset(dist, INF, sizeof(dist));
    dist[src] = 0;
    q.push(src);
    while(!q.empty())
    {
        u = q.front(), q.pop();
        for(i = first_arc[u]; i != -1; i = next_arc[i])
        {
            arc_t &a = arcs[i];
            if(a.cap > a.flow && dist[a.v] == INF)
            {
                dist[a.v] = dist[u]+1;
                q.push(a.v);
            }
        }
    }
    return dist[sink] != INF;
}

int send_flow(int cur, int sink, int flow)
{
    if(cur == sink)
        return flow;
    for(; cur_arc[cur] != -1; cur_arc[cur] = next_arc[cur_arc[cur]])
    {
        arc_t &a = arcs[cur_arc[cur]];
        if(a.cap > a.flow && dist[a.v] > dist[cur])
        {
            int f = std::min(flow, a.cap-a.flow);
            if((f = send_flow(a.v, sink, f)))
            {
                a.flow += f;
                arcs[cur_arc[cur]^1].flow -= f;
                return f;
            }
        }
    }
    return 0;
}

int maxflow(int src, int sink)
{
    int i, f, tot = 0;
    while(bfs(src, sink))
    {
        for(i = 0; i < nn; i++)
            cur_arc[i] = first_arc[i];
        while((f = send_flow(src, sink, INF)))
            tot += f;
    }
    return tot;
}

void solve()
{
    int i, j, tot, f;
    int all_match = 0;
    nans = 0;
    np = n*(n-1)/2;
    nn = np+n+2;
    for(i = 0; i < n; i++)
        for(j = i+1; j < n; j++)
            all_match += rem[i][j];
    for(i = 0; i < n; i++)
    {
        tot = cwin[i];
        for(j = 0; j < n; j++)
            tot += rem[i][j];
        for(j = 0; j < n; j++)
            if(tot < cwin[j])
                break;
        if(j < n) continue;
        create_network(i, tot);
        f = maxflow(0, np+n+1);
        if(f == all_match-(tot-cwin[i]))
            ans[nans++] = i+1;
    }
}

int main()
{
    int i, j, tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d%*d", &cwin[i]);
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                scanf("%d", &rem[i][j]);
        solve();
        for(i = 0; i < nans-1; i++)
            printf("%d ", ans[i]);
        printf("%d\n", ans[nans-1]);
    }
    return 0;
}

