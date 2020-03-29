#include <cstdio>
#include <algorithm>

int m, n;
int e[900], w;

int main()
{
    int i, j, k, a, tc = 0;
    double h;
    while(scanf("%d%d", &m, &n), m)
    {
        for(i = k = 0; i < m; i++)
            for(j = 0; j < n; j++)
                scanf("%d", &e[k++]);
        scanf("%d", &w);
        std::sort(&e[0], &e[k]);
        h = 0.0;
        for(i = 0; i < k; i++)
        {
            if(w == 0)
                break;
            if(i < k-1 && e[i] == e[i+1])
                continue;
            a = 100*(i+1);
            if(i < k-1 && a*(e[i+1]-e[i]) <= w)
            {
                h = e[i+1];
                w -= a*(e[i+1]-e[i]);
            }
            else
            {
                h = e[i]+w/(double)((i+1)*100);
                w = 0;
            }
        }
        printf("Region %d\n", ++tc);
        printf("Water level is %.2f meters.\n", h);
        printf("%.2f percent of the region is under water.\n\n", (double)i/k*100);
    }
    return 0;
}

