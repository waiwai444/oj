#include <cstdio>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <utility>
#include <functional>

#define MAXP (52*52)

struct adj_t
{
    int u, s, v;
    adj_t(int u, int s, int v) : u(u), s(s), v(v) {}
};

struct point_t
{
    int x, y, h;
    std::vector<adj_t> adj;
};

struct side_t
{
    int u, v;
    int a[2];
    side_t() { a[0] = -1, a[1] = -1; }
};

struct area_t
{
    std::vector<int> sd;
    int min_h;
    int wl;
    area_t() : min_h(0), wl(-1) {}
};

typedef std::pair<int, int> pii;

int np, ns;
point_t pts[MAXP];
int ptidx[MAXP];
std::vector<side_t> sds;
std::vector<area_t> areas;

std::priority_queue<pii, std::vector<pii>, std::greater<pii> > pq;
std::queue<int> q;
std::vector<int> ans;

int letter_idx(char ch)
{
    if(ch >= 'a' && ch <= 'z')
        return ch-'a';
    return ch-'A'+26;
}

int point_idx(char *code)
{
    return letter_idx(code[0])*52+letter_idx(code[1]);
}

bool cmp_adj(const adj_t &adj1, const adj_t &adj2)
{
    int u = adj1.u, v = adj1.v, w = adj2.v;
    int x1 = pts[v].x-pts[u].x, y1 = pts[v].y-pts[u].y;
    int x2 = pts[w].x-pts[u].x, y2 = pts[w].y-pts[u].y;
    if(x1 == 0)
        return x2 >= 0 ? y1 < 0 : true;
    if(x2 == 0)
        return x1 >= 0 ? y2 > 0 : false;
    if(x1 > 0 && x2 < 0)
        return true;
    if(x1 < 0 && x2 > 0)
        return false;
    return (double)y1/x1 < (double)y2/x2;
}

int get_side_id(int pid1, int pid2)
{
    point_t &p = pts[pid1];
    for(int i = 0; i < p.adj.size(); i++)
        if(p.adj[i].v == pid2)
            return p.adj[i].s;
    return -1;
}

void bind_area_side(int aid, int sid)
{
    area_t &a = areas[aid];
    side_t &s = sds[sid];
    a.sd.push_back(sid);
    s.a[0] < 0 ? s.a[0] = aid : s.a[1] = aid;
}

int cross_product(const point_t &p0, const point_t &p1, const point_t &p2)
{
    int x1 = p1.x-p0.x, y1 = p1.y-p0.y;
    int x2 = p2.x-p0.x, y2 = p2.y-p0.y;
    return x1*y2-x2*y1;
}

void add_triangle(int u, const adj_t &adj1, const adj_t &adj2)
{
    int s, v = adj1.v, w = adj2.v;
    if(u >= v || u >= w)
        return;
    if(cross_product(pts[u], pts[v], pts[w]) <= 0)
        return;
    if((s = get_side_id(v, w)) < 0)
        return;
    area_t a;
    a.min_h = std::min(std::min(pts[u].h, pts[v].h), pts[w].h);
    areas.push_back(a);
    bind_area_side(areas.size()-1, adj1.s);
    bind_area_side(areas.size()-1, adj2.s);
    bind_area_side(areas.size()-1, s);
}

void get_areas()
{
    int i, j;
    areas.clear();
    areas.push_back(area_t());// outer area
    for(i = 0; i < np; i++)
    {
        std::vector<adj_t> &adj = pts[i].adj;
        std::sort(adj.begin(), adj.end(), cmp_adj);

        for(j = 1; j < adj.size(); j++)
            add_triangle(i, adj[j-1], adj[j]);
        if(adj.size() > 1)
            add_triangle(i, adj[j-1], adj[0]);
    }
    for(i = 0; i < sds.size(); i++)
        if(sds[i].a[1] < 0)
            bind_area_side(0, i);
}

void max_water_level()
{
    int i, wl, h, aid, nid;
    pii p; 
    pq.push(std::make_pair(0, 0));
    while(!pq.empty())
    {
        p = pq.top(), pq.pop();
        wl = p.first, aid = p.second;
        area_t &a = areas[aid];
        if(a.wl >= 0)
            continue;
        a.wl = wl;
        for(i = 0; i < a.sd.size(); i++)
        {
            side_t &s = sds[a.sd[i]];
            nid = s.a[0] != aid ? s.a[0] : s.a[1];
            if(areas[nid].wl >= 0)
                continue;
            h = std::min(pts[s.u].h, pts[s.v].h);
            if(areas[nid].min_h < h || wl > h)
                pq.push(std::make_pair(std::max(wl, h), nid));
            else
                pq.push(std::make_pair(0, nid));
        }
    }
}

void floodfill()
{
    int i, j, aid, nid, wl;
    for(i = 0; i < areas.size(); i++)
    {
        wl = areas[i].wl;
        if(wl == 0)
            continue;
        ans.push_back(wl);
        q.push(i);
        areas[i].wl = 0;
        while(!q.empty())
        {
            aid = q.front(), q.pop();
            area_t &a = areas[aid];
            for(j = 0; j < a.sd.size(); j++)
            {
                side_t &s = sds[a.sd[j]];
                nid = s.a[0] != aid ? s.a[0] : s.a[1];
                if(areas[nid].wl == 0 || (pts[s.u].h >= wl && pts[s.v].h >= wl))
                    continue;
                q.push(nid);
                areas[nid].wl = 0;
            }
        }
    }
}

void solve()
{
    ans.clear();
    max_water_level();
    floodfill();
    std::sort(ans.begin(), ans.end());
}

int main()
{
    int i, c = 0;
    char id[3];
    side_t sd;
    while(scanf("%d%d", &np, &ns), np)
    {
        sds.clear();
        for(i = 0; i < np; i++)
        {
            scanf("%s%d%d%d", id, &pts[i].x, &pts[i].y, &pts[i].h);
            pts[i].adj.clear();
            ptidx[point_idx(id)] = i;
        }
        for(i = 0; i < ns; i++)
        {
            scanf("%s", id);
            sd.u = ptidx[point_idx(id)];
            scanf("%s", id);
            sd.v = ptidx[point_idx(id)];
            sds.push_back(sd);
            pts[sd.u].adj.push_back(adj_t(sd.u, i, sd.v));
            pts[sd.v].adj.push_back(adj_t(sd.v, i, sd.u));
        }
        get_areas();
        solve();
        printf("Case %d:\n", ++c);
        if(ans.size() == 0)
            printf("  0\n");
        else
            for(i = 0; i < ans.size(); i++)
                printf("  %d\n", ans[i]);
    }
    return 0;
}

