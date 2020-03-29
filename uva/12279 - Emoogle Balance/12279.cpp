#include <cstdio>

int main()
{
    int n, i, tc = 0, ans;
    while(std::scanf("%d", &n) != EOF && n)
    {
        ans = 0;
        while(n--)
        {
            std::scanf("%d", &i);
            i ? ++ans : --ans;
        }
        std::printf("Case %d: %d\n", ++tc, ans);
    }
    return 0;
}
