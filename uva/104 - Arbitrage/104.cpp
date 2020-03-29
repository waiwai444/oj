#include <cstdio>

int n;
double rate[20][20];
double dp[20][20][20];
int prev[20][20][20];
const double THRESHOLD = 1.01L;
int ans_i, ans_l;

bool solve()
{
    int i, j, k, l;
    double t;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            dp[i][j][0] = rate[i][j];
    for(l = 1; l < n; l++)
    {
        for(i = 0; i < n; i++)
        {
            for(j = 0; j < n; j++)
            {
                dp[i][j][l] = dp[i][0][l-1]*rate[0][j];
                prev[i][j][l] = 0;
                for(k = 1; k < n; k++)
                {
                    t = dp[i][k][l-1]*rate[k][j];
                    if(t > dp[i][j][l])
                    {
                        dp[i][j][l] = t;
                        prev[i][j][l] = k;
                    }
                }
                if(i == j && dp[i][i][l] > THRESHOLD)
                {
                    ans_i = i, ans_l = l;
                    return true;
                }
            }
        }
    }
    return false;
}

void print_ans()
{
    int i, k = ans_i, path[20];
    for(i = ans_l; i > 0; i--)
    {
        k = prev[ans_i][k][i];
        path[i] = k;
    }
    printf("%d", ans_i+1);
    for(i = 1; i <= ans_l; i++)
        printf(" %d", path[i]+1);
    printf(" %d\n", ans_i+1);
}

int main()
{
    int i, j;
    while(scanf("%d", &n) != EOF)
    {
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                if(i == j) rate[i][i] = 1.0;
                else scanf("%lf", &rate[i][j]);
        if(solve())
            print_ans();
        else
            printf("no arbitrage sequence exists\n");
    }
    return 0;
}

