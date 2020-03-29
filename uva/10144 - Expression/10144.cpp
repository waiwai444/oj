#include <cstdio>
#include <cstring>

char res[4000];
int f[101], e[101];
const char pre[] = "((A%d|B%d)|(((A%d|A%d)|(B%d|B%d))|";

int recur(int n, int p)
{
    f[n] = p;
    if(n == 1)
    {
        strcat(&res[p], "((A0|B0)|(A0|B0))");
        p += 17;
    }
    else
    {
        p += sprintf(&res[p], pre, n-1, n-1, n-1, n-1, n-1, n-1);
        p = recur(n-1, p);
        res[p] = res[p+1] = ')';
        p += 2;
    }
    e[n] = p;
    return p;
}

void solve()
{
    recur(100, 0);
}

int main()
{
    int n, tc;
    solve();
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d", &n);
        char t = res[e[n]];
        res[e[n]] = 0;
        printf("%s\n", &res[f[n]]);
        res[e[n]] = t;
        if(tc)
            printf("\n");
    }
    return 0;
}

