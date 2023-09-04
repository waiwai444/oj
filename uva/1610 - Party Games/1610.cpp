#include <stdio.h>
#include <string.h>
#include <algorithm>

int n;
char str[1000][31];
int idx[1000];

bool cmp(int i, int j)
{
    return strcmp(str[i], str[j]) < 0;
}

void solve()
{
    int i = n/2, j = 0;
    char ans[31];
    std::sort(&idx[0], &idx[n], cmp);
    char *p = str[idx[i-1]], *q = str[idx[i]];
    while(*p == *q)
    {
        ans[j++] = *p;
        ++p, ++q;
    }
    if (*p)
    {
        if(*(p+1) == 0)
            ans[j++] = *p;
        else if(*p+1 < *q || *(q+1))
            ans[j++] = *p+1;
        else
        {
            ans[j++] = *p++;
            while(*p)
            {
                if (*p < 'Z')
                {
                    ans[j++] = *(p+1) ? *p+1 : *p;
                    break;
                }
                ans[j++] = *p++;
            }
        }
    }
    ans[j] = 0;
    printf("%s\n", ans);
}

int main()
{
    int i;
    while(scanf("%d", &n) != EOF)
    {
        if(n == 0)
            break;
        for(i = 0; i < n; ++i)
        {
            scanf("%s", str[i]);
            idx[i] = i;
        }
        solve();
    }
    return 0;
}