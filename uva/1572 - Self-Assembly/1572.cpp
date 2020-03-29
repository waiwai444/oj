#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>

long n;

struct molecule_t
{
    signed char intf[4];
} mol[40000];

#define INPATH 1
#define BOUND 2

char vis[40000][4];

std::vector<std::pair<long, int> > idx[53];

signed char parse_conn_label(char *lbl)
{
    if(lbl[0] >= 'A' && lbl[0] <= 'Z')
        return lbl[1] == '-' ? -(lbl[0]-'A'+1) : lbl[0]-'A'+1;
    return 0;
}

inline int idx_pos(signed char i)
{
    return i+26;
}

bool dfs(long m, int ii)
{
    int i;
    std::size_t j;
    signed char l;
    molecule_t *pm = &mol[m];
    for(i = 0; i < 4; ++i)
    {
        if(i == ii)
            continue;
        if((l = pm->intf[i]) == 0)
            continue;
        if(vis[m][i] == INPATH)
            return true;
        if(vis[m][i] == BOUND)
            continue;
        vis[m][i] = INPATH;
        std::vector<std::pair<long, int> > &rv = idx[idx_pos(-l)];
        for(j = 0; j < rv.size(); ++j)
            if(dfs(rv[j].first, rv[j].second))
                return true;
        vis[m][i] = BOUND;
    }
    return false;
}

bool is_unbounded()
{
    std::memset(vis, 0, sizeof(vis));
    for(long i = 0; i < n; ++i)
        if(dfs(i, -1))
            return true;
    return false;
}

int main()
{
    long i, j;
    signed char l;
    char str[10];
    while(std::scanf("%ld", &n) != EOF)
    {
        for(i = 0; i < 53; ++i)
            idx[i].clear();
        for(i = 0; i < n; ++i)
        {
            std::scanf("%s", str);
            for(j = 0; j < 4; ++j)
            {
                l = parse_conn_label(str+j*2);
                mol[i].intf[j] = l;
                if(l != 0)
                    idx[idx_pos(l)].push_back(std::make_pair(i, (int)j));
            }
        }
        if(is_unbounded())
            std::puts("unbounded");
        else
            std::puts("bounded");
    }
    return 0;
}

