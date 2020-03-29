#include <cstdio>

int main()
{
    int i, tc, n, w0, w, c1, c2;
    std::scanf("%d", &tc);
    for(i = 1; i <= tc; ++i)
    {
        std::scanf("%d%d", &n, &w0);
        c1 = c2 = 0;
        while(--n)
        {
            std::scanf("%d", &w);
            if(w > w0)
                ++c1;
            else if(w < w0)
                ++c2;
            w0 = w;
        }
        std::printf("Case %d: %d %d\n", i, c1, c2);
    }
    return 0;
}
