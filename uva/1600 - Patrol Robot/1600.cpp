#include <cstdio>

int m, n, k;
int grid[20][20];

struct status_t
{
    int r, c, d, t;
};

status_t q[8500];
int front, back;
int tb[20][20];
const int dx[4] = { -1, 1, 0, 0 };
const int dy[4] = { 0, 0, -1, 1 };

int solve()
{
    int i, j, x, y;
    for(i = 0; i < m; ++i)
        for(j = 0; j < n; ++j)
            tb[i][j] = 99;
    front = back = 0;
    status_t &s = q[back++];
    s.r = s.c = s.d = s.t = tb[0][0] = 0;
    while(back > front)
    {
        status_t &s = q[front++];
        for(i = 0; i < 4; ++i)
        {
            x = s.r+dx[i], y = s.c+dy[i];
            if(x < 0 || x >= m || y < 0 || y >= n)
                continue;
            if(x == m-1 && y == n-1)
                return s.d+1;
            status_t &s2 = q[back];
            if(grid[x][y] == 1)
            {
                if(s.t == k)
                    continue;
                s2.t = s.t+1;
            }
            else
                s2.t = 0;
            if(tb[x][y] > s2.t)
            {
                tb[x][y] = s2.t;
                s2.r = x, s2.c = y, s2.d = s.d+1;
                ++back;
            }
        }
    }
    return -1;
}

int main()
{
    int tc, i, j;
    std::scanf("%d", &tc);
    while(tc--)
    {
        std::scanf("%d%d%d", &m, &n, &k);
        for(i = 0; i < m; ++i)
            for(j = 0; j < n; ++j)
                std::scanf("%d", &grid[i][j]);
        std::printf("%d\n", solve());
    }
    return 0;
}

