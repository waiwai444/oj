#include <cstdio>

int main()
{
    int i, tc, a, b;
    std::scanf("%d", &tc);
    for(i = 1; i <= tc; ++i)
    {
        std::scanf("%d%d", &a, &b);
        if((a&1) == 0)
            ++a;
        if((b&1) == 0)
            --b;
        if(a > b)
            std::printf("Case %d: 0\n", i);
        else
            std::printf("Case %d: %d\n", i, (a+b)*((b-a)/2+1)/2);
    }
    return 0;
}
