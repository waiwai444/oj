#include <cstdio>
#include <algorithm>
#include <functional>

int n, d, r;
int mr[100], er[100];

int solve()
{
    int i, ans = 0;
    std::sort(&mr[0], &mr[n]);
    std::sort(&er[0], &er[n], std::greater<int>());
    for(i = 0; i < n; i++)
        if(mr[i]+er[i] > d)
            ans += mr[i]+er[i]-d;
    return ans*r;
}

int main()
{
    int i;
    while(scanf("%d%d%d", &n, &d, &r), n)
    {
        for(i = 0; i < n; i++)
            scanf("%d", &mr[i]);
        for(i = 0; i < n; i++)
            scanf("%d", &er[i]);
        printf("%d\n", solve());
    }
    return 0;
}

