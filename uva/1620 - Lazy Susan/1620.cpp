#include <stdio.h>

int n;
int num[501];

void solve()
{
    int i, j, invc = 0;
    bool ans = true;
    if(n & 1)
    {
        for(i = 0; i < n; ++i)
        {
            for(j = i + 1; j < n; ++j)
            {
                if(num[j] < num[i])
                    ++invc;
            }
        }
        if(invc & 1)
            ans = false;
    }
    if(ans)
        puts("possible");
    else
        puts("impossible");
}

int main()
{
    int i, tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d", &n);
        for(i = 0; i < n; ++i)
        {
            scanf("%d", &num[i]);
        }
        solve();
    }
    return 0;
}
