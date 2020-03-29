#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>

double rw;
int ns;
int weight[6];
std::vector<std::pair<double, double> > range[1<<6];
double wsum[1<<6];

void recur(int subset)
{
    int i, j, lset, rset;
    double cl, cr, l, r;
    bool leaf = true;
    for(lset = (subset-1)&subset; lset; lset = (lset-1)&subset)
    {
        leaf = false;
        rset = subset^lset;
        if(range[lset].size() == 0)
            recur(lset);
        if(range[rset].size() == 0)
            recur(rset);
        cl = -wsum[rset]/(wsum[lset]+wsum[rset]), cr = 1+cl;
        for(i = 0; i < range[lset].size(); ++i)
        {
            for(j = 0; j < range[rset].size(); ++j)
            {
                l = std::min(cl+range[lset][i].first, cr+range[rset][j].first);
                r = std::max(cl+range[lset][i].second, cr+range[rset][j].second);
                if(r-l < rw)
                    range[subset].push_back(std::make_pair(l, r));
            }
        }
    }
    if(leaf)
        range[subset].push_back(std::make_pair(0, 0));
}

double solve()
{
    int i, j, k;
    double ans = -1;
    for(i = 1, k = (1<<ns); i < k; ++i)
    {
        range[i].clear();
        wsum[i] = 0;
        for(j = 0; j < ns; ++j)
            if(i&(1<<j))
                wsum[i] += weight[j];
    }
    k = (1<<ns)-1;
    recur(k);
    for(i = 0; i < range[k].size(); ++i)
        if(range[k][i].second-range[k][i].first > ans)
            ans = range[k][i].second-range[k][i].first;
    return ans;
}

int main()
{
    int i, tc;
    double ans;
    std::scanf("%d", &tc);
    while(tc--)
    {
        std::scanf("%lf%d", &rw, &ns);
        for(i = 0; i < ns; ++i)
            std::scanf("%d", &weight[i]);
        ans = solve();
        if(ans <= -0.9)
            std::printf("-1\n");
        else
            std::printf("%.16f\n", ans);
    }
    return 0;
}

