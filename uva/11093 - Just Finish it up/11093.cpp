#include <iostream>

int n;
int d[100001];

int solve()
{
    int i, f, ans;
    for(i = 0; i < n;)
    {
        ans = i;
        f = d[i];
        for(++i; f >= 0 && i < n; ++i)
            f += d[i];
    }
    return ans;
}

int main()
{
    int i, j, t, s, k;
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> t;
    for(i = 1; i <= t; ++i)
    {
        std::cin >> n;
        s = 0;
        for(j = 0; j < n; ++j)
            std::cin >> d[j];
        for(j = 0; j < n; ++j)
        {
            std::cin >> k;
            d[j] -= k;
            s += d[j];
        }
        if (s < 0)
            std::cout << "Case " << i << ": Not possible\n";
        else
        {
            int r = solve();
            std::cout << "Case " << i << ": Possible from station " << r+1 << '\n';
        }
    }
    return 0;
}
