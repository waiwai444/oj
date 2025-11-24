#include <algorithm>
#include <stdio.h>

int n;
struct category_t
{
    int V, K, C, L;
} cat[1000];

int dp[1000];
int min[1000];

bool cmp_cat(const category_t &c1, const category_t &c2)
{
    return c1.V < c2.V;
}

void solve()
{
    int i, j;
    std::sort(cat, cat+n, cmp_cat);
    dp[n-1] = cat[n-1].K+cat[n-1].C*cat[n-1].L;
    min[n-1] = dp[n-1];
    for(i = n-2; i >= 0; --i)
    {
        dp[i] = min[i+1]+cat[i].K+cat[i].C*cat[i].L;
        min[i] = dp[i];
        for(j = i+1; j < n; ++j)
        {
            dp[j] += cat[j].C*cat[i].L;
            if(dp[j] < min[i])
                min[i] = dp[j];
        }
    }
    printf("%d\n", min[0]);
}

int main()
{
    int i;
    while(scanf("%d", &n))
    {
        if(n == 0)
            break;
        for(i = 0; i < n; ++i)
            scanf("%d%d%d%d", &cat[i].V, &cat[i].K, &cat[i].C, &cat[i].L);
        solve();
    }
    return 0;
}
