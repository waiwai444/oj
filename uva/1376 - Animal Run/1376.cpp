#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <vector>
#include <queue>
#include <utility>

#define MAXN 1000
#define MAXV ((MAXN-1)*(MAXN-1)*2+2)
#define INF 0x3f3f3f3f

int n, m, nv;
typedef std::pair<int, int> pii;
std::vector<pii> adj[MAXV];
int dist[MAXV];
bool done[MAXV];

int readint()
{
    int x = 0, c = getchar();
    while(!isdigit(c))
        c = getchar();
    while(isdigit(c))
    {
        x = x*10+c-'0';
        c = getchar();
    }
    return x;
}

void add_edge(int u, int v, int w)
{
    pii p;
    p = std::make_pair(v, w);
    adj[u].push_back(p);
    p = std::make_pair(u, w);
    adj[v].push_back(p);
}

void construct_graph()
{
    int i, j, u, v, w;
    for(i = 0; i < nv; i++)
        adj[i].clear();
    nv = (n-1)*(m-1)*2+2;
    for(i = 1; i <= n; i++)
    {
        for(j = 1; j < m; j++)
        {
            w = readint();
            if(i == 1)
            {
                u = j*2;
                v = nv-1;
            }
            else if(i == n)
            {
                u = 0;
                v = (n-2)*(m-1)*2+j*2-1;
            }
            else
            {
                u = (i-1)*(m-1)*2+j*2;
                v = (i-2)*(m-1)*2+j*2-1;
            }
            add_edge(u, v, w);
        }
    }
    for(i = 1; i < n; i++)
    {
        for(j = 1; j <= m; j++)
        {
            w = readint();
            if(j == 1)
            {
                u = 0;
                v = (i-1)*(m-1)*2+1;
            }
            else if(j == m)
            {
                u = i*(m-1)*2;
                v = nv-1;
            }
            else
            {
                u = (i-1)*(m-1)*2+(j-1)*2;
                v = (i-1)*(m-1)*2+j*2-1;
            }
            add_edge(u, v, w);
        }
    }
    for(i = 1; i < n; i++)
    {
        for(j = 1; j < m; j++)
        {
            w = readint();
            u = (i-1)*(m-1)*2+j*2-1;
            v = (i-1)*(m-1)*2+j*2;
            add_edge(u, v, w);
        }
    }
}

int sssp(int s, int t)
{
    int u, v, w;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii> > q;
    std::vector<pii>::iterator it;
    pii p;
    memset(dist, INF, sizeof(int)*nv);
    memset(done, false, sizeof(bool)*nv);
    q.push(std::make_pair(0, s));
    dist[s] = 0;
    while(!q.empty())
    {
        p = q.top(), q.pop();
        u = p.second;
        if(u == t)
            break;
        if(done[u])
            continue;
        done[u] = true;
        for(it = adj[u].begin(); it != adj[u].end(); ++it)
        {
            v = it->first;
            w = it->second;
            if(dist[v] > dist[u]+w)
            {
                dist[v] = dist[u]+w;
                q.push(std::make_pair(dist[v], v));
            }
        }
    }
    return dist[t];
}

int main()
{
    int ret, c = 0;
    while(true)
    {
        n = readint(), m = readint();
        if(n == 0)
            break;
        construct_graph();
        ret = sssp(0, nv-1);
        printf("Case %d: Minimum = %d\n", ++c, ret);
    }
    return 0;
}

