#include <cstdio>

int main()
{
    int tc, s, d, a, b;
    std::scanf("%d", &tc);
    while(tc--)
    {
        std::scanf("%d%d", &s, &d);
        if((s+d)&1)
            std::puts("impossible");
        else
        {
            a = (s+d)/2;
            b = s-a;
            if(b < 0)
                std::puts("impossible");
            else
                std::printf("%d %d\n", a, b);
        }
    }
    return 0;
}
