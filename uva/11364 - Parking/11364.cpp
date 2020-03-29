#include <cstdio>

int main()
{
    int tc, n, max, min, x;
    std::scanf("%d", &tc);
    while(tc--)
    {
        std::scanf("%d%d", &n, &max);
        min = max;
        while(--n)
        {
            std::scanf("%d", &x);
            if(x < min)
                min = x;
            else if(x > max)
                max = x;
        }
        std::printf("%d\n", 2*(max-min));
    }
    return 0;
}
