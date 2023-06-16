#include <algorithm>
#include <stdio.h>
#include <vector>

int n;
int m[1024][1024];
std::vector<int> s[1024];
int s_idx[1024], s_cnt;
std::vector<int> res;

bool cmp(int i, int j)
{
    return s[i].size() > s[j].size();
}

void solve()
{
    int i, j, k;
    res.clear();
    res.reserve((n-1)*2);
    for(i = 1, s_cnt = 0; i < n; ++i)
        if(s[i].size())
            s_idx[s_cnt++] = i;
    std::sort(s_idx, &s_idx[s_cnt], cmp);
    for(i = 0, j = 1; i < s_cnt; ++i)
    {
        res.push_back(s_idx[i]);
        for(k = 0; k < s[s_idx[i]].size(); ++k)
            res.push_back(s[s_idx[i]][k]);
        ++k;
        while((k-1)&k)
        {
            while(m[0][j] == 0 || s[j].size() > 0)
                ++j;
            res.push_back(j++);
            ++k;
        }
    }
    for(; j < n; ++j)
        if(m[0][j] == 1 && s[j].size() == 0)
            res.push_back(j);
    res.push_back(0);
    for(i = res.size(), j = 0; i < (n-1)*2; ++i, j += 2)
        res.push_back(m[res[j]][res[j+1]] == 1 ? res[j] : res[j+1]);
}

int main()
{
    int i, j;
    char line[1030];
    while(scanf("%d", &n) != EOF)
    {
        fgets(line, 1030, stdin);
        for(i = 1; i < n; ++i)
            s[i].clear();
        for(i = 0; i < n; ++i)
        {
            fgets(line, 1030, stdin);
            m[i][0] = line[0]-'0';
            bool f = m[i][0] == 1;
            for(j = 1; j < n; ++j)
            {
                m[i][j] = line[j]-'0';
                if(f && m[i][j] == 0 && m[0][j] == 1)
                {
                    s[j].push_back(i);
                    f = false;
                }
            }
        }
        solve();
        for(i = 0; i < res.size(); i += 2)
            printf("%d %d\n", res[i]+1, res[i+1]+1);
    }
    return 0;
}