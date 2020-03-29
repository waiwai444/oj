#include <cstdio>
#include <cstring>
#include <algorithm>

int ans[100];

void solve(int n)
{
    int i, r, l;
    memset(ans, 0, sizeof(ans));
    ans[0] = 2;
    r = n-2, l = 1;
    while(r > ans[l-1])
    {
        ans[l] = ans[l-1]+1;
        r -= ans[l];
        ++l;
    }
    i = std::max(l-r, 0);
    ans[l] = ans[i]+r;
    ans[i] = 0;
    ++l;

    i = 0;
    if(ans[i] == 0)
        ++i;
    printf("%d", ans[i++]);
    for(; i < l; i++)
        if(ans[i] > 0)
            printf(" %d", ans[i]);
    printf("\n");
}

int main()
{
    int tc, n;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d", &n);
        solve(n);
        if(tc)
            printf("\n");
    }
    return 0;
}

