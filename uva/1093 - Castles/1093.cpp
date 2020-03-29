#include <cstdio>
#include <climits>
#include <algorithm>
#include <utility>

#define MAXN 100

int n;
typedef std::pair<int, int> pii;
pii node[MAXN];
int adj[MAXN][MAXN], na[MAXN];
pii mem[MAXN][MAXN];

void add_edge(int u, int v)
{
    adj[u][na[u]++] = v;
    adj[v][na[v]++] = u;
}

bool cmp_pii(const pii &p1, const pii &p2)
{
    return p1.second > p2.second;
}

pii dfs(int cur, int par)
{
    int i, j;

    if(par >= 0 && mem[cur][par].first >= 0)
        return mem[cur][par];

    pii r = node[cur], p[MAXN];
    for(i = j = 0; i < na[cur]; i++)
        if(adj[cur][i] != par)
            p[j++] = dfs(adj[cur][i], cur);
    std::sort(&p[0], &p[j], cmp_pii);
    for(i = 0; i < j; i++)
    {
        r.first += r.second <= p[i].first ? p[i].first-r.second : 0;
        r.second = r.second <= p[i].first ? p[i].second : p[i].second+r.second-p[i].first;
    }

    if(par >= 0)
        mem[cur][par] = r;
    return r;
}

int solve()
{
    int i, j, ans = INT_MAX;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            mem[i][j].first = mem[i][j].second = -1;
    for(i = 0; i < n; i++)
    {
        pii p = dfs(i, -1);
        ans = std::min(p.first, ans);
    }
    return ans;
}

int main()
{
    int i, a, m, g, u, v, c = 0;
    while(scanf("%d", &n), n)
    {
        for(i = 0; i < n; i++)
        {
            scanf("%d%d%d", &a, &m, &g);
            node[i].first = a >= m+g ? a : m+g;
            node[i].second = node[i].first-m-g;
            na[i] = 0;
        }
        for(i = 1; i < n; i++)
        {
            scanf("%d%d", &u, &v);
            add_edge(u-1, v-1);
        }
        printf("Case %d: %d\n", ++c, solve());
    }
    return 0;
}

