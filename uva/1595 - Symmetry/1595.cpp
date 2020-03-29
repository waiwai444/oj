#include <cstdio>
#include <vector>
#include <algorithm>

std::vector<int> v[20001];

int main()
{
    int i, j, n, tc, x, y, miny, maxy, midx;
    bool ans;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d", &n);
        miny = 10000, maxy = -10000;
        while(n--)
        {
            scanf("%d%d", &x, &y);
            if(y < miny) miny = y;
            if(y > maxy) maxy = y;
            v[y+10000].push_back(x*2);
        }
        miny += 10000, maxy += 10000;
        ans = true;
        std::sort(v[miny].begin(), v[miny].end());
        midx = (v[miny][0]+v[miny][v[miny].size()-1])/2;
        for(i = 1, j = v[miny].size()-2; i <= j; i++, j--)
        {
            if((v[miny][i]+v[miny][j])/2 != midx)
            {
                ans = false;
                break;
            }
        }
        if(ans)
        {
            for(y = miny+1; y <= maxy; y++)
            {
                if(v[y].size() == 0) continue;
                std::sort(v[y].begin(), v[y].end());
                for(i = 0, j = v[y].size()-1; i <= j; i++, j--)
                {
                    if((v[y][i]+v[y][j])/2 != midx)
                    {
                        ans = false;
                        break;
                    }
                }
                if(!ans)
                    break;
            }
        }
        if(ans)
            printf("YES\n");
        else
            printf("NO\n");
        for(y = miny; y <= maxy; y++)
            if(v[y].size())
                v[y].clear();
    }
    return 0;
}

