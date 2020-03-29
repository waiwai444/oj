#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>

#define INF 0x3f3f3f3f
#define MAXN 15
#define MAXV (2*MAXN+2)
#define MAXA ((MAXN*MAXN+2*MAXN)*2)

int n;
struct pos_t
{
    int r, c;
};
pos_t init[MAXN];
pos_t dst[2*MAXN+2][MAXN];

int na;
struct arc_t
{
    int u, v;
    int cap, cost, flow;
} arcs[MAXA];
int first_arc[MAXV], next_arc[MAXA];

std::queue<int> q;
int dist[MAXV], inarc[MAXV];
bool inq[MAXV];

void init_dst()
{
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            dst[i][j].r = i+1, dst[i][j].c = j+1;
    for(; i < n*2; i++)
        for(j = 0; j < n; j++)
            dst[i][j].r = j+1, dst[i][j].c = i-n+1;
    for(j = 0; j < n; j++)
    {
        dst[n*2][j].r = j+1, dst[n*2][j].c = j+1;
        dst[n*2+1][j].r = j+1, dst[n*2+1][j].c = n-j;
    }
}

void add_arc_pair(int u, int v, int cap, int cost)
{
    arc_t a;
    a.u = u, a.v = v, a.cap = cap, a.cost = cost, a.flow = 0;
    next_arc[na] = first_arc[u], first_arc[u] = na;
    arcs[na++] = a;
    a.u = v, a.v = u, a.cap = 0, a.cost = -cost;
    next_arc[na] = first_arc[v], first_arc[v] = na;
    arcs[na++] = a;
}

void construct_network(int dst_id)
{
    int i, j, d;
    na = 0;
    memset(first_arc, -1, sizeof(first_arc));
    for(i = 1; i <= n; i++)
        add_arc_pair(0, i, 1, 0);
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j <= n; j++)
        {
            d = abs(init[i-1].r-dst[dst_id][j-1].r)+abs(init[i-1].c-dst[dst_id][j-1].c);
            add_arc_pair(i, n+j, 1, d);
        }
    }
    for(i = n+1; i <= 2*n; i++)
        add_arc_pair(i, 2*n+1, 1, 0);
}

int mincost(int s, int t)
{
    int i, u, c = 0;
    while(true)
    {
        memset(dist, INF, sizeof(dist));
        dist[s] = 0;
        q.push(s);
        while(!q.empty())
        {
            u = q.front(), q.pop();
            inq[u] = false;
            for(i = first_arc[u]; i != -1; i = next_arc[i])
            {
                arc_t &a = arcs[i];
                if(a.cap > a.flow && dist[a.v] > dist[u]+a.cost)
                {
                    dist[a.v] = dist[u]+a.cost;
                    inarc[a.v] = i;
                    if(!inq[a.v])
                    {
                        q.push(a.v);
                        inq[a.v] = true;
                    }
                }
            }
        }
        if(dist[t] == INF)
            break;
        for(u = t; u != s; u = arcs[inarc[u]].u)
        {
            ++arcs[inarc[u]].flow;
            --arcs[inarc[u]^1].flow;
        }
        c += dist[t];
    }
    return c;
}

int main()
{
    int i, tc = 0, ans, c;
    while(scanf("%d", &n), n)
    {
        for(i = 0; i < n; i++)
            scanf("%d%d", &init[i].r, &init[i].c);
        init_dst();
        ans = INF;
        for(i = 0; i < 2*n+2; i++)
        {
            construct_network(i);
            c = mincost(0, 2*n+1);
            if(c < ans)
                ans = c;
        }
        printf("Board %d: %d moves required.\n\n", ++tc, ans);
    }
    return 0;
}

