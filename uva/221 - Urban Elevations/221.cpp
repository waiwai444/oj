#include <cstdio>
#include <algorithm>

int n;
struct building_t
{
    int id;
    double x, y;
    double w, d, h;
} bds[101];
bool vis[101];

bool cmp_bds(const building_t &b1, const building_t &b2)
{
    if(b1.x < b2.x)
        return true;
    if(b1.x > b2.x)
        return false;
    return b1.y < b2.y;
}

void solve()
{
    int i, j;
    double l;
    std::sort(&bds[0], &bds[n], cmp_bds);
    vis[0] = true;
    for(i = 1; i < n; ++i)
    {
        vis[i] = false;
        l = bds[i].x;
        for(j = 0; j < i; ++j)
        {
            if(bds[j].y >= bds[i].y || bds[j].h < bds[i].h)
                continue;
            l = std::max(l, bds[j].x+bds[j].w);
            if(l >= bds[i].x+bds[i].w)
                break;
        }
        if(l >= bds[i].x+bds[i].w)
            continue;
        for(j = i+1; j < n; ++j)
        {
            if(bds[j].x > l || bds[j].x >= bds[i].x+bds[i].w)
                break;
            if(bds[j].y >= bds[i].y || bds[j].h < bds[i].h)
                continue;
            l = std::max(l, bds[j].x+bds[j].w);
            if(l >= bds[i].x+bds[i].w)
                break;
        }
        if(l < bds[i].x+bds[i].w)
            vis[i] = true;
    }
}

int main()
{
    int i, tc = 0;
    while(scanf("%d", &n), n)
    {
        for(i = 0; i < n; ++i)
        {
            bds[i].id = i+1;
            scanf("%lf%lf%lf%lf%lf", &bds[i].x, &bds[i].y, &bds[i].w, &bds[i].d, &bds[i].h);
        }
        solve();
        if(tc)
            putchar('\n');
        printf("For map #%d, the visible buildings are numbered as follows:\n", ++tc);
        printf("%d", bds[0].id);
        for(i = 1; i < n; ++i)
            if(vis[i])
                printf(" %d", bds[i].id);
        putchar('\n');
    }
    return 0;
}

