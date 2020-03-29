#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define MAXNN 502

int np, nm, nf, nmu, nsp;
char music[500][101], sport[500][101];
struct pupil_t
{
    int height;
    int mid, sid;
} male[500], female[500];

int nn;
struct arc_t
{
    int u, v;
    bool c;
};
std::vector<arc_t> arcs;
std::vector<int> adj[MAXNN];

int get_mid(const char *m)
{
    for(int i = 0; i < nmu; i++)
        if(strcmp(m, music[i]) == 0)
            return i;
    strcpy(music[nmu], m);
    return nmu++;
}

int get_sid(const char *s)
{
    for(int i = 0; i < nsp; i++)
        if(strcmp(s, sport[i]) == 0)
            return i;
    strcpy(sport[nsp], s);
    return nsp++;
}

void add_arc_pair(int u, int v)
{
    arc_t a;
    a.u = u, a.v = v, a.c = true;
    adj[u].push_back(arcs.size());
    arcs.push_back(a);
    a.u = v, a.v = u, a.c = false;
    adj[v].push_back(arcs.size());
    arcs.push_back(a);
}

void create_network()
{
    int i, j;
    arcs.clear();
    for(i = 0; i < nn; i++)
        adj[i].clear();
    nn = nm+nf+2;
    for(i = 0; i < nm; i++)
        add_arc_pair(0, 1+i);
    for(i = 0; i < nm; i++)
    {
        for(j = 0; j < nf; j++)
        {
            if(abs(male[i].height-female[j].height) <= 40 && male[i].mid == female[j].mid && male[i].sid != female[j].sid)
            {
                add_arc_pair(1+i, 1+nm+j);
            }
        }
    }
    for(i = 0; i < nf; i++)
        add_arc_pair(1+nm+i, 1+nm+nf);
}

std::queue<int> q;
int dist[MAXNN];
int next[MAXNN];

bool bfs(int s, int t)
{
    int i, u;
    memset(dist, INF, sizeof(dist));
    dist[s] = 0;
    q.push(s);
    while(!q.empty())
    {
        u = q.front(), q.pop();
        for(i = 0; i < adj[u].size(); i++)
        {
            arc_t &a = arcs[adj[u][i]];
            if(a.c && dist[a.v] == INF)
            {
                dist[a.v] = dist[u]+1;
                q.push(a.v);
            }
        }
    }
    return dist[t] < INF;
}

bool send_flow(int cur, int t)
{
    if(cur == t)
        return true;
    int i;
    for(; next[cur] != adj[cur].size(); ++next[cur])
    {
        i = adj[cur][next[cur]];
        arc_t &a = arcs[i];
        if(a.c && dist[a.v] > dist[cur])
        {
            if(send_flow(a.v, t))
            {
                a.c = false;
                arcs[i^1].c = true;
                return true;
            }
        }
    }
    return false;
}

int maxflow(int s, int t)
{
    int f = 0;
    while(bfs(s, t))
    {
        memset(next, 0, sizeof(next));
        while(send_flow(s, t))
            ++f;
    }
    return f;
}

int solve()
{
    create_network();
    int f = maxflow(0, 1+nm+nf);
    return np-f;
}

int main()
{
    int i, tc, h;
    char g[2], m[101], s[101];
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d", &np);
        nm = nf = nmu = nsp = 0;
        for(i = 0; i < np; i++)
        {
            scanf("%d%s%s%s", &h, g, m, s);
            if(g[0] == 'M')
            {
                male[nm].height = h;
                male[nm].mid = get_mid(m);
                male[nm++].sid = get_sid(s);
            }
            else
            {
                female[nf].height = h;
                female[nf].mid = get_mid(m);
                female[nf++].sid = get_sid(s);
            }
        }
        printf("%d\n", solve());
    }
    return 0;
}

