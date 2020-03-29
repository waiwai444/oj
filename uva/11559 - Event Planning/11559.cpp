#include <cstdio>

int main()
{
    int i, j, k, n, b, h, w, p, min;
    while(std::scanf("%d%d%d%d", &n, &b, &h, &w) != EOF)
    {
        min = b+1;
        for(i = 0; i < h; ++i)
        {
            std::scanf("%d", &p);
            for(j = 0; j < w; ++j)
            {
                std::scanf("%d", &k);
                if(k >= n)
                {
                    if(p*n < min)
                        min = p*n;
                }
            }
        }
        if(min <= b)
            std::printf("%d\n", min);
        else
            std::puts("stay home");
    }
    return 0;
}
