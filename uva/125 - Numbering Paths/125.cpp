#include <cstdio>
#include <cstring>

int n;
bool adj[30][30];
int dp[30][30][2];
int sum[30][30];

void solve()
{
    int i, j, k, l, p = 0;
    memset(dp, 0, sizeof(dp));
    memset(sum, 0, sizeof(sum));
    for(i = 0; i < n; i++)
        dp[i][i][1-p] = 1;
    for(l = 1; l < n+n; l++)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                dp[i][j][p] = 0;
                for(k = 0; k < n; k++)
                {
                    if(dp[i][k][1-p] > 0 && adj[k][j])
                    {
                        dp[i][j][p] += dp[i][k][1-p];
                        if(l < n)
                            sum[i][j] += dp[i][k][1-p];
                        else
                            sum[i][j] = -1;
                    }
                }
            }
        }
        p = 1-p;
    }
}

int main()
{
    int i, j, m, c = 0, u, v;
    while(scanf("%d", &m) != EOF)
    {
        n = 0;
        memset(adj, false, sizeof(adj));
        for(i = 0; i < m; i++)
        {
            scanf("%d%d", &u, &v);
            if(u >= n) n = u+1;
            if(v >= n) n = v+1;
            adj[u][v] = true;
        }
        solve();
        printf("matrix for city %d\n", c++);
        for(i = 0; i < n; i++)
        {
            printf("%d", sum[i][0]);
            for(j = 1; j < n; j++)
                printf(" %d", sum[i][j]);
            printf("\n");
        }
    }
    return 0;
}

