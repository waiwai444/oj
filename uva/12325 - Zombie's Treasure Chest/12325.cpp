#include <cstdio>
#include <algorithm>
#include <utility>
#include <cmath>

int n, s1, v1, s2, v2;

long long solve()
{
    int i;
    long long ans = 0;

    if(s1 <= s2 && v1 >= v2)
        return (long long)v1*(n/s1);
    if(s1 >= s2 && v1 <= v2)
        return (long long)v2*(n/s2);

    if(s1 < s2)
        std::swap(s1, s2), std::swap(v1, v2);

    if(n/s1 >= std::sqrt(n))
    {
        for(i = 0; i <= s1; ++i)
            ans = std::max(ans, (long long)v1*((n-i*s2)/s1)+(long long)v2*i);
        for(i = 0; i <= s2; ++i)
            ans = std::max(ans, (long long)v1*i+(long long)v2*((n-i*s1)/s2));
    }
    else
    {
        for(i = 0; s1*i <= n; ++i)
            ans = std::max(ans, (long long)v1*i+(long long)v2*((n-i*s1)/s2));
    }

    return ans;
}

int main()
{
    int tc, c;
    std::scanf("%d", &tc);
    for(c = 1; c <= tc; ++c)
    {
        std::scanf("%d%d%d%d%d", &n, &s1, &v1, &s2, &v2);
        long long ans = solve();
        std::printf("Case #%d: %lld\n", c, ans); 
    }
    return 0;
}
