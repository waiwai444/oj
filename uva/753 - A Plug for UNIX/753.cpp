#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f
#define MAXN 502

int n, m;
char rec[400][25];
struct arc_t
{
    int u, v, cap, flow, rev;
};
std::vector<arc_t> arc;
std::vector<int> alist[MAXN];
int inarc[MAXN];
bool vis[MAXN];

int find_plug_type(const char *plug)
{
    for(int i = 0; i < n; i++)
        if(strcmp(rec[i], plug) == 0)
            return i;
    return -1;
}

int find_arc(int u, int v)
{
    for(int i = 0; i < alist[u].size(); i++)
        if(arc[alist[u][i]].v == v)
            return alist[u][i];
    return -1;
}

inline arc_t make_arc(int u, int v, int cap, int flow, int rev)
{
    arc_t a;
    a.u = u, a.v = v, a.cap = cap, a.flow = flow, a.rev = rev;
    return a;
}

void add_arc(int u, int v, int cap)
{
    alist[u].push_back(arc.size());
    alist[v].push_back(arc.size()+1);
    arc.push_back(make_arc(u, v, cap, 0, arc.size()+1));
    arc.push_back(make_arc(v, u, 0, 0, arc.size()-1));
}

int solve()
{
    int i, u, v, a, s = 0;
    std::queue<int> q;
    while(true)
    {
        memset(vis, false, sizeof(vis));
        vis[0] = true;
        q.push(0);
        while(!q.empty())
        {
            u = q.front(); q.pop();
            for(i = 0; i < alist[u].size(); i++)
            {
                a = alist[u][i];
                v = arc[a].v;
                if(!vis[v] && arc[a].cap-arc[a].flow > 0)
                {
                    inarc[v] = a;
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
        if(!vis[MAXN-1])
            break;
        for(u = MAXN-1; u != 0; u = arc[inarc[u]].u)
        {
            ++arc[inarc[u]].flow;
            --arc[arc[inarc[u]].rev].flow;
        }
        ++s;
    }
    return m-s;
}

int main()
{
    int i, j, j2, a, k, tc;
    char tmp[25], tmp2[25];
    scanf("%d", &tc);
    while(tc--)
    {
        arc.clear();
        for(i = 0; i < MAXN; i++)
            alist[i].clear();
        scanf("%d", &n);
        for(i = 0; i < n; i++)
        {
            scanf("%s", rec[i]);
            add_arc(101+i, MAXN-1, 1);
        }
        scanf("%d", &m);
        for(i = 0; i < m; i++)
        {
            scanf("%*s%24s", tmp);
            j = find_plug_type(tmp);
            if(j >= 0)
                add_arc(1+i, 101+j, 1);
            else
            {
                strcpy(rec[n], tmp);
                add_arc(1+i, 101+n, 1);
                ++n;
            }
            add_arc(0, 1+i, 1);
        }
        scanf("%d", &k);
        for(i = 0; i < k; i++)
        {
            scanf("%24s%24s", tmp, tmp2);
            j = find_plug_type(tmp);
            j2 = find_plug_type(tmp2);
            if(j < 0)
            {
                strcpy(rec[n], tmp);
                j = n++;
            }
            if(j2 < 0)
            {
                strcpy(rec[n], tmp2);
                j2 = n++;
            }
            a = find_arc(101+j, 101+j2);
            if(a >= 0)
                arc[a].cap = INF;
            else
                add_arc(101+j, 101+j2, INF);
        }
        printf("%d\n", solve());
        if(tc)
            printf("\n");
    }
    return 0;
}

