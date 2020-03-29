#include <cstdio>
#include <cstring>
#include <cmath>
#include <climits>

int n;
int x[751], y[751];
int adj[751][751];
bool vis[751];
int w[751];

void init_graph()
{
    for(int i = 1; i < n; i++)
        for(int j = i+1; j <= n; j++)
            adj[i][j] = adj[j][i] = (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
}

double prim()
{
    int i, j, p, min;
    double sum = 0.0;
    memset(vis, false, sizeof(vis));
    vis[1] = true;
    for(i = 1; i <= n; i++)
        w[i] = adj[1][i];
    for(i = 1; i < n; i++)
    {
        min = INT_MAX;
        for(j = 2; j <= n; j++)
        {
            if(!vis[j] && w[j] < min)
            {
                p = j;
                min = w[j];
            }
        }
        vis[p] = true;
        sum += sqrt(w[p]);
        for(j = 2; j <= n; j++)
            if(!vis[j] && w[j] > adj[p][j])
                w[j] = adj[p][j];
    }
    return sum;
}

int main()
{
    int i, j, m, b1, b2;
    while(scanf("%d", &n) != EOF)
    {
        for(i = 1; i <= n; i++)
            scanf("%d%d", &x[i], &y[i]);
        init_graph();
        scanf("%d", &m);
        for(i = 0; i < m; i++)
        {
            scanf("%d%d", &b1, &b2);
            adj[b1][b2] = adj[b2][b1] = 0;
        }
        printf("%.2f\n", prim());
    }
    return 0;
}

