#include <algorithm>
#include <stdio.h>

int n, t;
int len[50];
int dp[50][50*180+700];
int maxlen[50][50*180+700];

void solve()
{
    int i, j;
    for(j = 1; len[0] > j && j < t; ++j)
        dp[0][j] = maxlen[0][j] = 0;
    for(; j < t; ++j)
    {
        dp[0][j] = 1;
        maxlen[0][j] = len[0];
    }
    for(i = 1; i < n; ++i)
    {
        for(j = 1; j < t; ++j)
        {
            if(j >= len[i])
            {
                int c1 = dp[i-1][j], c2 = dp[i-1][j-len[i]]+1;
                dp[i][j] = std::max(c1, c2);
                if(c1 > c2)
                    maxlen[i][j] = maxlen[i-1][j];
                else if(c1 < c2)
                    maxlen[i][j] = maxlen[i-1][j-len[i]]+len[i];
                else
                    maxlen[i][j] = std::max(maxlen[i-1][j], maxlen[i-1][j-len[i]]+len[i]);
            }
            else
            {
                dp[i][j] = dp[i-1][j];
                maxlen[i][j] = maxlen[i-1][j];
            }
        }
    }
    printf("%d %d\n", dp[n-1][t-1]+1, maxlen[n-1][t-1]+678);
}

int main()
{
    int i, c, T;
    scanf("%d", &T);
    for(c = 1; c <= T; ++c)
    {
        scanf("%d%d", &n, &t);
        for(i = 0; i < n; ++i)
            scanf("%d", &len[i]);
        printf("Case %d: ", c);
        solve();
    }
    return 0;
}
