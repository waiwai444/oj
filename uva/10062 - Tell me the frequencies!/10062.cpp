#include <algorithm>
#include <iostream>
#include <string.h>

int cnt[128];
int idx[128];

bool cmp(int i, int j)
{
    if(cnt[i] < cnt[j])
        return true;
    if(cnt[i] > cnt[j])
        return false;
    return i > j;
}

int main()
{
    int i, n;
    bool first = true;
    std::string line;
    std::ios_base::sync_with_stdio(false);
    line.reserve(1005);
    while(std::getline(std::cin, line))
    {
        memset(cnt, 0, sizeof(cnt));
        for(char ch : line)
            ++cnt[ch];
        for(i = 32, n = 0; i < 128; ++i)
        {
            if(cnt[i] > 0)
                idx[n++] = i;
        }
        std::sort(idx, idx+n, cmp);
        if(first)
            first = false;
        else
            std::cout << '\n';
        for(i = 0; i < n; ++i)
            std::cout << idx[i] << ' ' << cnt[idx[i]] << '\n';
    }
    return 0;
}
