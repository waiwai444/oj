#include <cstdio>
#include <cstring>
#include <algorithm>

int n, ng;
char map[20][21];
char ans[20][20];

bool dfs(int r, int c, int g)
{
    int i, j, h, w, mw, sz;
    for(h = 1; h <= 9 && h <= n-r; ++h)
    {
        mw = std::min(9/h, n-c);
        w = sz = 0;
        for(j = c; j < c+mw; ++j)
        {
            w = j-c+1;
            for(i = r; i < r+h; ++i)
            {
                if(ans[i][j] || (sz > 0 && map[i][j] != '.'))
                {
                    sz = -1;
                    break;
                }
                else if(map[i][j] != '.')
                    sz = map[i][j]-'0';
            }
            if(sz && w*h >= sz)
                break;
        }
        if(sz == w*h)
        {
            for(i = r; i < r+h; ++i)
                std::memset(&ans[i][c], 'A'+g, w);
            for(i = r; i < n; ++i)
            {
                for(j = 0; j < n; ++j)
                {
                    if(!ans[i][j])
                    {
                        if(dfs(i, j, g+1))
                            return true;
                        break;
                    }
                }
                if(j < n)
                    break;
            }
            if(i >= n)
                return true;
            for(i = r; i < r+h; ++i)
                std::memset(&ans[i][c], 0, w);
        }
    }
    return false;
}

int main()
{
    int i;
    while(std::scanf("%d%d", &n, &ng) && n)
    {
        std::fgets(map[0], sizeof(map[0]), stdin);
        for(i = 0; i < n; ++i)
            std::fgets(map[i], sizeof(map[i]), stdin);
        std::memset(ans, 0, sizeof(ans));
        dfs(0, 0, 0);
        for(int i = 0; i < n; ++i)
            std::puts(ans[i]);
    }
    return 0;
}
