#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

int n, m;
char grid[26][30];
std::queue<std::pair<int, int> > q;

const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

void rm_newline(char *str)
{
    int l = strlen(str);
    while(l > 0 && (str[l-1] == '\n' || str[l-1] == '\r'))
        str[--l] = 0;
}

inline bool valid_pos(int r, int c)
{
    return r >= 0 && r < n && c >= 0 && c < m;
}

int bfs(int sr, int sc)
{
    int i, r, c, ret = 1;
    std::pair<int, int> p;
    q.push(std::make_pair(sr, sc));
    grid[sr][sc] = '0';
    while(!q.empty())
    {
        p = q.front(), q.pop();
        for(i = 0; i < 8; i++)
        {
            r = p.first+dx[i], c = p.second+dy[i];
            if(!valid_pos(r, c) || grid[r][c] != '1')
                continue;
            ++ret;
            grid[r][c] = '0';
            q.push(std::make_pair(r, c));
        }
    }
    return ret;
}

int solve()
{
    int i, j, t, ans = 0;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            if(grid[i][j] != '1')
                continue;
            t = bfs(i, j);
            if(t > ans)
                ans = t;
        }
    }
    return ans;
}

int main()
{
    int tc;
    scanf("%d", &tc);
    fgets(grid[0], sizeof(grid[0]), stdin);
    fgets(grid[0], sizeof(grid[0]), stdin);
    while(tc--)
    {
        n = m = 0;
        while(fgets(grid[n], sizeof(grid[n]), stdin))
        {
            rm_newline(grid[n]);
            if(grid[n][0] == 0)
                break;
            if(m == 0)
                m = strlen(grid[n]);
            ++n;
        }
        printf("%d\n", solve());
        if(tc)
            printf("\n");
    }
    return 0;
}

