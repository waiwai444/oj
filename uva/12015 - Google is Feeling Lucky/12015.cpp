#include <cstdio>

char url[10][101];
int rel[10];

int main()
{
    int i, j, tc, m;
    std::scanf("%d", &tc);
    for(i = 1; i <= tc; ++i)
    {
        m = 0;
        for(j = 0; j < 10; ++j)
        {
            std::scanf("%s%d", url[j], &rel[j]);
            if(rel[j] > m)
                m = rel[j];
        }
        std::printf("Case #%d:\n", i);
        for(j = 0; j < 10; ++j)
            if(rel[j] == m)
                std::printf("%s\n", url[j]);
    }
    return 0;
}
