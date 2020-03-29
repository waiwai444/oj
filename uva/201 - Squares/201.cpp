#include <cstdio>
#include <cstring>

int n;
struct adj_t
{
    bool r, b;
} adj[10][10];
struct con_t
{
    int r, b;
} con[10][10];

int ans[9];

void solve()
{
    int i, j, k, l;
    memset(ans, 0, sizeof(ans));
    for(i = 1; i <= n; i++)
    {
        for(k = l = 0, j = n; j >= 1; j--)
        {
            con[i][j].r = adj[i][j].r ? ++k : (k = 0);
            con[j][i].b = adj[j][i].b ? ++l : (l = 0);
        }
    }
    for(i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            for(k = 1; k <= con[i][j].r && k <= con[i][j].b; k++)
                if(con[i+k][j].r >= k && con[i][j+k].b >= k)
                    ++ans[k];
}

int main()
{
    int i, j, k, m, tc = 0;
    char d[2];
    bool na;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        memset(adj, false, sizeof(adj));
        for(k = 0; k < m; k++)
        {
            scanf("%s%d%d", d, &i, &j);
            if(d[0] == 'H')
                adj[i][j].r = true;
            else
                adj[j][i].b = true;
        }
        solve();
        if(tc)
            printf("\n**********************************\n\n");
        printf("Problem #%d\n\n", ++tc);
        na = true;
        for(i = 1; i <= 8; i++)
        {
            if(ans[i] > 0)
            {
                printf("%d square (s) of size %d\n", ans[i], i);
                na = false;
            }
        }
        if(na)
            printf("No completed squares can be found.\n");
    }
    return 0;
}

