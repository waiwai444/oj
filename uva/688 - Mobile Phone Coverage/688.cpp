#include <cstdio>
#include <cstring>
#include <algorithm>

int n;
double x[100], y[100], r[100];
double v[200], h[200];
bool in[200][200];

int main()
{
    int i, j, k, tc = 0;
    double sum;
    while(scanf("%d", &n), n)
    {
        for(i = 0; i < n; i++)
        {
            scanf("%lf%lf%lf", &x[i], &y[i], &r[i]);
            v[2*i] = x[i]-r[i], v[2*i+1] = x[i]+r[i];
            h[2*i] = y[i]-r[i], h[2*i+1] = y[i]+r[i];
        }
        std::sort(v, v+2*n);
        std::sort(h, h+2*n);
        memset(in, false, sizeof(in));
        for(k = 0; k < n; k++)
        {
            for(i = 1; i < 2*n; i++)
            {
                if(v[i] <= x[k]-r[k])
                    continue;
                if(v[i-1] >= x[k]+r[k])
                    break;
                for(j = 1; j < 2*n; j++)
                {
                    if(h[j] <= y[k]-r[k])
                        continue;
                    if(h[j-1] >= y[k]+r[k])
                        break;
                    if(!in[i][j])
                        in[i][j] = true;
                }
            }
        }
        sum = 0;
        for(i = 1; i < 2*n; i++)
            for(j = 1; j < 2*n; j++)
                if(in[i][j])
                    sum += (v[i]-v[i-1])*(h[j]-h[j-1]);
        printf("%d %.2f\n", ++tc, sum);
    }
    return 0;
}

