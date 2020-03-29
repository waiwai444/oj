#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

int n;
double xc[1000], yc[1000], rad[1000];
std::vector<int> adj[1000];
bool tt[1000], tl[1000], tr[1000], tb[1000];
bool vis[1000];
double en, ex;

void init()
{
    int i, j;
    for(i = 0; i < n; ++i)
        adj[i].clear();
    for(i = 0; i < n; ++i)
    {
        for(j = i+1; j < n; ++j)
            if((xc[i]-xc[j])*(xc[i]-xc[j])+(yc[i]-yc[j])*(yc[i]-yc[j]) <= (rad[i]+rad[j])*(rad[i]+rad[j]))
                adj[i].push_back(j), adj[j].push_back(i);
        tt[i] = yc[i]+rad[i] >= 1000;
        tb[i] = yc[i]-rad[i] <= 0;
        tl[i] = xc[i]-rad[i] <= 0;
        tr[i] = xc[i]+rad[i] >= 1000;
        vis[i] = false;
    }
    en = ex = 1000;
}

bool dfs(int v)
{
    vis[v] = true;
    if(tb[v])
        return true;
    if(tl[v])
        en = std::min(yc[v]-std::sqrt(rad[v]*rad[v]-xc[v]*xc[v]), en);
    if(tr[v])
        ex = std::min(yc[v]-std::sqrt(rad[v]*rad[v]-(1000-xc[v])*(1000-xc[v])), ex);
    for(int i = 0; i < adj[v].size(); ++i)
        if(!vis[adj[v][i]] && dfs(adj[v][i]))
            return true;
    return false;
}

bool solve()
{
    int i;
    init();
    for(i = 0; i < n; ++i)
        if(!vis[i] && tt[i] && dfs(i))
            return false;
    return true;
}

int main()
{
    int i;
    while(std::scanf("%d", &n) != EOF)
    {
        for(i = 0; i < n; ++i)
            std::scanf("%lf%lf%lf", &xc[i], &yc[i], &rad[i]);
        if(solve())
            std::printf("0.00 %.2f 1000.00 %.2f\n", en, ex);
        else
            std::puts("IMPOSSIBLE");
    }
    return 0;
}

