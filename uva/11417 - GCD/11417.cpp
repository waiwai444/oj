#include <cstdio>

int sum[501];

int gcd(int x, int y)
{
    return y == 0 ? x : gcd(y, x%y);
}

void get_sum()
{
    sum[1] = 0;
    for(int i = 2; i <= 500; ++i)
    {
        sum[i] = sum[i-1];
        for(int j = 1; j < i; ++j)
            sum[i] += gcd(j, i);
    }
}

int main()
{
    int n;
    get_sum();
    while(std::scanf("%d", &n) != EOF && n)
        std::printf("%d\n", sum[n]);
    return 0;
}
