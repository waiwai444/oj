#include <cstdio>
#include <cstring>

int val[128];

int main()
{
    int i, tc, k, m, c, v;
    long long sum;
    std::scanf("%d", &tc);
    while(tc--)
    {
        std::scanf("%d", &k);
        std::memset(val, 0, sizeof(val));
        for(i = 0; i < k; ++i)
        {
            while(std::getchar() != '\n');
            c = std::getchar();
            std::scanf("%d", &v);
            val[c] = v;
        }
        sum = 0;
        std::scanf("%d", &m);
        while(std::getchar() != '\n');
        for(i = 0; i < m; ++i)
        {
            while(1)
            {
                c = std::getchar();
                if(c == EOF || !c || c == '\n')
                    break;
                sum += val[c];
            }
        }
        std::printf("%lld.%02lld$\n", sum/100, sum%100);
    }
    return 0;
}
