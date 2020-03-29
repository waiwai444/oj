#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

int n;
std::vector<int> adj[101];
std::queue<int> q;
bool vis[101];

int bfs(int s)
{
    int i, u, v, cnt = 0;
    memset(vis, false, sizeof(vis));
    q.push(s);
    while(!q.empty())
    {
        u = q.front(), q.pop();
        for(i = 0; i < adj[u].size(); i++)
        {
            v = adj[u][i];
            if(!vis[v])
            {
                q.push(v);
                vis[v] = true;
                ++cnt;
            }
        }
    }
    return cnt;
}

int main()
{
    int i, u, v, ns, s, c;
    while(scanf("%d", &n), n)
    {
        for(i = 1; i <= n; i++)
            adj[i].clear();
        while(scanf("%d", &u), u)
            while(scanf("%d", &v), v)
                adj[u].push_back(v);
        scanf("%d", &ns);
        while(ns--)
        {
            scanf("%d", &s);
            c = bfs(s);
            printf("%d", n-c);
            for(i = 1; i <= n; i++)
                if(!vis[i])
                    printf(" %d", i);
            printf("\n");
        }
    }
    return 0;
}

