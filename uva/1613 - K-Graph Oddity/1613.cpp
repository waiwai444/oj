#include <stdio.h>
#include <list>
#include <map>
#include <set>
#include <utility>

int n;
std::list<int> edges[10001];
int deg_r[10001];
int color[10001];

struct vlink_t
{
    int v;
    vlink_t *prev, *next;
} vl[10001];

std::map<int, vlink_t> deg_idx;

void insert_to_deg_idx(int v)
{
    int d = deg_r[v];
    std::pair<std::map<int, vlink_t>::iterator, bool> p = deg_idx.insert(std::make_pair(d, vlink_t()));
    std::map<int, vlink_t>::iterator it = p.first;
    vl[v].next = it->second.next;
    it->second.next = &vl[v];
    if(vl[v].next)
        vl[v].next->prev = &vl[v];
    vl[v].prev = &it->second;
}

void remove_from_deg_idx(int v)
{
    int d = deg_r[v];
    std::map<int, vlink_t>::iterator it = deg_idx.find(d);
    vl[v].prev->next = vl[v].next;
    if(vl[v].next)
        vl[v].next->prev = vl[v].prev;
    if(!it->second.next)
        deg_idx.erase(it);
}

void solve(int r)
{
    std::list<int>::iterator it;
    int cv = deg_idx.begin()->second.next->v;

    if(r == 1)
    {
        color[cv] = 1;
        return;
    }

    remove_from_deg_idx(cv);
    color[cv] = -1;
    for(it = edges[cv].begin(); it != edges[cv].end(); ++it)
    {
        int av = *it;
        if(color[av] < 0)
            continue;
        remove_from_deg_idx(av);
        --deg_r[av];
        insert_to_deg_idx(av);
    }

    solve(r-1);

    std::set<int> color_set;
    for(it = edges[cv].begin(); it != edges[cv].end(); ++it)
    {
        int c = color[*it];
        if(c > 0)
            color_set.insert(c);
    }

    color[cv] = 1;
    for(std::set<int>::iterator it_s = color_set.begin(); it_s != color_set.end(); ++it_s)
    {
        if(*it_s != color[cv])
            break;
        ++color[cv];
    }
}

int main()
{
    int i, m, u, v, md;
    bool fst = true;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        for(i = 1; i <= n; ++i)
        {
            edges[i].clear();
            deg_r[i] = 0;
            color[i] = 0;
            vl[i].v = i;
        }
        for(i = 0; i < m; ++i)
        {
            scanf("%d%d", &u, &v);
            edges[u].push_back(v);
            edges[v].push_back(u);
            ++deg_r[u];
            ++deg_r[v];
        }
        deg_idx.clear();
        for(i = 1; i <= n; ++i)
            insert_to_deg_idx(i);
        md = 1;
        for(i = 1; i <= n; ++i)
            if(deg_r[i] > md)
                md = deg_r[i];

        solve(n);

        if(!fst)
            printf("\n");
        else
            fst = false;
        printf("%d\n", md|1);
        for(i = 1; i <= n; ++i)
            printf("%d\n", color[i]);
    }
    return 0;
}
