#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

double n;
int p;
double a[10][31];
int b[10][31];
int p2[31];

void init()
{
    int i, j;
    double x;
    p2[0] = 1;
    for(i = 1; i <= 30; i++)
        p2[i] = p2[i-1]*2;
    for(i = 0; i <= 9; i++)
    {
        for(j = 1; j <= 30; j++)
        {
            x = log10(1-1.0L/p2[i+1])+(p2[j]-1)*log10(2.0L);
            a[i][j] = pow(10, x-(int)x);
            b[i][j] = (int)x;
        }
    }
}

void solve()
{
    int i, j;
    while(n < 1)
    {
        n *= 10;
        --p;
    }
    for(i = 0; i <= 9; i++)
    {
        for(j = 1; j <= 30; j++)
        {
            if(b[i][j] == p && fabs(a[i][j]-n) < 1e-6)
            {
                printf("%d %d\n", i, j);
                return;
            }
        }
    }
}

int main()
{
    char tmp[30];
    init();
    while(scanf("%s", tmp))
    {
        if(strcmp(tmp, "0e0") == 0)
            break;
        tmp[17] = 0;
        n = atof(tmp);
        p = atoi(&tmp[18]);
        solve();
    }
    return 0;
}

