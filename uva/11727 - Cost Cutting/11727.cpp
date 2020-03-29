#include <cstdio>

int main()
{
    int i, t, x, y, z, m;
    std::scanf("%d", &t);
    for(i = 1; i <= t; ++i)
    {
        std::scanf("%d%d%d", &x, &y, &z);
        if(x < y)
        {
            if(y < z)
                m = y;
            else if(z < x)
                m = x;
            else
                m = z;
        }
        else
        {
            if(x < z)
                m = x;
            else if(z < y)
                m = y;
            else
                m = z;
        }
        std::printf("Case %d: %d\n", i, m);
    }
    return 0;
}

