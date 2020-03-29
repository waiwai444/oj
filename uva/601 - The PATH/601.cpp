#include <cstdio>
#include <queue>
#include <utility>

int n;
char board[82][82];
std::queue<std::pair<int, int> > q;

#define LEFT 'Z'
#define RIGHT 'Y'
#define TOP 'S'
#define BOTTOM 'X'

const int dx[4] = { -1, 0, 0, 1 };
const int dy[4] = { 0, -1, 1, 0 };

void bfs(char color, char tag, int r, int c)
{
    int i, u, v;
    std::pair<int, int> p;
    q.push(std::make_pair(r, c));
    board[r][c] = tag;
    while(!q.empty())
    {
        p = q.front(), q.pop();
        for(i = 0; i < 4; i++)
        {
            u = p.first+dx[i], v = p.second+dy[i];
            if(u < 0 || u >= n || v < 0 || v >= n)
                continue;
            if(board[u][v] != color)
                continue;
            board[u][v] = tag;
            q.push(std::make_pair(u, v));
        }
    }
}

void white_from_left()
{
    for(int i = 0; i < n; i++)
        if(board[i][0] == 'W')
            bfs('W', LEFT, i, 0);
}

void white_from_right()
{
    for(int i = 0; i < n; i++)
        if(board[i][n-1] == 'W')
            bfs('W', RIGHT, i, n-1);
}

void black_from_top()
{
    for(int i = 0; i < n; i++)
        if(board[0][i] == 'B')
            bfs('B', TOP, 0, i);
}

void black_from_bottom()
{
    for(int i = 0; i < n; i++)
        if(board[n-1][i] == 'B')
            bfs('B', BOTTOM, n-1, i);
}

void solve()
{
    int i, j;
    white_from_left();
    for(i = 0; i < n; i++)
    {
        if(board[i][n-1] == LEFT)
        {
            printf("White has a winning path.\n");
            return;
        }
    }
    black_from_top();
    for(i = 0; i < n; i++)
    {
        if(board[n-1][i] == TOP)
        {
            printf("Black has a winning path.\n");
            return;
        }
    }
    white_from_right();
    black_from_bottom();
    bool b = false;
    char u, d, l, r;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(board[i][j] != 'U')
                continue;
            l = j > 0 ? board[i][j-1] : LEFT;
            r = j < n-1 ? board[i][j+1] : RIGHT;
            u = i > 0 ? board[i-1][j] : TOP;
            d = i < n-1 ? board[i+1][j] : BOTTOM;
            if((l == LEFT || r == LEFT || u == LEFT || d == LEFT)
                    && (l == RIGHT || r == RIGHT || u == RIGHT || d == RIGHT))
            {
                printf("White can win in one move.\n");
                return;
            }
            if((l == TOP || r == TOP || u == TOP || d == TOP)
                    && (l == BOTTOM || r == BOTTOM || u == BOTTOM || d == BOTTOM))
                b = true;
        }
    }
    if(b)
        printf("Black can win in one move.\n");
    else
        printf("There is no winning path.\n");
}

int main()
{
    int i;
    while(scanf("%d", &n), n)
    {
        for(i = 0; i < n; i++)
            scanf("%s", board[i]);
        solve();
    }
    return 0;
}

