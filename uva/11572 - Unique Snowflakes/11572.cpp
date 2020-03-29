#include <cstdio>
#include <map>

#define MAXN 1000000

int n;
int seq[MAXN];
std::map<int, int> smap[1<<14];

inline int hash(int x)
{
    return x&((1<<14)-1);
}

int solve()
{
    int i, j, h, cnt, ans;
    std::map<int, int>::iterator it;
    cnt = ans = 0;
    for(i = 0; i < (1<<14); i++)
        smap[i].clear();
    for(i = j = 0; i < n; i++)
    {
        h = hash(seq[i]);
        it = smap[h].find(seq[i]);
        if(it == smap[h].end())
        {
            smap[h][seq[i]] = i;
            ++cnt;
        }
        else
        {
            if(cnt > ans)
                ans = cnt;
            cnt -= (it->second-j);
            while(j < it->second)
            {
                h = hash(seq[j]);
                smap[h].erase(seq[j++]);
            }
            j++;
            it->second = i;
        }
    }
    if(cnt > ans)
        ans = cnt;
    return ans;
}

int main()
{
    int i, tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            scanf("%d", &seq[i]);
        printf("%d\n", solve());
    }
    return 0;
}

