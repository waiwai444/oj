#include <algorithm>
#include <limits.h>
#include <stdio.h>

int N, K;
int ps[602];
int dp[301][601];

int main()
{
    int i, j, k, d, m, ans;
    while(scanf("%d%d", &N, &K) != EOF)
    {
        for(i = 1; i <= N+1; ++i)
        {
            scanf("%d", &d);
            ps[i] = d+ps[i-1];
        }
        if(K == 0)
            ans = ps[N+1];
        else
        {
            if(K > N)
                K = N;
            for(i = 1; i <= N-K+1; ++i)
                dp[1][i] = ps[i];
            for(i = 2; i <= K; ++i)
            {
                for(j = i; j <= N-K+i; ++j)
                {
                    dp[i][j] = INT_MAX;
                    for(k = j-1; k >= i-1; --k)
                    {
                        if(ps[j]-ps[k] >= dp[i][j])
                            break;
                        m = std::max(dp[i-1][k], ps[j]-ps[k]);
                        if(m < dp[i][j])
                            dp[i][j] = m;
                    }
                }
            }
            ans = INT_MAX;
            for(i = K; i <= N; ++i)
            {
                m = std::max(dp[K][i], ps[N+1]-ps[i]);
                if(ans > m)
                    ans = m;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
