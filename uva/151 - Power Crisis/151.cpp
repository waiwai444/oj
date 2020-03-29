#include <cstdio>

int n;
int dp[100];

int solve()
{
    int i, m = 1;
    while(1)
    {
        for(i = 2; i < n; ++i)
            dp[i] = (m+dp[i-1])%i;
        if(dp[n-1]+1 == 12)
            break;
        ++m;
    }
    return m;
}

int main()
{
    while(std::scanf("%d", &n) != EOF && n)
        std::printf("%d\n", solve());
    return 0;
}
