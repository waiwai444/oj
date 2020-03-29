#include <cstdio>
#include <climits>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

long n, m, ne;
std::vector<std::pair<long, long> > adj[100000];
long dist[100000];
long q[100000], front, rear;
bool vis[100000];

void find_dist()
{
    long i, a, b;
    for(i = 0; i < n; ++i)
        dist[i] = LONG_MAX;
    front = rear = 0;
    q[rear++] = n-1;
    dist[n-1] = 0;
    while(q[front] != 0)
    {
        a = q[front++];
        for(i = 0; i < adj[a].size(); ++i)
        {
            b = adj[a][i].first;
            if(dist[b] < LONG_MAX)
                continue;
            q[rear++] = b;
            dist[b] = dist[a]+1;
        }
    }
}

void print_path()
{
    long i, j, k, a, b, minc, curd;
    bool first = true;
    for(i = 0; i < n; ++i)
        vis[i] = false;
    front = rear = 0;
    q[rear++] = 0;
    curd = dist[0], minc = LONG_MAX;
    while(q[front] != n-1)
    {
        a = q[front++];
        for(i = 0; i < adj[a].size(); ++i)
            if(dist[adj[a][i].first] == curd-1)
                minc = std::min(minc, adj[a][i].second);
        for(i = 0; i < adj[a].size(); ++i)
        {
            b = adj[a][i].first;
            if(dist[b] == curd-1 && adj[a][i].second == minc && !vis[b])
            {
                q[rear++] = b;
                vis[b] = true;
            }
        }
        if(dist[q[front]] < curd)
        {
            first ? first = false, std::printf("%ld", minc) : std::printf(" %ld", minc);
            curd = dist[q[front]], minc = LONG_MAX;
        }
    }
}

void solve()
{
    find_dist();
    std::printf("%ld\n", dist[0]);
    print_path();
    std::putchar('\n');
}

int main()
{
    long i, a, b, c;
    while(std::scanf("%ld%ld", &n, &m) != EOF)
    {
        for(i = 0; i < n; ++i)
            adj[i].clear();
        ne = 0;
        for(i = 0; i < m; ++i)
        {
            std::scanf("%ld%ld%ld", &a, &b, &c);
            if(a == b)
                continue;
            adj[a-1].push_back(std::make_pair(b-1, c));
            adj[b-1].push_back(std::make_pair(a-1, c));
        }
        solve();
    }
    return 0;
}
