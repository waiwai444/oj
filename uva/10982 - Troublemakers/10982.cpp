#include <cstdio>
#include <cstring>

int n, m;
bool pr[101][101];
int g1[100], g2[100];
int n1, n2;

void solve()
{
    int i, j, c1, c2;
    n1 = 1, n2 = 0;
    g1[0] = 1;
    for(i = 2; i <= n; i++)
    {
        c1 = c2 = 0;
        for(j = 0; j < n1; j++)
            if(pr[i][g1[j]])
                ++c1;
        for(j = 0; j < n2; j++)
            if(pr[i][g2[j]])
                ++c2;
        if(c1 <= c2)
            g1[n1++] = i;
        else
            g2[n2++] = i;
    }
}

void print_ans(int c)
{
    printf("Case #%d: %d\n", c, n2);
    if(n2 > 0)
    {
        printf("%d", g2[0]);
        for(int i = 1; i < n2; i++)
            printf(" %d", g2[i]);
    }
    printf("\n");
}

int main()
{
    int i, k, c, p, q;
    scanf("%d", &c);
    for(k = 1; k <= c; ++k)
    {
        scanf("%d%d", &n, &m);
        memset(pr, false, sizeof(pr));
        for(i = 0; i < m; i++)
        {
            scanf("%d%d", &p, &q);
            pr[p][q] = pr[q][p] = true;
        }
        solve();
        print_ans(k);
    }
    return 0;
}

