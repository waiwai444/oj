#include <cstdio>

int main()
{
    int n, ans;
    while(std::scanf("%d", &n), n)
    {
        ans = n >= 101 ? n-10 : 91;
        std::printf("f91(%d) = %d\n", n, ans);
    }
    return 0;
}
