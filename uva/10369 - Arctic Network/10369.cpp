#include <cstdio>
#include <cstring>
#include <cmath>
#include <climits>
#include <algorithm>

int s, p;
int x[500], y[500];
int adj[500][500];
bool vis[500];
int pt_w[500];
int edge_len[500];

void init_graph()
{
    for(int i = 0; i < p; i++)
        for(int j = i+1; j < p; j++)
            adj[i][j] = adj[j][i] = (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
}

double solve()
{
    int i, j, min, pos;
    memset(vis, false, sizeof(vis));
    vis[0] = true;
    pt_w[0] = 0;
    for(i = 1; i < p; i++)
        pt_w[i] = adj[0][i];
    for(i = 1; i < p; i++)
    {
        min = INT_MAX;
        for(j = 1; j < p; j++)
        {
            if(!vis[j] && pt_w[j] < min)
            {
                min = pt_w[j];
                pos = j;
            }
        }
        vis[pos] = true;
        edge_len[i-1] = min;
        for(j = 1; j < p; j++)
        {
            if(!vis[j] && pt_w[j] > adj[pos][j])
                pt_w[j] = adj[pos][j];
        }
    }
    std::sort(edge_len, edge_len+p-1);
    return sqrt((double)edge_len[p-1-s]);
}

int main()
{
    int i, c;
    scanf("%d", &c);
    while(c--)
    {
        scanf("%d%d", &s, &p);
        for(i = 0; i < p; i++)
            scanf("%d%d", &x[i], &y[i]);
        init_graph();
        printf("%.2f\n", solve());
    }
    return 0;
}

