#include <algorithm>
#include <stdio.h>
#include <string.h>

int m, k;
char ge[310][310];
int idx[310];
char vis[310];

bool cmp(int x, int y)
{
    for(int i = 0; i < m; ++i)
        if(ge[x][i] != ge[y][i])
            return ge[x][i];
        else if(ge[x][i] == 1)
            return false;
    return false;
}

bool solve()
{
    int i, j, k;
    for(i = 0; i < m; ++i)
    {
        idx[i] = i;
        vis[i] = 0;
    }
    std::sort(idx, idx + m, cmp);
    for(i = j = 0; i < m - 1; ++i)
    {
        while(ge[idx[i]][j] == 0 && j < m)
            ++j;
        if(j == m)
            return true;
        if(vis[j])
            return false;
        if(ge[idx[i]][j] == ge[idx[i + 1]][j])
        {
            for(k = j + 1; k < m; ++k)
            {
                if(ge[idx[i]][k] != ge[idx[i + 1]][k])
                    return false;
                if(ge[idx[i]][k] && vis[k])
                    return false;
            }
        }
        else
        {
            for(k = 0; k < m; ++k)
                if(ge[idx[i]][k])
                    vis[k] = 1;
        }
    }
    return true;
}

int main()
{
    int i, c, N, x, y;
    bool ans;
    scanf("%d", &N);
    for(c = 1; c <= N; ++c)
    {
        scanf("%d%d", &m, &k);
        memset(ge, 0, sizeof(ge));
        ans = true;
        for(i = 0; i < k; ++i)
        {
            scanf("%d%d", &x, &y);
            if(ge[x][y] == 1)
                ans = false;
            ge[x][y] = 1;
        }
        if(ans)
            ans = solve();
        printf("Case #%d: %s\n", c, ans ? "Yes" : "No");
    }
    return 0;
}
