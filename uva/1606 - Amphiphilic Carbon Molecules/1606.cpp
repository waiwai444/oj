#include <cstdio>
#include <algorithm>

int n;
struct point_t
{
    int x, y, r;
} pt[1000], pt2[1000];

inline int cross_prod(int x1, int y1, int x2, int y2)
{
    return x1*y2-x2*y1;
}

bool cmp(const point_t &p1, const point_t &p2)
{
    if(p1.y == 0 && p2.y == 0)
        return p1.x > 0 && p2.x < 0;
    if(p1.y == 0 && p1.x > 0)
        return true;
    if(p1.y*p2.y >= 0)
        return cross_prod(p1.x, p1.y, p2.x, p2.y) > 0;
    return p1.y > 0 && p2.y < 0;
}

int solve()
{
    int i, j, k, s, t;
    int ans = 1;
    for(i = 0; i < n; ++i)
    {
        for(j = t = 0; j < n; ++j)
        {
            if(j == i || (pt[j].x == pt[i].x && pt[j].y == pt[i].y))
                continue;
            pt2[t].x = pt[j].x-pt[i].x;
            pt2[t].y = pt[j].y-pt[i].y;
            if(pt[j].r == 1)
            {
                pt2[t].x = -pt2[t].x;
                pt2[t].y = -pt2[t].y;
            }
            ++t;
        }
        if(t == 0)
            return n;
        std::sort(&pt2[0], &pt2[t], cmp);

        s = n-t+1;
        for(j = 0, k = 1%t; j < t; ++j, --s)
        {
            while(k != j && cross_prod(pt2[j].x, pt2[j].y, pt2[k].x, pt2[k].y) >= 0)
                ++s, k = (k+1)%t;
            if(s > ans)
                ans = s;
        }
    }
    return ans;
}

int main()
{
    int i;
    while(scanf("%d", &n) != EOF)
    {
        if(n == 0)
            break;
        for(i = 0; i < n; ++i)
            scanf("%d%d%d", &pt[i].x, &pt[i].y, &pt[i].r);
        printf("%d\n", solve());
    }
    return 0;
}

