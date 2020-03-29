#include <cstdio>
#include <cstring>
#include <queue>

#define MAXN 50
#define MAX_NODE (MAXN*2)
#define MAX_ARC (MAXN+MAXN*(MAXN-1)*2)
#define INF 0x3f3f3f3f

int n, nn, na;
struct arc_t
{
    int u, v;
    bool c;
};
arc_t arcs[MAX_ARC];
int first_arc[MAX_NODE], next_arc[MAX_ARC];
bool adj[MAXN][MAXN];

void add_arc_pair(int u, int v)
{
    arc_t a;
    a.u = u, a.v = v, a.c = true;
    next_arc[na] = first_arc[u], first_arc[u] = na, arcs[na++] = a;
    a.u = v, a.v = u, a.c = false;
    next_arc[na] = first_arc[v], first_arc[v] = na, arcs[na++] = a;
}

int dist[MAX_NODE];
int next[MAX_NODE];
std::queue<int> q;

void init_cap()
{
    for(int i = 0; i < na; i += 2)
    {
        arcs[i].c = true;
        arcs[i+1].c = false;
    }
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
            if(a.c && dist[a.v] == INF)
            {
                dist[a.v] = dist[u]+1;
                q.push(a.v);
            }
        }
    }
    return dist[sink] < INF;
}

bool dfs(int cur, int sink)
{
    if(cur == sink)
        return true;
    int i;
    for(; (i = next[cur]) != -1; next[cur] = next_arc[i])
    {
        arc_t &a = arcs[i];
        if(a.c && dist[a.v] > dist[cur] && dfs(a.v, sink))
        {
            a.c = false;
            arcs[i^1].c = true;
            return true;
        }
    }
    return false;
}

int maxflow(int src, int sink)
{
    int i, f = 0;
    while(bfs(src, sink))
    {
        for(i = 0; i < nn; i++)
            next[i] = first_arc[i];
        while(dfs(src, sink))
            ++f;
    }
    return f;
}

int min_vcut()
{
    int from, to, ans = n;
    for(from = 0; from < n; from++)
    {
        for(to = from+1; to < n; to++)
        {
            if(adj[from][to]) continue;
            init_cap();
            int t = maxflow(2*from+1, 2*to);
            if(t < ans)
                ans = t;
        }
    }
    return ans;
}

int main()
{
    int i, m, r1, r2;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        memset(adj, false, sizeof(adj));
        memset(first_arc, -1, sizeof(first_arc));
        na = 0;
        nn = 2*n;
        for(i = 0; i < m; i++)
        {
            scanf(" (%d,%d)", &r1, &r2);
            if(adj[r1][r2]) continue;
            adj[r1][r2] = adj[r2][r1] = true;
            add_arc_pair(2*r1+1, 2*r2);
            add_arc_pair(2*r2+1, 2*r1);
        }
        for(i = 0; i < n; i++)
            add_arc_pair(2*i, 2*i+1);
        printf("%d\n", min_vcut());
    }
    return 0;
}

