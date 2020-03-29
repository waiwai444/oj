#include <cstdio>
#include <cstring>

int cnt[26];
const char marg[] = "MARGIT";
const int marg_cnt[] = { 1, 3, 2, 1, 1, 1 };

int main()
{
    int i, tc, c, ans;
    char ind[601];
    const char *p;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%s", ind);
        memset(cnt, 0, sizeof(cnt));
        for(p = ind; *p; ++p)
            ++cnt[*p-'A'];
        ans = 1000;
        for(p = marg, i = 0; *p; ++p, ++i)
        {
            c = cnt[*p-'A']/marg_cnt[i];
            if(c < ans)
                ans = c;
        }
        printf("%d\n", ans);
    }
    return 0;
}

