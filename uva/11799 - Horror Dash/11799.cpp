#include <cstdio>

int main()
{
    int i, tc, n, v, ans;
    std::scanf("%d", &tc);
    for(i = 1; i <= tc; ++i)
    {
        std::scanf("%d", &n);
        ans = 0;
        while(n--)
        {
            std::scanf("%d", &v);
            if(v > ans)
                ans = v;
        }
        std::printf("Case %d: %d\n", i, ans);
    }
    return 0;
}
