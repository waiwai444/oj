#include <cstdio>

int main()
{
    int tc, n, r;
    std::scanf("%d", &tc);
    while(tc--)
    {
        std::scanf("%d", &n);
        n = ((n*63+7492)*5-498)/10;
        r = n%10;
        if(r < 0)
            r = -r;
        std::printf("%d\n", r);
    }
    return 0;
}
