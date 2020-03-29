#include <cstdio>

unsigned long m, n;
const unsigned long base[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };

unsigned long solve()
{
    int i;
    unsigned long a, b, c, d, res = 0;
    for(i = 8; i >= 0; i--)
    {
        if(n < base[i+1])
            continue;
        a = m/base[i+1];
        b = n/base[i+1];
        c = m%base[i+1];
        d = n%base[i+1];
        if(a == 0)
        {
            a = 1;
            c = 0;
        }
        res += (b-a+1)*base[i];
        if(c >= base[i])
            res -= base[i];
        else
            res -= c;
        if(d < base[i])
            res -= (base[i]-1-d);
    }
    if(m == 0)
        ++res;
    return res;
}

int main()
{
    long long a, b;
    while(scanf("%lld%lld", &a, &b), a >= 0)
    {
        m = a, n = b;
        printf("%lu\n", solve());
    }
    return 0;
}

