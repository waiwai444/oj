#include <cstdio>
#include <cstring>

int s, n;
int x[100001];
char sh[100001];
int p[100001];

int solve()
{
    int i, j, ans = 0;

    memset(sh, 0, n+1);
    memset(p, 0, (s+1)*sizeof(int));

    for(i = 1, j = 1-s; i <= n; ++i)
    {
        if(i-j == s)
        {
            if(j <= 0 || sh[j] == 1)
                sh[i] = 1;
            ++j;
        }
        if(p[x[i]] > 0 && p[x[i]] >= j)
        {
            j = p[x[i]]+1;
        }
        p[x[i]] = i;
    }

    for(; j <= n; ++j)
        if(j <= 0 || sh[j])
            ++ans;

    return ans;
}

int main()
{
    int tc, i;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d%d", &s, &n);
        for(i = 1; i <= n; ++i)
            scanf("%d", &x[i]);
        printf("%d\n", solve());
    }
    return 0;
}