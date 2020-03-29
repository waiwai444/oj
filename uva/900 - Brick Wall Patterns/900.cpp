#include <cstdio>

long long dp[51];

int main()
{
    int i;
    dp[1] = 1, dp[2] = 2;
    for(i = 3; i <= 50; ++i)
        dp[i] = dp[i-1]+dp[i-2];
    while(std::scanf("%d", &i) && i)
        std::printf("%lld\n", dp[i]);
    return 0;
}
