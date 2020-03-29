#include <cstdio>
#include <vector>
#include <algorithm>

struct epinfo_t
{
    double x;
    double r;
    bool in;
};

std::vector<epinfo_t> ep;

bool cmp_ep(const epinfo_t &e1, const epinfo_t &e2)
{
    return e1.x < e2.x;
}

int main()
{
    int i, c, nl;
    double x1, x2, r, t, nz;
    epinfo_t e;
    scanf("%d", &c);
    while(c--)
    {
        ep.clear();
        scanf("%d", &nl);
        for(i = 0; i < nl; i++)
        {
            scanf("%lf%*lf%lf%*lf%lf", &x1, &x2, &r);
            if(x1 > x2)
                std::swap(x1, x2);
            e.x = x1, e.r = r, e.in = true;
            ep.push_back(e);
            e.x = x2, e.in = false;
            ep.push_back(e);
        }
        std::sort(ep.begin(), ep.end(), cmp_ep);
        t = nz = 1.0;
        printf("%lu\n-inf ", ep.size()+1);
        for(i = 0; i < ep.size(); i++)
        {
            printf("%.3f %.3f\n%.3f ", ep[i].x, t, ep[i].x);
            if(ep[i].in)
            {
                t *= ep[i].r;
                if(ep[i].r != 0)
                    nz *= ep[i].r;
            }
            else
            {
                if(ep[i].r != 0)
                {
                    t /= ep[i].r;
                    nz /= ep[i].r;
                }
                else
                    t = nz;
            }
        }
        printf("+inf 1.000\n");
        if(c)
            printf("\n");
    }
    return 0;
}

