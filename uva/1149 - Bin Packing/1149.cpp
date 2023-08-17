#include <algorithm>
#include <stdio.h>

int n, l, li[100001];

int solve()
{
    int i, j, ans = 0;
    
    std::sort(&li[0], &li[n]);

    for(i = 0, j = n-1; i <= j; --j)
    {
        if(li[i]+li[j] <= l)
            ++i;
        ++ans;
    }

    return ans;
}

int main()
{
    int c, i;
    scanf("%d", &c);
    while(c--)
    {
        scanf("%d%d", &n, &l);
        for(i = 0; i < n; ++i)
            scanf("%d", &li[i]);
        printf("%d\n", solve());
        if(c)
            putc('\n', stdout);
    }
    return 0;
}