#include <stdio.h>

#define PI 3.14159265358979
#define EPS 1e-4

int n, f;
double pie_vol[10000];

bool feasible(double share)
{
    int i, r = f;
    for(i = 0; i < n; i++)
    {
        r -= (int)(pie_vol[i]/share);
        if(r <= 0)
            return true;;
    }
    return false;
}

int main()
{
    int i, tc, rad;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d%d", &n, &f);
        ++f;
        double total_vol = 0, lb = EPS, ub, cur, pre;
        for(i = 0; i < n; i++)
        {
            scanf("%d", &rad);
            pie_vol[i] = rad*rad*PI;
            total_vol += pie_vol[i];
        }
        
        ub = total_vol/f;
        pre = lb;
        while(ub-lb >= EPS)
        {
            cur = (ub+lb)/2;
            if(feasible(cur))
                lb = pre = cur;
            else
                ub = cur;
        }
        
        printf("%.4lf\n", pre);
    }
    return 0;
}