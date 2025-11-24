#include <stdio.h>

char str[1001];
int dp[1000];

void solve()
{
    int i, j, k;
    for(i = 0; str[i]; ++i)
    {
        dp[i] = i+1;
        for(j = i; j >= 0; --j)
        {
            for(k = j; k <= ((i+j)>>1); ++k)
                if(str[k] != str[i-(k-j)])
                    break;
            if(k > ((i+j)>>1))
            {
                if(j > 0 && dp[i] > dp[j-1]+1)
                    dp[i] = dp[j-1]+1;
                else if(j == 0)
                    dp[i] = 1;
            }
        }
    }
    printf("%d\n", dp[i-1]);
}

int main()
{
    int c;
    scanf("%d", &c);
    while(c--)
    {
        scanf("%s", str);
        solve();
    }
    return 0;
}
