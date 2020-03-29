#include <algorithm>
#include <cstdio>

int cnt[1000000];

int main()
{
    int i, j, n, ch, tc = 0;
    char cur;
    while((ch = std::getchar()))
    {
        if(ch == '\n')
            continue;
        if(ch == EOF)
            break;
        cur = ch;
        i = 0;
        cnt[i++] = n = 1;
        while((ch = std::getchar()) != '\n')
        {
            if(ch != cur)
            {
                cur = ch;
                n = 1;
            }
            else
                ++n;
            cnt[i++] = n;
        }
        std::scanf("%d", &n);
        std::printf("Case %d:\n", ++tc);
        while(n--)
        {
            std::scanf("%d%d", &i, &j);
            if(i > j)
                std::swap(i, j);
            if(cnt[j] > j-i)
                std::puts("Yes");
            else
                std::puts("No");
        }
    }
    return 0;
}
