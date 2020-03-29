#include <cstdio>
#include <cstring>
#include <queue>

#define INF 0x3f3f3f3f

int nn;
int cap[38][38];
int flow[38][38];
int prev[38];
int minf[38];

int sz_idx(const char *sz)
{
    switch(sz[0])
    {
    case 'X':
        switch(sz[1])
        {
        case 'X':   // XXL
            return 1;
        case 'L':   // XL
            return 2;
        case 'S':   // XS
            return 6;
        }
        break;
    case 'L':
        return 3;
    case 'M':
        return 4;
    case 'S':
        return 5;
    }
    return 0;
}

int edmonds_karp()
{
    int u, v, f, s = 0;
    std::queue<int> q;
    memset(flow, 0, sizeof(flow));
    while(true)
    {
        memset(minf, 0, sizeof(minf));
        minf[0] = INF;
        q.push(0);
        while(!q.empty())
        {
            u = q.front(); q.pop();
            for(v = 0; v < nn; v++)
            {
                if(!minf[v] && (f = cap[u][v]-flow[u][v]) > 0)
                {
                    prev[v] = u;
                    minf[v] = minf[u] < f ? minf[u] : f;
                    q.push(v);
                }
            }
        }
        if(minf[nn-1] == 0)
            break;
        f = minf[nn-1];
        for(u = nn-1; u != 0; u = prev[u])
        {
            flow[prev[u]][u] += f;
            flow[u][prev[u]] -= f;
        }
        s += f;
    }
    return s;
}

int main()
{
    int n, m, i, tc;
    char sz1[4], sz2[4];
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d%d", &n, &m);
        memset(cap, 0, sizeof(cap));
        nn = m+8;
        for(i = 0; i < m; i++)
        {
            scanf("%s%s", sz1, sz2);
            cap[sz_idx(sz1)][7+i] = cap[sz_idx(sz2)][7+i] = 1;
        }
        for(i = 1; i <= 6; i++)
            cap[0][i] = n/6;
        for(i = 0; i < m; i++)
            cap[7+i][7+m] = 1;
        if(edmonds_karp() == m)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

