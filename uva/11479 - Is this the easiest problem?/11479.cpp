#include <cstdio>

int main()
{
    int i, tc, a, b, c;
    std::scanf("%d", &tc);
    for(i = 1; i <= tc; ++i)
    {
        std::scanf("%d%d%d", &a, &b, &c);
        std::printf("Case %d: ", i);
        if(a <= 0 || b <= 0 || c <= 0 || (long long)a+b <= c || (long long)a+c <= b || (long long)b+c <= a)
            std::puts("Invalid");
        else if(a == b && a == c)
            std::puts("Equilateral");
        else if(a == b || a == c || b == c)
            std::puts("Isosceles");
        else
            std::puts("Scalene");
    }
    return 0;
}
