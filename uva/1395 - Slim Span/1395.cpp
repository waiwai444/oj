#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 100
#define MAXM 4950
#define MAXW 10000

int n, m;
struct edge_t
{
    int a, b, w;
} edges[MAXM];
int repr[MAXN+1];

bool cmp_edge(const edge_t &e1, const edge_t &e2)
{
    return e1.w < e2.w;
}

int find(int x)
{
    return x == repr[x] ? x : repr[x] = find(repr[x]);
}

int maxw_in_st(int first_edge)
{
    int i, k = 0, ra, rb;
    for(i = 1; i <= n; i++)
        repr[i] = i;
    for(i = first_edge; i < m; i++)
    {
        ra = find(edges[i].a), rb = find(edges[i].b);
        if(ra == rb)
            continue;
        repr[rb] = ra;
        if(++k == n-1)
            break;
    }
    if(k == n-1)
        return edges[i].w;
    return -1;
}

int solve()
{
    int i, t, ans = -1;
    std::sort(edges, edges+m, cmp_edge);
    for(i = 0; i < m; i++)
    {
        if(i > 0 && edges[i].w == edges[i-1].w)
            continue;
        t = maxw_in_st(i);
        if(t > 0)
        {
            t -= edges[i].w;
            if(ans == -1 || t < ans)
                ans = t;
        }
    }
    return ans;
}

int main()
{
    int i, ans;
    while(scanf("%d%d", &n, &m), n)
    {
        for(i = 0; i < m; i++)
            scanf("%d%d%d", &edges[i].a, &edges[i].b, &edges[i].w);
        ans = solve();
        printf("%d\n", ans);
    }
    return 0;
}

