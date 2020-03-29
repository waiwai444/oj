#include <cstdio>

using namespace std;

int main()
{
    int i, ans, n, k, m;
    while(scanf("%d%d%d", &n, &k, &m), n)
    {
        ans = 0;
        for(int i = 2; i < n; i++)
            ans = (ans+k)%i;
        ans = (m+ans)%n+1;
        printf("%d\n", ans);
    }
    return 0;
}

