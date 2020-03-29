#include <cstdio>
#include <cstring>
#include <algorithm>

#define INF 0x3f3f3f3f

using namespace std;

int c, s, q;
int dp[101][101];

void solve()
{
    for(int k = 1; k <= c; k++)
    {
        for(int i = 1; i <= c; i++)
        {
            for(int j = i+1; j <= c; j++)
            {
                if(dp[i][j] > dp[i][k] && dp[i][j] > dp[k][j])
                {
                    dp[j][i] = dp[i][j] = max(dp[i][k], dp[k][j]);
                }
            }
        }
    }
}

int main()
{
    int i, c1, c2, d, tc = 0;
    while(scanf("%d%d%d", &c, &s, &q), c)
    {
        memset(dp, INF, sizeof(dp));
        for(i = 1; i <= c; i++)
            dp[i][i] = 0;
        for(i = 0; i < s; i++)
        {
            scanf("%d%d%d", &c1, &c2, &d);
            dp[c1][c2] = dp[c2][c1] = d;
        }
        solve();
        if(tc > 0)
            printf("\n");
        printf("Case #%d\n", ++tc);
        for(i = 0; i < q; i++)
        {
            scanf("%d%d", &c1, &c2);
            if(dp[c1][c2] < INF)
                printf("%d\n", dp[c1][c2]);
            else
                printf("no path\n");
        }
    }
    return 0;
}

