#include <cstdio>
#include <cstring>
#include <vector>

std::vector<int> fact[101];
int denom[101], num[101];

void get_all_factors()
{
    int i, j, n;
    for(i = 2; i <= 100; ++i)
    {
        n = i;
        for(j = 2; j <= i; ++j)
        {
            while(n%j == 0)
            {
                fact[i].push_back(j);
                n /= j;
            }
        }
    }
}

long combination(int n, int m)
{
    int i, j;
    long c = 1;
    std::memset(denom, 0, sizeof(denom));
    std::memset(num, 0, sizeof(num));
    for(i = n; i > n-m; --i)
        for(j = 0; j < fact[i].size(); ++j)
            ++num[fact[i][j]];
    for(i = m; i > 1; --i)
        for(j = 0; j < fact[i].size(); ++j)
            ++denom[fact[i][j]];
    for(i = 2; i <= n; ++i)
        if(denom[i])
            num[i] -= denom[i];
    for(i = 2; i <= n; ++i)
        while(num[i]--)
            c *= i;
    return c;
}

int main()
{
    int n, m;
    long c;
    get_all_factors();
    while(std::scanf("%d%d", &n, &m) != EOF)
    {
        if(n == 0 && m == 0)
            break;
        c = combination(n, m);
        std::printf("%d things taken %d at a time is %ld exactly.\n", n, m, c);
    }
    return 0;
}
