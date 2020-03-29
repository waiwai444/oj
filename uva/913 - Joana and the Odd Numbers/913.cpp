#include <cstdio>

int main()
{
    int n;
    while(std::scanf("%d", &n) != EOF)
    {
        long long r = n;
        r = 3*(r+1)*(r+1)/2-9;
        std::printf("%lld\n", r);
    }
    return 0;
}
