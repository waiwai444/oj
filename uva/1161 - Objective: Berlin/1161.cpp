#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 0x3f3f3f3f
#define MAXC 150
#define MAXFL 5000
#define MAXNN (2*MAXFL+2)
#define TRANSFER_TIME 30

int nc, nf, nn;
int latest;

struct arc_t
{
    int u, v, cap, flow;
};
std::vector<arc_t> arcs;

std::vector<int> adj[MAXNN]; // for each node

struct flight_t
{
    int from, to, cap, dtime, atime;
    int dnode, anode;
} flights[MAXFL];

struct city_t
{
    char name[10];
    std::vector<int> depart;
    std::vector<int> arrival;
} cities[MAXC];

void add_city(const char *name)
{
    strcpy(cities[nc].name, name);
    cities[nc].depart.clear();
    cities[nc].arrival.clear();
    ++nc;
}

int get_city_idx(const char *name)
{
    for(int i = 0; i < nc; i++)
        if(strcmp(cities[i].name, name) == 0)
            return i;
    add_city(name);
    return nc-1;
}

void change_time_fmt(int *time)
{
    int h = *time/100;
    int m = *time%100;
    *time = h*60+m;
}

void add_arc_pair(int u, int v, int cap)
{
    arc_t a;
    a.u = u, a.v = v, a.cap = cap, a.flow = 0;
    adj[u].push_back(arcs.size());
    arcs.push_back(a);
    a.u = v, a.v = u, a.cap = 0;
    adj[v].push_back(arcs.size());
    arcs.push_back(a);
}

void construct_graph()
{
    int i, j, k;
    for(i = 0; i < nn; i++)
        adj[i].clear();
    nn = 1;
    for(i = 0; i < nf; i++)
    {
        flight_t &fl = flights[i];
        fl.dnode = nn++, fl.anode = nn++;
        add_arc_pair(nn-2, nn-1, fl.cap);
    }
    ++nn;
    for(i = 0; i < cities[0].depart.size(); i++)
    {
        flight_t &fl = flights[cities[0].depart[i]];
        add_arc_pair(0, fl.dnode, INF);
    }
    for(i = 0; i < nc; i++)
    {
        for(j = 0; j < cities[i].arrival.size(); j++)
        {
            flight_t &fl1 = flights[cities[i].arrival[j]];
            for(k = 0; k < cities[i].depart.size(); k++)
            {
                flight_t &fl2 = flights[cities[i].depart[k]];
                if(fl1.atime+TRANSFER_TIME <= fl2.dtime)
                    add_arc_pair(fl1.anode, fl2.dnode, INF);
            }
        }
    }
    for(i = 0; i < cities[1].arrival.size(); i++)
    {
        flight_t &fl = flights[cities[1].arrival[i]];
        if(fl.atime <= latest)
            add_arc_pair(fl.anode, nn-1, INF);
    }
}

std::queue<int> q;
int dist[MAXNN];
int next[MAXNN];

bool bfs()
{
    int i, u;
    memset(dist, INF, sizeof(dist));
    dist[0] = 0;
    q.push(0);
    while(!q.empty())
    {
        u = q.front(), q.pop();
        for(i = 0; i < adj[u].size(); i++)
        {
            arc_t &a = arcs[adj[u][i]];
            if(a.cap > a.flow && dist[a.v] == INF)
            {
                dist[a.v] = dist[u]+1;
                q.push(a.v);
            }
        }
    }
    return dist[nn-1] < INF;
}

int send_flow(int cur, int flow)
{
    if(cur == nn-1)
        return flow;
    int f;
    for(; next[cur] != adj[cur].size(); ++next[cur])
    {
        arc_t &a = arcs[adj[cur][next[cur]]];
        if(a.cap <= a.flow || dist[a.v] <= dist[cur]) continue;
        f = std::min(flow, a.cap-a.flow);
        if(f = send_flow(a.v, f))
        {
            a.flow += f;
            arcs[adj[cur][next[cur]]^1].flow -= f;
            return f;
        }
    }
    return 0;
}

int maxflow()
{
    int tot = 0, f;
    while(bfs())
    {
        memset(next, 0, nn*sizeof(int));
        while(f = send_flow(0, INF))
            tot += f;
    }
    return tot;
}

int main()
{
    int i;
    char name1[10], name2[10];
    while(scanf("%*d") != EOF)
    {
        nc = 0;
        scanf("%s%s%d%d", name1, name2, &latest, &nf);
        change_time_fmt(&latest);
        add_city(name1), add_city(name2);
        for(i = 0; i < nf; i++)
        {
            scanf("%s%s%d%d%d", name1, name2, &flights[i].cap, &flights[i].dtime, &flights[i].atime);
            change_time_fmt(&flights[i].dtime);
            change_time_fmt(&flights[i].atime);
            flights[i].from = get_city_idx(name1);
            flights[i].to = get_city_idx(name2);
            cities[flights[i].from].depart.push_back(i);
            cities[flights[i].to].arrival.push_back(i);
        }
        construct_graph();
        printf("%d\n", maxflow());
    }
    return 0;
}

