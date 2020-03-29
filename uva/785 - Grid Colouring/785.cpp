#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>

int n;
char grid[51][110];
bool vis[50][100];
char cch;
std::queue<std::pair<int, int> > q;

const int dx[4] = { -1, 0, 0, 1 };
const int dy[4] = { 0, -1, 1, 0 };

inline void rm_newline(char *str)
{
    int len = strlen(str);
    while(len > 0 && (str[len-1] == '\n' || str[len-1] == '\r'))
        str[--len] = 0;
}

inline bool valid_pos(int r, int c)
{
    return r >= 0 && c >= 0 && r < n && c < 100 && grid[r][c];
}

void find_contour_ch()
{
    cch = 0;
    for(int i = 0; i < n; i++)
    {
        for(char *p = grid[i]; *p; ++p)
        {
            if(*p != ' ')
            {
                cch = *p;
                return;
            }
        }
    }
}

void colour(int sr, int sc, char ch)
{
    int i, r, c;
    std::pair<int, int> p;
    q.push(std::make_pair(sr, sc));
    grid[sr][sc] = ch;
    while(!q.empty())
    {
        p = q.front(), q.pop();
        vis[sr][sc] = true;
        for(i = 0; i < 4; i++)
        {
            r = p.first+dx[i], c = p.second+dy[i];
            if(!valid_pos(r, c) || grid[r][c] != ' ')
                continue;
            grid[r][c] = ch;
            q.push(std::make_pair(r, c));
        }
    }
}

void solve()
{
    int i, j;
    char *p;
    memset(vis, false, sizeof(vis));
    find_contour_ch();
    for(i = 0; i < n; i++)
    {
        for(j = 0, p = grid[i]; *p; j++, p++)
        {
            if(*p != ' ' && *p != cch && !vis[i][j])
            {
                colour(i, j, *p);
            }
        }
    }
}

void print_ans()
{
    for(int i = 0; i < n; i++)
        puts(grid[i]);
    puts(grid[n]);
}

int main()
{
    for(;;)
    {
        n = 0;
        memset(grid, 0, sizeof(grid));
        if(!fgets(grid[0], sizeof(grid[0]), stdin))
            break;
        rm_newline(grid[0]);
        if(grid[0][0] != '_')
        {
            ++n;
            while(fgets(grid[n], sizeof(grid[n]), stdin))
            {
                rm_newline(grid[n]);
                if(grid[n++][0] == '_')
                    break;
            }
            --n;
            solve();
        }
        print_ans();
    }
    return 0;
}

