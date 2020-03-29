#include <cstdio>

int main()
{
    int n, m, p;
    while(std::scanf("%d", &n) != EOF && n)
    {
        m = 1<<30;
        p = 0;
        while(m && (n&m) == 0)
            m >>= 1;
        std::printf("The parity of ");
        while(m)
        {
            if(n&m)
            {
                std::putchar('1');
                ++p;
            }
            else
                std::putchar('0');
            m >>= 1;
        }
        std::printf(" is %d (mod 2).\n", p);
    }
    return 0;
}
