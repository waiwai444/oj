#include <cstdio>
#include <vector>
#include <utility>

int k;
std::vector<std::pair<int, int> > ans;

int main()
{
    int x, y, i;
    while(std::scanf("%d", &k) != EOF)
    {
        ans.clear();
        i = 2*k;
        for(y = k+1; y <= i; ++y)
        {
            if(k*y%(y-k))
                continue;
            x = k*y/(y-k);
            ans.push_back(std::make_pair(x, y));
        }
        std::printf("%d\n", (int)ans.size());
        for(i = 0; i < ans.size(); ++i)
            std::printf("1/%d = 1/%d + 1/%d\n", k, ans[i].first, ans[i].second);
    }
    return 0;
}

