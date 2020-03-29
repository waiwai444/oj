#include <cstdio>

int count_one(int m)
{
    int r = 0;
    while(m)
    {
        m &= m-1;
        ++r;
    }
    return r;
}

int main()
{
    int n, m, b1, b2;
    std::scanf("%d", &n);
    while(n--)
    {
        std::scanf("%d", &m);
        b1 = count_one(m);
        b2 = 0;
        while(m)
        {
            b2 += count_one(m%10);
            m /= 10;
        }
        std::printf("%d %d\n", b1, b2);
    }
    return 0;
}
