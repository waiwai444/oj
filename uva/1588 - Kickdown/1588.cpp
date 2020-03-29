#include <cstdio>
#include <cstring>

char s[2][101];
int l[2];

int solve()
{
    int i, j, k, ans;
    l[0] = strlen(s[0]), l[1] = strlen(s[1]);
    k = l[0] >= l[1] ? 0 : 1;
    for(i = 0; i <= l[k]-l[1-k]; i++)
    {
        for(j = 0; j < l[1-k]; j++)
            if(s[k][i+j] == '2' && s[1-k][j] == '2')
                break;
        if(j == l[1-k])
            return l[k];
    }
    ans = l[0]+l[1];
    for(; i < l[k]; i++)
    {
        for(j = 0; i+j < l[k]; j++)
            if(s[k][i+j] == '2' &&  s[1-k][j] == '2')
                break;
        if(i+j == l[k])
        {
            ans = l[k]+l[1-k]-j;
            break;
        }
    }
    for(i = -1; i >= -l[1-k]+1; i--)
    {
        if(-i+l[k] >= ans)
            break;
        for(j = -i; j < l[1-k]; j++)
            if(s[k][i+j] == '2' && s[1-k][j] == '2')
                break;
        if(j == l[1-k])
        {
            ans = -i+l[k];
            break;
        }
    }
    return ans;
}

int main()
{
    while(scanf("%s%s", s[0], s[1]) != EOF)
        printf("%d\n", solve());
    return 0;
}

