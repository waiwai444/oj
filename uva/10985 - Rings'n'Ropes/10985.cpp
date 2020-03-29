#include <cstdio>
#include <cstring>

#define INF 0x3f3f3f3f

int n, m;
int adj[120][120];
int sp[120][120];
int cnt[120][120];
int cand1[120], cand2[120], nc1, nc2;

int solve()
{
    int i, j, k, l;
    memset(sp, INF, sizeof(sp));
    for(i = 0; i < n; i++)
    {
        sp[i][i] = 0;
        for(j = i+1; j < n; j++)
            if(adj[i][j])
                sp[i][j] = sp[j][i] = 1;
    }
    for(k = 0; k < n; k++)
        for(i = 0; i < n; i++)
            for(j = i+1; j < n; j++)
                if(sp[i][j] > sp[i][k]+sp[k][j])
                    sp[i][j] = sp[j][i] = sp[i][k]+sp[k][j];

    memset(cnt, 0, sizeof(cnt));
    for(i = 0; i < n; i++)
    {
        for(j = i+1; j < n; j++)
        {
            if(adj[i][j])
            {
                nc1 = nc2 = 0;
                for(k = 0; k < n; k++)
                {
                    if(sp[i][k] == sp[j][k]+1)
                        cand2[nc2++] = k;
                    else if(sp[j][k] == sp[i][k]+1)
                        cand1[nc1++] = k;
                }
                for(k = 0; k < nc1; k++)
                {
                    int u = cand1[k];
                    for(l = 0; l < nc2; l++)
                    {
                        int v = cand2[l];
                        if(sp[u][i]+sp[j][v]+1 == sp[u][v])
                        {
                            ++cnt[u][v];
                            ++cnt[v][u];
                        }
                    }
                }
            }
        }
    }

    int max = 0;
    for(i = 0; i < n; i++)
        for(j = i+1; j < n; j++)
            if(cnt[i][j] > max)
                max = cnt[i][j];
    return max;
}

int main()
{
    int i, c, u, v, tc;
    scanf("%d", &tc);
    for(c = 1; c <= tc; c++)
    {
        memset(adj, false, sizeof(adj));
        scanf("%d%d", &n, &m);
        for(i = 0; i < m; i++)
        {
            scanf("%d%d", &u, &v);
            adj[u][v] = adj[v][u] = true;
        }
        int ans = solve();
        printf("Case #%d: %d\n", c, ans);
    }
    return 0;
}

