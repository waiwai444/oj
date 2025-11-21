#include <stdio.h>
#include <string.h>

int N, T, M1, M2;
int tt[55];
int dt[255], et[255];

int st[55];
int dp[205][55];

int solve()
{
    int i, j, t;
    for(i = 2; i <= N; ++i)
        st[i] = st[i-1]+tt[i-1];
    for(i = 1; i <= N; ++i)
        for(j = 0; j <= T; ++j)
            dp[j][i] = -1;
    dp[0][1] = 0;
    for(i = 1; i <= T; ++i)
    {
        for(j = 1; j <= N; ++j)
        {
            if(dp[i-1][j] >= 0)
                dp[i][j] = dp[i-1][j]+1;
            if(i-st[j] >= 0 && dt[i-st[j]] && j > 1)
            {
                t = dp[i-tt[j-1]][j-1];
                if(t >= 0 && (dp[i][j] < 0 || t < dp[i][j]))
                    dp[i][j] = t;
            }
            if(i-(st[N]-st[j]) >= 0 && et[i-(st[N]-st[j])] && j < N)
            {
                t = dp[i-tt[j]][j+1];
                if(t >= 0 && (dp[i][j] < 0 || t < dp[i][j]))
                    dp[i][j] = t;
            }
        }
    }
    return dp[T][N];
}

int main()
{
    int i, c = 1, t;
    while(scanf("%d%d", &N, &T) != EOF)
    {
        if(N == 0)
            break;
        memset(dt, 0, sizeof(dt));
        memset(et, 0, sizeof(et));
        for(i = 1; i < N; ++i)
            scanf("%d", &tt[i]);
        scanf("%d", &M1);
        for(i = 0; i < M1; ++i)
        {
            scanf("%d", &t);
            dt[t] = 1;
        }
        scanf("%d", &M2);
        for(i = 0; i < M2; ++i)
        {
            scanf("%d", &t);
            et[t] = 1;
        }
        printf("Case Number %d: ", c++);
        int ans = solve();
        if(ans == -1)
            puts("impossible");
        else
            printf("%d\n", ans);
    }
    return 0;
}
