#include <cstdio>

#define EPS (1e-9)

int main()
{
    int i, j, m, k;
    double d, l, p, r, t, v;
    while(std::scanf("%d%lf%lf%d", &m, &d, &l, &k) != EOF)
    {
        if(m < 0)
            break;
        p = l/m;
        v = l+d;
        l += p;
        i = 0;
        r = 0;
        while(k--)
        {
            std::scanf("%d%lf", &j, &t);
            while(i < j && (i == 0 || v <= l+EPS))
            {
                l -= p;
                v *= 1-r;
                ++i;
            }
            r = t;
        }
        while(i == 0 || v <= l+EPS)
        {
            l -= p;
            v *= 1-r;
            ++i;
        }
        if(i-1 == 1)
            std::printf("%d month\n", i-1);
        else
            std::printf("%d months\n", i-1);
    }
    return 0;
}
