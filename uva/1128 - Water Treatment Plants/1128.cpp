#include <cstdio>

#define BASE (1000000000) 
#define WIDTH (9)
#define MAXD (5)

using namespace std;

int dp[100][MAXD], ans[100][MAXD];

int print_ans(int n)
{
    int i = MAXD-1;
    while(ans[n][i] == 0)
        --i;
    printf("%d", ans[n][i--]);
    for(; i >= 0; i--)
        printf("%0*d", WIDTH, ans[n][i]);
    printf("\n");
    return 0;
}

void solve()
{
    int i, j, k, c;
    long long t;
    dp[0][0] = ans[0][0] = 1;
    for(i = 1; i < 100; i++)
    {
        dp[i][0] = 1;
        for(j = 0; j < i; j++)
        {
            c = 0;
            for(k = 0; k < MAXD; k++)
            {
                t = dp[i][k]+(long long)(i-j)*dp[j][k]+c;
                if(t >= BASE)
                {
                    c = t/BASE;
                    dp[i][k] = t%BASE;
                }
                else
                {
                    c = 0;
                    dp[i][k] = t;
                }
            }
        }
        for(j = 0; j <= i; j++)
        {
            c = 0;
            for(k = 0; k < MAXD; k++)
            {
                t = (long long)ans[i][k]+dp[j][k]+c;
                if(t >= BASE)
                {
                    c = t/BASE;
                    ans[i][k] = t%BASE;
                }
                else
                {
                    c = 0;
                    ans[i][k] = t;
                }
            }
        }
    }
}

int main()
{
    int nc;
    solve();
    while(scanf("%d", &nc) != EOF)
        nc ? print_ans(nc-1) : printf("0\n");
    return 0;
}

