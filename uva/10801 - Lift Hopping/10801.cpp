#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <functional>

#define INF 0x3f3f3f3f

int n, k, tm[5];
bool fl[5][100];
int first[5];
int prev[5][100], next[5][100];
bool vis[5][100];
int dist[5][100];

int dijkstra()
{
    int i, e, f, g[2];
    typedef std::pair<int, int> pii;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
    pii p;
    memset(vis, false, sizeof(vis));
    memset(dist, INF, sizeof(dist));
    for(i = 0; i < n; i++)
    {
        if(first[i] != 0)
            continue;
        dist[i][0] = 0;
        q.push(std::make_pair(0, i<<8));
    }
    while(!q.empty())
    {
        p = q.top();
        q.pop();
        e = p.second>>8;
        f = p.second&0xff;
        if(f == k)
            return p.first;
        if(vis[e][f])
            continue;
        vis[e][f] = true;
        if(f > 0)
        {
            for(i = 0; i < n; i++)
            {
                if(i == e || !fl[i][f])
                    continue;
                if(dist[i][f] > p.first+60)
                {
                    dist[i][f] = p.first+60;
                    q.push(std::make_pair(dist[i][f], (i<<8)+f));
                }
            }
        }
        g[0] = next[e][f], g[1] = prev[e][f];
        for(i = 0; i < 2; i++)
        {
            if(g[i] < 0)
                continue;
            int d = p.first+abs(g[i]-f)*tm[e];
            if(dist[e][g[i]] > d)
            {
                dist[e][g[i]] = d;
                q.push(std::make_pair(d, (e<<8)+g[i]));
            }
        }
    }
    return -1;
}

int main()
{
    int i, p, q, ans;
    char buf[300], *ptr;
    while(scanf("%d%d", &n, &k) != EOF)
    {
        for(i = 0; i < n; i++)
            scanf("%d", &tm[i]);
        fgets(buf, sizeof(buf), stdin);
        memset(fl, false, sizeof(fl));
        for(i = 0; i < n; i++)
        {
            fgets(buf, sizeof(buf), stdin);
            first[i] = p = atoi(strtok(buf, " "));
            fl[i][p] = true;
            prev[i][p] = -1;
            while((ptr = strtok(NULL, " ")))
            {
                q = atoi(ptr);
                fl[i][q] = true;
                prev[i][q] = p;
                next[i][p] = q;
                p = q;
            }
            next[i][p] = -1;
        }
        ans = dijkstra();
        if(ans >= 0)
            printf("%d\n", ans);
        else
            printf("IMPOSSIBLE\n");
    }
    return 0;
}

