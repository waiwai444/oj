#include <cstdio>
#include <algorithm>

#define MAXN 10000

int n;
struct point_t
{
    int x, y;
} pts[MAXN];

bool cmp_pt(const point_t &p1, const point_t &p2)
{
    if(p1.y < p2.y)
        return true;
    if(p1.y == p2.y && p1.x < p2.x)
        return true;
    return false;
}

bool solve()
{
    int i;
    std::sort(pts, pts+n, cmp_pt);
    int cx = pts[0].x+pts[n-1].x;
    int cy = pts[0].y+pts[n-1].y;
    for(i = 1; i <= n/2; i++)
    {
        int cx1 = pts[i].x+pts[n-1-i].x;
        int cy1 = pts[i].y+pts[n-1-i].y;
        if(cx != cx1 || cy != cy1)
            return false;
    }
    return true;
}

int main()
{
    int i, c;
    scanf("%d", &c);
    while(c--)
    {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d%d", &pts[i].x, &pts[i].y);
        if(solve())
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}

