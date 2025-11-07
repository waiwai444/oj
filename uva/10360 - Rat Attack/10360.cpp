#include <stdio.h>
#include <string.h>

int grid[1025][1025];
int d;

void solve()
{
    int i, j, s, max, mx, my, d2;
    for(i = 0; i < 1025; ++i)
    {
        s = 0;
        for(j = 0; j < 1025; ++j)
        {
            s += grid[i][j];
            grid[i][j] = (i >= 1 ? grid[i - 1][j] : 0) + s;
        }
    }
    max = mx = my = -1;
    d2 = d + d;
    for(i = d; i < 1025; ++i)
    {
        for(j = d; j < 1025; ++j)
        {
            s = grid[i][j] - (i >= d2 + 1 ? grid[i - d2 - 1][j] : 0) - (j >= d2 + 1 ? grid[i][j - d2 - 1] : 0) + (i >= d2 + 1 && j >= d2 + 1 ? grid[i - d2 - 1][j - d2 - 1] : 0);
            if(s > max)
            {
                max = s;
                mx = i;
                my = j;
            }
        }
    }
    printf("%d %d %d\n", mx - d, my - d, max);
}

int main()
{
    int i, n, tc, x, y, sz;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d%d", &d, &n);
        memset(grid, 0, sizeof(grid));
        for(i = 0; i < n; ++i)
        {
            scanf("%d%d%d", &x, &y, &sz);
            grid[x][y] = sz;
        }
        solve();
    }
    return 0;
}
