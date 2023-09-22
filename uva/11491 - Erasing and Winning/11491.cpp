#include <stdio.h>

int n, d;
char num[100001];
char ans[100001];

void solve()
{
    int i, j;

    ans[0] = num[0];
    for(i = j = 1; i < n; ++i, ++j)
    {
        while(j > 0 && num[i] > ans[j-1] && d+j >= i+1)
            --j;
        ans[j] = num[i];
    }
    ans[n-d] = 0;
}

int main()
{
    while(1)
    {
        scanf("%d%d", &n, &d);
        if(n == 0 && d == 0)
            break;
        scanf("%s", num);
        solve();
        printf("%s\n", ans);
    }
    return 0;
}