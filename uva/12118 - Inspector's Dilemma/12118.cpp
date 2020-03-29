#include <cstdio>
#include <cstring>

int V, E, T;

int parent[1001];
int rank[1001];
int degree[1001];
int ovc[1001];

void make_set()
{
    for(int i = 1; i <= V; ++i)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find_set(int x)
{
    while(parent[x] != x)
    {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void union_set(int x, int y)
{
    int rx = find_set(x);
    int ry = find_set(y);
    if(rx == ry)
        return;
    if(rank[rx] < rank[ry])
        parent[rx] = ry;
    else if(rank[rx] > rank[ry])
        parent[ry] = rx;
    else
    {
        parent[ry] = rx;
        ++rank[rx];
    }
}

void count_odd_vertex()
{
    for(int i = 1; i <= V; ++i)
    {
        int r = find_set(i);
        if(degree[i]&1)
            ++ovc[r];
    }
}

int get_move_num()
{
    int nc = 0;
    for(int i = 1; i <= V; ++i)
    {
        if(parent[i] != i || degree[i] == 0)
            continue;
        if(ovc[i] == 0)
            ++nc;
        else
            nc += ovc[i]/2;
    }
    if(nc > 0)
        --nc;
    return nc+E;
}

int main()
{
    int i, x, y, tc = 0;
    while(std::scanf("%d%d%d", &V, &E, &T))
    {
        if(V == 0 && E == 0 && T == 0)
            break;
        std::memset(degree, 0, sizeof(degree));
        std::memset(ovc, 0, sizeof(ovc));
        make_set();
        for(i = 0; i < E; ++i)
        {
            std::scanf("%d%d", &x, &y);
            ++degree[x], ++degree[y];
            union_set(x, y);
        }
        count_odd_vertex();
        std::printf("Case %d: %d\n", ++tc, get_move_num()*T);
    }
    return 0;
}

