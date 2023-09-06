#include <stdio.h>

char s[101], t[101];

int solve()
{
    int c10 = 0, c01 = 0, cq0 = 0, cq1 = 0, ans;
    char *p = s, *q = t;

    for(; *p; ++p, ++q)
    {
        if(*p == '0' && *q == '1')
            ++c01;
        else if(*p == '1' && *q == '0')
            ++c10;
        else if(*p == '?')
        {
            if(*q == '0')
                ++cq0;
            else
                ++cq1;
        }
    }

    if(c10 <= c01)
        ans = c01+cq0+cq1;
    else if(c10 <= c01+cq1)
        ans = c10+cq1+cq0;
    else
        ans = -1;

    return ans;
}

int main()
{
    int i, c;
    scanf("%d", &c);
    for(i = 1; i <= c; ++i)
    {
        scanf("%s%s", s, t);
        printf("Case %d: %d\n", i, solve());
    }
    return 0;
}