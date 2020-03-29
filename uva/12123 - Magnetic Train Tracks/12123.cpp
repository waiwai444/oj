#include <cstdio>
#include <algorithm>

using namespace std;

int n;

struct point_t
{
    int x, y;
} sta[1200];

point_t nb[1200];

bool compare_nb(const point_t &nb1, const point_t &nb2)
{
    // No 3 points will be collinear.
    if(nb1.y >= 0 && nb2.y < 0)
        return true;
    if(nb1.y < 0 && nb2.y >= 0)
        return false;
    if(nb1.y >= 0 && nb2.y >= 0)
    {
        if(nb1.x >= 0 && nb2.x < 0)
            return true;
        if(nb1.x < 0 && nb2.x >= 0)
            return false;
        if(nb1.y*nb2.x < nb1.x*nb2.y)
            return true;
        return false;
    }
    if(nb1.x >= 0 && nb2.x < 0)
        return false;
    if(nb1.x < 0 && nb2.x >= 0)
        return true;
    if(nb1.y*nb2.x < nb1.x*nb2.y)
        return true;
    return false;
}

// from p1 to p2, [0, 90)
inline bool angle_0_90(const point_t &p1, const point_t &p2)
{
    return p1.x*p2.y-p1.y*p2.x >= 0 && p1.x*p2.x+p1.y*p2.y > 0;
}

int solve()
{
    int i, j, k, l, a = 0;
    for(i = 0; i < n; i++)
    {
        for(j = 0, l = 0; j < n; j++)
        {
            if(j == i) continue;
            nb[l].x = sta[j].x-sta[i].x;
            nb[l].y = sta[j].y-sta[i].y;
            ++l;
        }
        sort(nb, nb+l, compare_nb);
        j = 0, k = 0;
        while(k < l)
        {
            point_t &p = nb[j >= l ? j-l : j];
            if(!angle_0_90(nb[k], p) || j-l == k)
            {
                a += j-k-1;
                ++k;
            }
            else
                ++j;
        }
    }
    return n*(n-1)*(n-2)/6-(n*(n-1)*(n-2)/2-a);
}

int main()
{
    int i, tc = 0;
    while(scanf("%d", &n), n)
    {
        for(i = 0; i < n; i++)
            scanf("%d%d", &sta[i].x, &sta[i].y);
        printf("Scenario %d:\nThere are %d sites for making valid tracks\n", ++tc, solve());
    }
    return 0;
}

