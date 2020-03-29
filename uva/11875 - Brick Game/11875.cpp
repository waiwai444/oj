#include <cstdio>

int main()
{
    int i, j, tc, n, a;
    std::scanf("%d", &tc);
    for(i = 1; i <= tc; ++i)
    {
        std::scanf("%d", &n);
        std::printf("Case %d: ", i);
        for(j = 0; j < n; ++j)
        {
            std::scanf("%d", &a);
            if(j == n/2)
                std::printf("%d\n", a);
        }
    }
    return 0;
}
