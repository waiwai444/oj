#include <cstdio>
#include <cstring>
#include <utility>

int n;
char grid[7][8];
int vtx[8][8];
std::pair<int, int> par[8][8];

#define PARENT(x) par[x.first][x.second]

std::pair<int, int> find_repr(std::pair<int, int> x)
{
    std::pair<int, int> px = PARENT(x);
    while(px != x)
        x = px, px = PARENT(x);
    return px;
}

bool dfs(int r, int c)
{
    if(r == n+1)
        return true;

    int nr = r, nc = c+1;
    if(nc == n+1)
        nr = r+1, nc = 0;

    if(r == n || c == n)
    {
        if(vtx[r][c] > 0)
            return false;
        return dfs(nr, nc);
    }

    if(vtx[r][c] > 1 || (vtx[r][c] == 1 && vtx[r+1][c+1] == 0))
        return false;
    if(vtx[r][c] != 0 && vtx[r+1][c+1] != 0)
    {
        std::pair<int, int> p1, p2, ptmp;
        p1 = find_repr(std::make_pair(r, c));
        p2 = find_repr(std::make_pair(r+1, c+1));
        if(p1 != p2)
        {
            grid[r][c] = '\\';
            --vtx[r][c], --vtx[r+1][c+1];
            ptmp = PARENT(p2), PARENT(p2) = p1;
            if(dfs(nr, nc))
                return true;
            grid[r][c] = 0;
            ++vtx[r][c], ++vtx[r+1][c+1];
            PARENT(p2) = ptmp;
        }
    }
    if(vtx[r][c] != 1 && vtx[r][c+1] != 0 && vtx[r+1][c] != 0)
    {
        std::pair<int, int> p1, p2, ptmp;
        p1 = find_repr(std::make_pair(r, c+1));
        p2 = find_repr(std::make_pair(r+1, c));
        if(p1 != p2)
        {
            grid[r][c] = '/';
            --vtx[r][c+1], --vtx[r+1][c];
            ptmp = PARENT(p2), PARENT(p2) = p1;
            if(dfs(nr, nc))
                return true;
            grid[r][c] = 0;
            ++vtx[r][c+1], ++vtx[r+1][c];
            PARENT(p2) = ptmp;
        }
    }

    return false;
}

void solve()
{
    std::memset(grid, 0, sizeof(grid));
    for(int i = 0; i <= n; ++i)
        for(int j = 0; j <= n; ++j)
            par[i][j] = std::make_pair(i, j);
    dfs(0, 0);
}

int main()
{
    int i, j, tc;
    char line[10];
    std::scanf("%d", &tc);
    while(tc--)
    {
        std::scanf("%d", &n);
        for(i = 0; i <= n; ++i)
        {
            std::scanf("%s", line);
            for(j = 0; line[j]; ++j)
            {
                vtx[i][j] = line[j] == '.' ? -1 : line[j]-'0';
            }
        }
        solve();
        for(i = 0; i < n; ++i)
            std::puts(grid[i]);
    }
    return 0;
}
