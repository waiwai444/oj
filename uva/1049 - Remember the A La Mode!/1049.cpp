#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

#define MAXN 102
#define MAXA 5200
#define EPS 1e-9
#define INF 0x3f3f3f3f

int nn, na;
int np, ni;
struct arc_t
{
    int u, v;
    int cap, cost, flow;
} arcs[MAXA];
int first_arc[MAXN], next_arc[MAXA];

std::queue<int> q;
int dist[MAXN], inarc[MAXN];
bool inq[MAXN];

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

int mincost(int s, int t)
{
    int i, u, f, cost = 0;
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
                if(a.cap-a.flow > 0 && dist[a.v] > dist[u]+a.cost)
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
        u = t, f = INF;
        while(u != s)
        {
            arc_t &a = arcs[inarc[u]];
            f = std::min(f, a.cap-a.flow);
            u = a.u;
        }
        u = t;
        while(u != s)
        {
            arc_t &a = arcs[inarc[u]];
            a.flow += f;
            arcs[inarc[u]^1].flow -= f;
            u = a.u;
        }
        cost += dist[t]*f;
    }
    return cost;
}

int main()
{
    int i, j, c, tc = 0, min, max;
    double p;
    while(scanf("%d%d", &np, &ni), np)
    {
        nn = np+ni+2, na = 0;
        memset(first_arc, -1, sizeof(first_arc));
        for(i = 1; i <= np; i++)
        {
            scanf("%d", &c);
            add_arc_pair(0, i, c, 0);
        }
        for(i = 1; i <= ni; i++)
        {
            scanf("%d", &c);
            add_arc_pair(np+i, nn-1, c, 0);
        }
        for(i = 1; i <= np; i++)
        {
            for(j = 1; j <= ni; j++)
            {
                scanf("%lf", &p);
                if(p >= 0)
                    add_arc_pair(i, np+j, INF, (int)((p+EPS)*100));
            }
        }
        min = mincost(0, nn-1);
        for(i = 0; i < na; i++)
        {
            arc_t &a = arcs[i];
            a.flow = 0;
            if(a.u != 0 && a.u != 0 && a.u != nn-1 && a.v != nn-1)
                a.cost = -a.cost;
        }
        max = -mincost(0, nn-1);
        printf("Problem %d: %.2f to %.2f\n", ++tc, (double)min/100+EPS, (double)max/100+EPS);
    }
    return 0;
}

