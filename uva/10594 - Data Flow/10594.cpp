#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define MAXN 101
#define MAXE 20002

int n, m, d, k;
struct arc_t
{
    int u, v, cap, flow, cost;
};
arc_t arc[MAXE];
int first[MAXN], next[MAXE];

void add_arc(int idx, const arc_t &a)
{
    arc[idx] = a;
    next[idx] = first[a.u];
    first[a.u] = idx;
}

int dist[MAXN], inarc[MAXN];
bool inq[MAXN];

struct comparator
{
    bool operator()(int u, int v)
    {
        return dist[u] > dist[v];
    }
};

long long solve()
{
    int i, u, s = 0, f;
    long long c = 0;
    std::priority_queue<int, std::vector<int>, comparator> q;
    while(true)
    {
        memset(dist, INF, sizeof(dist));
        dist[0] = 0;
        q.push(0);
        while(!q.empty())
        {
            u = q.top(), q.pop();
            inq[u] = false;
            for(i = first[u]; i != -1; i = next[i])
            {
                arc_t &a = arc[i];
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
        if(dist[n] == INF)
            break;
        f = d-s >= k ? k : d-s;
        for(u = n; u != 0; u = arc[inarc[u]].u)
        {
            arc[inarc[u]].flow += f;
            arc[inarc[u]^1].flow -= f;
        }
        s += f;
        c += (long long)f*dist[n];
    }
    return s == d ? c : -1;
}

int main()
{
    int i, j, m, u, v, c;
    arc_t a;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        memset(first, -1, sizeof(first));
        j = 0;
        for(i = 0; i < m; i++)
        {
            scanf("%d%d%d", &u, &v, &c);
            a.u = u, a.v = v, a.cap = 0, a.flow = 0, a.cost = c;
            add_arc(j++, a);
            a.u = v, a.v = u, a.cost = -c;
            add_arc(j++, a);
            a.u = v, a.v = u, a.cost = c;
            add_arc(j++, a);
            a.u = u, a.v = v, a.cost = -c;
            add_arc(j++, a);
        }
        scanf("%d%d", &d, &k);
        for(i = 0; i < j; i += 2)
            arc[i].cap = k;
        a.u = 0, a.v = 1, a.cap = d, a.flow = 0, a.cost = 0;
        add_arc(j++, a);
        a.u = 1, a.v = 0, a.cap = 0;
        add_arc(j++, a);
        m = j;
        long long t = solve();
        if(t >= 0)
            printf("%lld\n", t);
        else
            printf("Impossible.\n");
    }
    return 0;
}

