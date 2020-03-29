#include <cstdio>

int main()
{
    int i, tc, l, w, h;
    std::scanf("%d", &tc);
    for(i = 1; i <= tc; ++i)
    {
        std::scanf("%d%d%d", &l, &w, &h);
        if(l > 20 || w > 20 || h > 20)
            std::printf("Case %d: bad\n", i);
        else
            std::printf("Case %d: good\n", i);
    }
    return 0;
}
