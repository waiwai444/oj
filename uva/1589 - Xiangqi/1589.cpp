#include <cstdio>
#include <cstring>

int n;
int rb, cb;

char board[10][9];
const int dr[] = { -1, 0, 0, 1 };
const int dc[] = { 0, -1, 1, 0 };
const int hr[] = { -2, -2, -1, -1, 1, 1, 2, 2 };
const int hc[] = { -1, 1, -2, 2, -2, 2, -1, 1 };
const int lr[] = { -1, -1, -1, -1, 1, 1, 1, 1 };
const int lc[] = { -1, 1, -1, 1, -1, 1, -1, 1 };

bool check_row(int r, int c)
{
    int i, ret;
    bool m = false;
    for(i = c-1; i >= 0; i--)
    {
        if(board[r][i] == 0)
            continue;
        if(!m)
        {
            if(board[r][i] == 'R')
                return true;
            m = true;
        }
        else
        {
            if(board[r][i] == 'C')
                return true;
            break;
        }
    }
    m = false;
    for(i = c+1; i < 9; i++)
    {
        if(board[r][i] == 0)
            continue;
        if(!m)
        {
            if(board[r][i] == 'R')
                return true;
            m = true;
        }
        else
        {
            if(board[r][i] == 'C')
                return true;
            break;
        }
    }
    return false;
}

bool check_col(int r, int c)
{
    int i;
    bool m = false;
    for(i = r-1; i >= 0; i--)
    {
        if(board[i][c] == 0)
            continue;
        if(!m)
        {
            if(board[i][c] == 'R')
                return true;
            m = true;
        }
        else
        {
            if(board[i][c] == 'C')
                return true;
            break;
        }
    }
    m = false;
    for(i = r+1; i < 10; i++)
    {
        if(board[i][c] == 0)
            continue;
        if(!m)
        {
            if(board[i][c] == 'R' || board[i][c] == 'G')
                return true;
            m = true;
        }
        else
        {
            if(board[i][c] == 'C')
                return true;
            break;
        }
    }
    return false;
}

bool check_h(int r, int c)
{
    int i, x, y;
    for(i = 0; i < 8; i++)
    {
        x = r+lr[i], y = c+lc[i];
        if(x < 0 || board[x][y])
            continue;
        x = r+hr[i], y = c+hc[i];
        if(x >= 0 && board[x][y] == 'H')
            return true;
    }
    return false;
}

bool checkmate()
{
    int i, r, c;
    for(i = 0; i < 4; i++)
    {
        r = rb+dr[i], c = cb+dc[i];
        if(r < 0 || r > 2 || c < 3 || c > 5)
            continue;
        if(check_row(r, c))
            continue;
        if(check_col(r, c))
            continue;
        if(check_h(r, c))
            continue;
        break;
    }
    return i == 4;
}

int main()
{
    int i, r, c;
    char type[2];
    while(scanf("%d%d%d", &n, &rb, &cb), rb && cb)
    {
        --rb, --cb;
        memset(board, 0, sizeof(board));
        for(i = 0; i < n; i++)
        {
            scanf("%s%d%d", type, &r, &c);
            board[r-1][c-1] = type[0];
        }
        if(checkmate())
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}

