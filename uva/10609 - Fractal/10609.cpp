#include <cstdio>
#include <cmath>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>

#define EPS 1e-8

struct point_t
{
    double x, y;
};

typedef std::pair<point_t, point_t> line_t;

std::vector<point_t> pts;
std::queue<line_t> q;

bool cmp_pts(const point_t &u, const point_t &v)
{
    if(u.x < v.x-EPS)
        return true;
    if(u.x > v.x+EPS)
        return false;
    if(u.y < v.y-EPS)
        return true;
    return false;
}

void get_mid_pts(const line_t &l, point_t *c, point_t *d)
{
    double x1, y1, x2, y2;
    x1 = l.first.x, y1 = l.first.y;
    x2 = l.second.x, y2 = l.second.y;
    c->x = (x2-x1)/4+x1;
    c->y = (y2-y1)/4+y1;
    d->x = (x1-x2)/4+x2;
    d->y = (y1-y2)/4+y2;
}

inline double cross_product(double x1, double y1, double x2, double y2)
{
    return x1*y2-x2*y1;
}

inline double distance2(double x1, double y1, double x2, double y2)
{
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

void gen_new_pt(const point_t &c, const point_t &d, point_t *e)
{
    double xm, ym, k, h, r, xe, ye;
    xm = (c.x+d.x)/2, ym = (c.y+d.y)/2;
    h = sqrt(distance2(c.x, c.y, d.x, d.y)/4*3);
    if(fabs(d.y-c.y) < EPS)
    {
        e->x = xm;
        e->y = d.x > c.x ? ym+h : ym-h;
    }
    else
    {
        k = -(d.x-c.x)/(d.y-c.y);
        r = sqrt(h*h/(1+k*k));
        xe = xm+r;
        ye = ym+r*k;
        if(cross_product(c.x-xe, c.y-ye, d.x-xe, d.y-ye) > 0)
            e->x = xe, e->y = ye;
        else
            e->x = xm-r, e->y = ym-r*k;
    }
}

void solve(line_t l, double tt)
{
    point_t c, d, e;
    pts.clear();
    pts.push_back(l.first);
    pts.push_back(l.second);
    if(distance2(l.first.x, l.first.y, l.second.x, l.second.y) > tt*tt-EPS)
        q.push(l);
    while(!q.empty())
    {
        l = q.front(), q.pop();
        get_mid_pts(l, &c, &d);
        if(distance2(c.x, c.y, d.x, d.y) > tt*tt-EPS)
        {
            gen_new_pt(c, d, &e);
            pts.push_back(c);
            pts.push_back(d);
            pts.push_back(e);
            q.push(std::make_pair(c, e));
            q.push(std::make_pair(e, d));
        }
    }
    std::sort(pts.begin(), pts.end(), cmp_pts);
}

int main()
{
    int i, c = 0;
    double t;
    line_t l;
    while(scanf("%lf%lf%lf%lf%lf", &l.first.x, &l.first.y, &l.second.x, &l.second.y, &t) != EOF)
    {
        if(t <= 1.0-EPS)
            break;
        solve(l, t);
        printf("Case %d:\n%lu\n", ++c, pts.size());
        for(i = 0; i < pts.size(); i++)
            printf("%.5f %.5f\n", pts[i].x, pts[i].y);
    }
    return 0;
}

