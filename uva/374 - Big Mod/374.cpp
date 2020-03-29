#include <cstdio>

int b, p, m;

int main()
{
    int r, t;
    while(std::scanf("%d%d%d", &b, &p, &m) != EOF)
    {
        if(p == 0)
            r = 1%m;
        else
        {
            t = b%m, r = 1;
            while(p)
            {
                if(p&1)
                    r = r*t%m;
                t = t*t%m;
                p /= 2;
            }
        }
        std::printf("%d\n", r);
    }
    return 0;
}
