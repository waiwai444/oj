#include <cstdio>

int main()
{
    int x;
    while(std::scanf("%d", &x) != EOF)
    {
        unsigned long long tmp = (unsigned long long)x+1;
        tmp *= tmp;
        tmp -= (unsigned long long)x+1;
        tmp *= tmp;
        std::printf("%lld\n", tmp/4);
    }
    return 0;
}
