#include <cstdio>

int digit_sum(int n)
{
    int s = 0;
    while(n)
        s += n%10, n /= 10;
    return s;
}

int main()
{
    int n;
    while(std::scanf("%d", &n) != EOF)
    {
        if(n == 0)
            break;
        while(n >= 10)
            n = digit_sum(n);
        std::printf("%d\n", n);
    }
    return 0;
}
