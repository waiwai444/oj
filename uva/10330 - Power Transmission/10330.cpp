#include <cstdio>
#include <cstring>
#include <queue>

#define INF 0x3f3f3f3f

int nn;
int cap[202][202], flow[202][202];
int prev[202], min[202];

int edmond_karp(int s, int t)
{
    int u, i, f, res = 0;
    memset(flow, 0, sizeof(flow));
    while(true)
    {
        std::queue<int> q;
        memset(min, 0, sizeof(min));
        q.push(s);
        min[s] = INF;
        while(!q.empty())
        {
            u = q.front(); q.pop();
            if(u == t) break;
            for(i = 0; i < nn; i++)
            {
                if(min[i]) continue;
                if((f = cap[u][i]-flow[u][i]) > 0)
                {
                    q.push(i);
                    prev[i] = u;
                    min[i] = min[u] < f ? min[u] : f;
                }
            }
        }
        if(u != t) break;
        for(i = t; i != 0; i = prev[i])
        {
            flow[prev[i]][i] += min[t];
            flow[i][prev[i]] -= min[t];
        }
        res += min[t];
    }
    return res;
}

int main()
{
    int n, m, i, j, c, k, b, d;
    while(scanf("%d", &n) != EOF)
    {
        nn = n*2+2;
        memset(cap, 0, sizeof(cap));
        for(i = 1; i <= n; i++)
        {
            scanf("%d", &k);
            cap[2*i-1][2*i] = k;
        }
        scanf("%d", &m);
        for(k = 0; k < m; k++)
        {
            scanf("%d%d%d", &i, &j, &c);
            cap[2*i][2*j-1] = c;
        }
        scanf("%d%d", &b, &d);
        for(i = 0; i < b; i++)
        {
            scanf("%d", &k);
            cap[0][2*k-1] = INF;
        }
        for(i = 0; i < d; i++)
        {
            scanf("%d", &k);
            cap[2*k][nn-1] = INF;
        }
        printf("%d\n", edmond_karp(0, nn-1));
    }
    return 0;
}

