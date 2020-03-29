#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define MAXN 5002

int st, av, b;
struct arc_t
{
    int u, v, cap, flow;
};
std::vector<arc_t> arc;
std::vector<int> adj[MAXN];
int sink;

#define NODE_IDX(x, y, out) (((x-1)*av+y-1)*2+(out?1:0)+1)

void add_arc_pair(int u, int v, int cap)
{
    arc_t a, a1;
    a.u = u, a.v = v, a.cap = cap, a.flow = 0;
    a1.u = v, a1.v = u, a1.cap = 0, a1.flow = 0;
    adj[u].push_back(arc.size());
    adj[v].push_back(arc.size()+1);
    arc.push_back(a);
    arc.push_back(a1);
}

void add_crossing(int x, int y)
{
    int ci = NODE_IDX(x, y, 0);
    int co = NODE_IDX(x, y, 1);
    add_arc_pair(ci, co, 1);
}

void connect_crossing(int x, int y, int x1, int y1)
{
    int ci, co, ni, no;
    ci = NODE_IDX(x, y, 0);
    co = NODE_IDX(x, y, 1);
    ni = NODE_IDX(x1, y1, 0);
    no = NODE_IDX(x1, y1, 1);
    add_arc_pair(co, ni, INF);
    add_arc_pair(no, ci, INF);
}

int dist[MAXN];
int first[MAXN];

bool bfs()
{
    int i, u;
    std::queue<int> q;
    memset(dist, -1, (sink+1)*sizeof(int));
    dist[0] = 0;
    q.push(0);
    while(!q.empty())
    {
        u = q.front(), q.pop();
        for(i = 0; i < adj[u].size(); i++)
        {
            arc_t &a = arc[adj[u][i]];
            if(dist[a.v] < 0 && a.cap > a.flow)
            {
                dist[a.v] = dist[u]+1;
                if(a.v == sink)
                    return true;
                q.push(a.v);
            }
        }
    }
    return false;
}

int flow(int u)
{
    if(u == sink)
        return 1;
    for(; first[u] < adj[u].size(); ++first[u])
    {
        int i = adj[u][first[u]];
        arc_t &a = arc[i];
        if(dist[a.v] == dist[u]+1 && a.cap > a.flow)
        {
            if(flow(a.v))
            {
                ++a.flow;
                --arc[i^1].flow;
                return 1;
            }
        }
    }
    return 0;
}

bool solve()
{
    // Dinic
    int f = 0;
    while(bfs())
    {
        memset(first, 0, (sink+1)*sizeof(int));
        while(flow(0)) // unit flow for this problem
            ++f;
    }
    return f == b;
}

int main()
{
    int i, j, x, y, tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d%d%d", &st, &av, &b);
        sink = NODE_IDX(st+1, 1, 0);
        arc.clear();
        for(i = 0; i <= sink; i++)
            adj[i].clear();
        for(i = 1; i <= st; i++)
        {
            for(j = 1; j <= av; j++)
            {
                add_crossing(i, j);
                if(i > 1)
                    connect_crossing(i, j, i-1, j);
                if(i < st)
                    connect_crossing(i, j, i+1, j);
                if(j > 1)
                    connect_crossing(i, j, i, j-1);
                if(j < av)
                    connect_crossing(i, j, i, j+1);
                if(i == 1 || i == st || j == 1 || j == av)
                    add_arc_pair(NODE_IDX(i, j, 1), sink, 1);
            }
        }
        for(i = 0; i < b; i++)
        {
            scanf("%d%d", &x, &y);
            add_arc_pair(0, NODE_IDX(x, y, 0), 1);
        }
        if(solve())
            printf("possible\n");
        else
            printf("not possible\n");
    }
    return 0;
}

