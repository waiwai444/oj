#include <cstdio>

int main()
{
    int i, tc, c, d;
    std::scanf("%d", &tc);
    for(i = 1; i <= tc; ++i)
    {
        std::scanf("%d%d", &c, &d);
        std::printf("Case %d: %.2lf\n", i, c+d*5/9.0);
    }
    return 0;
}
