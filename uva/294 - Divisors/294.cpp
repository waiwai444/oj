#include <cstdio>

char flag[32000];
int np, prime[32000];

void init()
{
    int i, j;
    flag[2] = 1;
    for(i = 3; i < 32000; i += 2)
        flag[i] = 1;
    for(i = 3; i < 16000; i += 2)
        if(flag[i])
            for(j = i+i; j < 32000; j += i)
                if(flag[j])
                    flag[j] = 0;
    prime[np++] = 2;
    for(i = 3; i < 32000; i += 2)
        if(flag[i])
            prime[np++] = i;
}

int count_divisors(int x)
{
    int i, c = 1;
    for(i = 0; i < np && x > 1; ++i)
    {
        int t = 1;
        while(x%prime[i] == 0)
            x /= prime[i], ++t;
        c *= t;
    }
    return c;
}

int main()
{
    int i, n, l, u, p, d;
    init();
    std::scanf("%d", &n);
    while(n--)
    {
        std::scanf("%d%d", &l, &u);
        d = 0;
        for(i = l; i <= u; ++i)
        {
            int c = count_divisors(i);
            if(c > d)
                d = c, p = i;
        }
        std::printf("Between %d and %d, %d has a maximum of %d divisors.\n", l, u, p, d);
    }
    return 0;
}
