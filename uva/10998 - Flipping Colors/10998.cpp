#include <cstdio>

double h, v;

char solve(double x0, double y0, double x1, double y1, double x, double y, char color)
{
    double xm = x0+(x1-x0)*h;
    double ym = y0+(y1-y0)*v;
    if(x <= xm && y >= ym || x >= xm && y <= ym)
        return color;
    if(x < xm && y < ym)
        return solve(x0, y0, xm, ym, x, y, 1-color);
    else
        return solve(xm, ym, x1, y1, x, y, 1-color);
}

int main()
{
    int c = 0, i, n;
    double length, height, x, y;
    while(scanf("%lf%lf%lf%lf", &length, &height, &h, &v))
    {
        if(length == 0.0)
            break;
        scanf("%d", &n);
        printf("Case %d:\n", ++c);
        for(i = 0; i < n; i++)
        {
            scanf("%lf%lf", &x, &y);
            if(solve(0.0, 0.0, length, height, x, y, 0) == 0)
                printf("black\n");
            else
                printf("white\n");
        }
    }
    return 0;
}

