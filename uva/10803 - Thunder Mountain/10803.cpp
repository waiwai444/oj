#include <cstdio>
#include <cmath>

#define INF (double)1e9

int n;
int x[100], y[100];
double dist[100][100];

double solve()
{
    int i, j, k;
    double d;
    for(i = 0; i < n; i++)
    {
        for(j = i+1; j < n; j++)
        {
            d = (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
            if(d <= 100)
                dist[i][j] = dist[j][i] = sqrt(d);
            else
                dist[i][j] = dist[j][i] = INF; 
        }
    }
    for(k = 0; k < n; k++)
    {
        for(i = 0; i < n; i++)
        {
            for(j = i+1; j < n; j++)
            {
                if(dist[i][j] > dist[i][k]+dist[k][j])
                    dist[i][j] = dist[j][i] = dist[i][k]+dist[k][j];
            }
        }
    }
    d = 0;
    for(i = 0; i < n; i++)
        for(j = i+1; j < n; j++)
            if(dist[i][j] > d)
                d = dist[i][j];
    return d;
}

int main()
{
    int tc, i, j;
    scanf("%d", &tc);
    for(i = 1; i <= tc; i++)
    {
        scanf("%d", &n);
        for(j = 0; j < n; j++)
            scanf("%d%d", &x[j], &y[j]);
        double ans = solve();
        printf("Case #%d:\n", i);
        if(ans < INF)
            printf("%.4f\n\n", ans);
        else
            printf("Send Kurdy\n\n");
    }
    return 0;
}

