#include <cstdio>
#include <cstring>
#include <cctype>
#include <queue>
#include <utility>

int n, m;
char grid[50][100];
char line[110];

typedef std::pair<int, int> pii;
const int dx[4] = { -1, 0, 0, 1 };
const int dy[4] = { 0, -1, 1, 0 };

inline bool is_contour(int r, int c)
{
    return grid[r][c] != ' ' && grid[r][c] != '*' && grid[r][c] != '#';
}

inline bool valid_pos(int r, int c)
{
    return !(r < 0 || r >= n || c < 0 || c >= m);
}

void mark_area(int sr, int sc)
{
    int i, r, c;
    std::queue<pii> q;
    pii p;
    q.push(std::make_pair(sr, sc));
    grid[sr][sc] = '*';
    while(!q.empty())
    {
        p = q.front(), q.pop();
        for(i = 0; i < 4; i++)
        {
            r = p.first+dx[i], c = p.second+dy[i];
            if(!valid_pos(r, c))
                continue;
            if(grid[r][c] == ' ')
            {
                grid[r][c] = '*';
                q.push(std::make_pair(r, c));
            }
        }
    }
}

void paint()
{
    int i, j, k, r, c;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            if(!is_contour(i, j))
                continue;
            for(k = 0; k < 4; k++)
            {
                r = i+dx[k], c = j+dy[k];
                if(!valid_pos(r, c))
                    continue;
                if(grid[r][c] == '*')
                    grid[r][c] = '#';
            }
        }
    }
}

void solve()
{
    int i, j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
            if(grid[i][j] == '*')
                break;
        if(j < m)
            break;
    }
    if(i >= n)
        return;
    mark_area(i, j);
    paint();
}

void print_ans()
{
    int i, j, k;
    for(i = 0; i < n; i++)
    {
        for(k = m-1; grid[i][k] == ' ' || grid[i][k] == '*'; --k);
        for(j = 0; j <= k; j++)
            putchar(grid[i][j] == '*' ? ' ' : grid[i][j]);
        putchar('\n');
    }
    printf("%s", line);
}

int main()
{
    int tc, i, j, l;
    scanf("%d", &tc);
    fgets(line, sizeof(line), stdin);
    while(tc--)
    {
        n = m = 0;
        memset(grid, ' ', sizeof(grid));
        for(;;)
        {
            fgets(line, sizeof(line), stdin);
            if(line[0] == '_')
                break;
            l = strlen(line);
            while(l > 0 && iscntrl(line[l-1]))
                line[--l] = 0;
            memcpy(grid[n++], line, l);
            if(++l > m)
                m = l;
        }
        solve();
        print_ans();
    }
    return 0;
}

