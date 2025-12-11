#include <algorithm>
#include <stdio.h>
#include <unordered_map>

int m, n;
int obj[128];
std::unordered_map<int, int> dp[1<<11];

void traverse(int mask, int cur, const int *obj_idx, int obj_cnt)
{
    int i, j, min = 20;
    if(obj_cnt == 1)
    {
        dp[mask][cur] = 0;
        return;
    }
    int o0[128], o1[128], sz0, sz1;
    for(i = m-1; i >= 0; --i)
    {
        if(mask&(1<<i))
            continue;
        int k = mask|(1<<i);
        bool b0 = dp[k].find(cur) == dp[k].end(), b1 = dp[k].find(cur|(1<<i)) == dp[k].end();
        if(b0 || b1)
        {
            sz0 = sz1 = 0;
            for(j = 0; j < obj_cnt; ++j)
            {
                if(obj[obj_idx[j]]&(1<<i))
                    o1[sz1++] = obj_idx[j];
                else
                    o0[sz0++] = obj_idx[j];
            }
            if(sz0 == 0 || sz1 == 0)
                continue;
            if(b0)
                traverse(k, cur, o0, sz0);
            if(b1)
                traverse(k, cur|(1<<i), o1, sz1);
        }
        min = std::min(min, std::max(dp[k][cur], dp[k][cur|(1<<i)])+1);
        if((1<<min) <= obj_cnt)
            break;
    }
    dp[mask][cur] = min;
}

int main()
{
    int i;
    char s[12];
    int idx[128];
    while(scanf("%d%d", &m, &n) && m)
    {
        for(i = 0; i < n; ++i)
        {
            scanf("%s", s);
            obj[i] = 0;
            for(char *p = s; *p; ++p)
                obj[i] = (obj[i]<<1)|(*p-'0');
            idx[i] = i;
        }
        for(i = 0; i < (1<<m); ++i)
            dp[i].clear();
        traverse(0, 0, idx, n);
        printf("%d\n", dp[0][0]);
    }
    return 0;
}
