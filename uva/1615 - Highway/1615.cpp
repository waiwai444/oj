#include <algorithm>
#include <math.h>
#include <stdio.h>
#include <vector>

int L, D, N;
struct loc_t
{
    double x, y;
    double l, r;
};
std::vector<loc_t> loc;

bool cmp(loc_t &l1, loc_t &l2)
{
    return l1.r < l2.r;
}

int main()
{
    int i;
    loc_t l;
    while(scanf("%d%d%d", &L, &D, &N) != EOF)
    {
        loc.clear();
        int d2 = D*D;
        for(i = 0; i < N; ++i)
        {
            scanf("%lf%lf", &l.x, &l.y);
            double t = sqrt(d2-l.y*l.y);
            l.l = l.x-t < 0 ? 0 : l.x-t;
            l.r = l.x+t > L ? L : l.x+t;
            loc.push_back(l);
        }

        sort(loc.begin(), loc.end(), cmp);

        int ans = 0;
        double exit = -1;
        for(std::vector<loc_t>::iterator it = loc.begin(); it != loc.end(); ++it)
        {
            if(exit < 0 || it->l > exit)
            {
                ++ans;
                exit = it->r;
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}
