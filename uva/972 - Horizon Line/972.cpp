#include <cstdio>
#include <cfloat>
#include <algorithm>

int nf, ng;
double sv_f[100], sl_f[100], sv_g[100], sl_g[100];

int main()
{
    int i, j;
    double xf, xg, h, ans;
    while(scanf("%d", &nf) != EOF)
    {
        for(i = 0; i < nf; i++)
            scanf("%lf%lf", &sv_f[i], &sl_f[i]);
        scanf("%d", &ng);
        for(i = 0; i < ng; i++)
            scanf("%lf%lf", &sv_g[i], &sl_g[i]);
        xf = xg = 0;
        i = j = 0;
        ans = DBL_MAX;
        while(true)
        {
            while(i < nf && xf+sl_f[i] <= xg+sl_g[j])
            {
                h = std::max(sv_f[i], sv_g[j]);
                if(h < ans)
                    ans = h;
                xf += sl_f[i++];
            }
            if(i == nf)
                break;
            while(j < ng && xf+sl_f[i] >= xg+sl_g[j])
            {
                h = std::max(sv_f[i], sv_g[j]);
                if(h < ans)
                    ans = h;
                xg += sl_g[j++];
            }
            if(j == ng)
                break;
        }
        printf("%.3f\n", ans);
    }
    return 0;
}

