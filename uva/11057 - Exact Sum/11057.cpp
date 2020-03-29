#include <cstdio>
#include <algorithm>

int n, bk[10000], m;

int main()
{
    int i, j, x, y;
    while(std::scanf("%d", &n) != EOF)
    {
        for(i = 0; i < n; ++i)
            std::scanf("%d", &bk[i]);
        std::scanf("%d", &m);
        std::sort(&bk[0], &bk[n]);
        i = 0, j = n-1;
        while(i < j)
        {
            if(bk[i]+bk[j] < m)
                ++i;
            else if(bk[i]+bk[j] > m)
                --j;
            else
            {
                x = bk[i], y = bk[j];
                ++i, --j;
            }
        }
        std::printf("Peter should buy books whose prices are %d and %d.\n\n", x, y);
    }
    return 0;
}
