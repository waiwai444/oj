#include <cstdio>
#include <cstring>
#include <utility>

using namespace std;

int adj[21][20];
int adj_num[21];
int dist[21][21];
bool vis[21];
pair<int, int> que[20];
int front, tail;

void bfs(int s)
{
    int i, n;
    pair<int, int> p;
    memset(vis, false, sizeof(vis));
    front = tail = 0;
    que[tail++] = make_pair(s, 0);
    vis[s] = true;
    while(tail > front)
    {
        p = que[front++];
        for(i = 0; i < adj_num[p.first]; i++)
        {
            n = adj[p.first][i];
            if(!vis[n])
            {
                dist[s][n] = dist[n][s] = p.second+1;
                vis[n] = true;
                que[tail++] = make_pair(n, p.second+1);
            }
        }
    }
}

int main()
{
    int i, j, k, n, c = 0;
    while(scanf("%d", &n) != EOF)
    {
        memset(dist, -1, sizeof(dist));
        memset(adj_num, 0, sizeof(adj_num));
        for(k = 0; k < n; k++)
        {
            scanf("%d", &j);
            adj[1][adj_num[1]++] = j;
            adj[j][adj_num[j]++] = 1;
        }
        for(i = 2; i < 20; i++)
        {
            scanf("%d", &n);
            for(k = 0; k < n; k++)
            {
                scanf("%d", &j);
                adj[i][adj_num[i]++] = j;
                adj[j][adj_num[j]++] = i;
            }
        }
        scanf("%d", &n);
        printf("Test Set #%d\n", ++c);
        for(i = 0; i < n; i++)
        {
            scanf("%d%d", &j, &k);
            if(dist[j][k] < 0)
                bfs(j);
            printf("%2d to %2d: %d\n", j, k, dist[j][k]);
        }
        printf("\n");
    }
    return 0;
}

