#include <cstdio>

int main()
{
    int n, k, b, ans;
    while(std::scanf("%d%d", &n, &k) != EOF)
    {
        ans = b = 0;
        while(n)
        {
            ans += n;
            b += n;
            n = b/k;
            b = b%k;
        }
        std::printf("%d\n", ans);
    }
    return 0;
}
