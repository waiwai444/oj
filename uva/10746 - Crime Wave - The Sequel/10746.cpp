#include <cstdio>
#include <cstring>
#include <queue>

#define INF 1000000000.0L
#define EPS 1e-9

int n, m;
int cap[42][42];
int flow[42][42];
double cost[42][42];

bool inq[42];
int prev[42];
double dist[42];

double solve()
{
    int i, u, v;
    double c = 0;
    std::queue<int> q;
    while(true)
    {
        memset(inq, false, sizeof(inq));
        for(i = 1; i <= n+m+1; i++) dist[i] = INF;
        q.push(0);
        while(!q.empty())
        {
            u = q.front(), q.pop();
            inq[u] = false;
            for(v = 0; v <= n+m+1; v++)
            {
                if(cap[u][v]-flow[u][v] > 0 && dist[v] > dist[u]+cost[u][v]+EPS)
                {
                    dist[v] = dist[u]+cost[u][v];
                    prev[v] = u;
                    if(!inq[v])
                    {
                        q.push(v);
                        inq[v] = true;
                    }
                }
            }
        }
        if(dist[n+m+1] == INF)
            break;
        for(u = n+m+1; u != 0; u = prev[u])
        {
            ++flow[prev[u]][u];
            --flow[u][prev[u]];
        }
        c += dist[n+m+1];
    }
    return c/n;
}

int main()
{
    int i, j;
    double c;
    while(scanf("%d%d", &n, &m), n)
    {
        memset(cap, 0, sizeof(cap));
        memset(flow, 0, sizeof(flow));
        memset(cost, 0, sizeof(cost));
        for(i = 1; i <= n; i++)
        {
            for(j = 1; j <= m; j++)
            {
                scanf("%lf", &c);
                cap[i][n+j] = 1;
                cost[i][n+j] = c;
                cost[n+j][i] = -c;
            }
            cap[0][i] = 1;
        }
        for(i = 1; i <= m; i++)
            cap[n+i][n+m+1] = 1;
        printf("%.2f\n", solve()+EPS);
    }
    return 0;
}

