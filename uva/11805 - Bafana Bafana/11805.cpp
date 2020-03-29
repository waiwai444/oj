#include <cstdio>

int main()
{
    int i, tc, n, k, p;
    std::scanf("%d", &tc);
    for(i = 1; i <= tc; ++i)
    {
        std::scanf("%d%d%d", &n, &k, &p);
        std::printf("Case %d: %d\n", i, ((k-1)+p)%n+1);
    }
    return 0;
}
