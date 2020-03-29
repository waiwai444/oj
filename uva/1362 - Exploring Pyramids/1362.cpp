#include <stdio.h>
#include <string.h>

#define MAX 1000000000

char tape[301];
int dp[300][300];

int solve()
{
    int i, j, k, d, len;
    len = strlen(tape);
    if((len & 1) == 0 || tape[0] != tape[len-1])
        return 0;
    for(i = 0; i < len; i++)
        dp[i][i] = 1;
    for(d = 1; d < len; d++)
    {
        for(i = 0; (j = i+d) < len; i++)
        {
            dp[i][j] = 0;
            if(tape[i] == tape[j])
            {
                for(k = i+2; k < j; k++)
                {
                    if(tape[i] == tape[k])
                    {
                        dp[i][j] = (dp[i][j]+(long long)dp[i+1][k-1]*dp[k][j])%MAX;
                    }
                }
                dp[i][j] = ((long long)dp[i][j]+dp[i+1][j-1])%MAX;
            }
        }
    }
    return dp[0][len-1];
}

int main()
{
    while(scanf("%s", tape) != EOF)
    {
        printf("%d\n", solve());
    }
    return 0;
}
