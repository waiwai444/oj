#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

int n;
std::vector<int> adj[15];
char vis[15];
char flag[32768];

inline bool is_removed(int v, std::pair<int, int> p)
{
    return p.first&(1<<v);
}

bool is_single_strand(int v, std::pair<int, int> p, int prev)
{
    int i, u, adj_cnt = 0;
    vis[v] = 1;
    for(i = 0; i < adj[v].size(); ++i)
    {
        u = adj[v][i];
        if(is_removed(u, p) || u == prev)
            continue;
        if(vis[u])
            return false;
        ++adj_cnt;
        if((prev < 0 && adj_cnt > 2) || (prev >= 0 && adj_cnt > 1))
            return false;
        if(!is_single_strand(u, p, v))
            return false;
    }
    return true;
}

bool check(std::pair<int, int> p)
{
    int comp_cnt = 0;
    std::memset(vis, 0, sizeof(vis));
    for(int i = 0; i < n; ++i)
    {
        if(!is_removed(i, p) && !vis[i])
        {
            ++comp_cnt;
            if(!is_single_strand(i, p, -1))
                return false;
        }
    }
    return p.second+1 >= comp_cnt;
}

int solve()
{
    std::pair<int, int> p;
    std::queue<std::pair<int, int> > q;
    std::memset(flag, 0, sizeof(flag));
    q.push(std::make_pair(0, 0));
    flag[0] = 1;
    while(!q.empty())
    {
        p = q.front(), q.pop();
        if(check(p))
            break;
        for(int i = 0; i < n; ++i)
        {
            if(!(p.first&(1<<i)))
            {
                int t = p.first|(1<<i);
                if(!flag[t])
                {
                    q.push(std::make_pair(t, p.second+1));
                    flag[t] = 1;
                }
            }
        }
    }
    return p.second;
}

int main()
{
    int i, j, k, tc = 0;
    while(std::scanf("%d", &n) != EOF)
    {
        if(n == 0)
            break;
        for(i = 0; i < n; ++i)
            adj[i].clear();
        while(1)
        {
            std::scanf("%d%d", &i, &j);
            if(i == -1 && j == -1)
                break;
            for(k = 0; k < adj[i-1].size(); ++k)
                if(adj[i-1][k] == j-1)
                    break;
            if(k == adj[i-1].size())
                adj[i-1].push_back(j-1), adj[j-1].push_back(i-1);
        }
        int ans = solve();
        std::printf("Set %d: Minimum links to open is %d\n", ++tc, ans);
    }
    return 0;
}
