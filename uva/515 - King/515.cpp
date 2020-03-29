#include <cstdio>
#include <cstring>

int n, m;
int u[100], v[100], w[100];
int dist[101];

bool solve()
{
    int i, j;
    memset(dist, 0, sizeof(dist));
    for(i = 1; i <= n; i++)
        for(j = 0; j < m; j++)
            if(dist[v[j]] > dist[u[j]]+w[j])
                dist[v[j]] = dist[u[j]]+w[j];
    for(j = 0; j < m; j++)
        if(dist[v[j]] > dist[u[j]]+w[j])
            return false;
    return true;
}

int main()
{
    int i, si, ni, ki;
    char oi[3];
    while(scanf("%d%d", &n, &m), n)
    {
        for(i = 0; i < m; i++)
        {
            scanf("%d%d%2s%d", &si, &ni, oi, &ki);
            if(oi[0] == 'l')
                u[i] = si-1, v[i] = si+ni, w[i] = ki-1;
            else
                u[i] = si+ni, v[i] = si-1, w[i] = -ki-1;
        }
        if(solve())
            printf("lamentable kingdom\n");
        else
            printf("successful conspiracy\n");
    }
    return 0;
}

