#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

struct seg_t
{
    int l, r, y;
};

int size, n;
std::vector<seg_t> segs;

bool cmp_seg(const seg_t &s1, const seg_t &s2)
{
    if(s1.y < s2.y)
        return true;
    if(s1.y == s2.y && s1.l < s2.l)
        return true;
    return false;
}

void get_seg(double x, double y, double r, int b, double w)
{
    double t;
    seg_t s;
    s.y = b;
    t = sqrt(r*r-(w-y)*(w-y));
    s.l = std::max(0, (int)(x-t));
    s.r = std::min(size, (int)ceil(x+t));
    segs.push_back(s);
}

void cut_circle(double x, double y, double r)
{
    int i, top = y+r, bot = y-r+1;
    if(top >= size) top = size-1;
    if(bot <= 0) bot = 1;
    for(i = top; i > (int)y && i >= 0; i--)
        get_seg(x, y, r, i, i);
    get_seg(x, y, r, (int)y, y);
    for(i = bot; i <= (int)y && i <= size; i++)
        get_seg(x, y, r, i-1, i);
}

int count()
{
    int i = 0, y, x, ans = 0;
    y = -1;
    for(i = 0; i < segs.size(); i++)
    {
        seg_t &s = segs[i];
        if(s.y > y)
        {
            ans += s.r-s.l;
            y = s.y;
            x = s.r;
        }
        else if(s.r > x)
        {
            if(s.l < x)
                ans += s.r-x;
            else
                ans += s.r-s.l;
            x = s.r;
        }
    }
    return ans;
}

int main()
{
    int tc, i;
    double x, y, r;
    segs.reserve(1000000);
    scanf("%d", &tc);
    while(tc--)
    {
        segs.clear();
        scanf("%d%d", &size, &n);
        for(i = 0; i < n; i++)
        {
            scanf("%lf%lf%lf", &x, &y, &r);
            cut_circle(x, y, r);
        }
        std::sort(segs.begin(), segs.end(), cmp_seg);
        printf("%d\n", count());
    }
    return 0;
}

