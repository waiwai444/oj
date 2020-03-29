#include <cstdio>

char board[8][9];
char cur;
int nb, nw;

const int step[8][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};

inline char get_opponent()
{
    return cur == 'W' ? 'B' : 'W';
}

inline bool valid_pos(int r, int c)
{
    return r >= 0 && r < 8 && c >= 0 && c < 8;
}

void init()
{
    int i, j;
    nb = nw = 0;
    for(i = 0; i < 8; i++)
        for(j = 0; j < 8; j++)
            if(board[i][j] == 'B')
                ++nb;
            else if(board[i][j] == 'W')
                ++nw;
}

void list_moves()
{
    int i, j, k, l, r, c, m = 0;
    char opp = get_opponent();
    bool f, first = true;
    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if(board[i][j] != '-')
                continue;
            f = false;
            for(k = 0; k < 8; k++)
            {
                r = i+step[k][0], c = j+step[k][1];
                if(!valid_pos(r, c) || board[r][c] != opp)
                    continue;
                while(valid_pos(r, c) && board[r][c] == opp)
                    r += step[k][0], c += step[k][1];
                if(valid_pos(r, c) && board[r][c] == cur)
                {
                    f = true;
                    break;
                }
            }
            if(f)
            {
                if(first)
                    first = false, printf("(%d,%d)", i+1, j+1);
                else
                    printf(" (%d,%d)", i+1, j+1);
                ++m;
            }
        }
    }
    if(m == 0)
        puts("No legal move.");
    else
        putchar('\n');
}

void move(int r0, int c0)
{
    int i, j, r, c, d;
    char opp = get_opponent();
    bool f;
    for(i = 0; i < 2; i++)
    {
        f = false;
        for(j = 0; j < 8; j++)
        {
            r = r0+step[j][0], c = c0+step[j][1], d = 0;
            if(!valid_pos(r, c) || board[r][c] != opp)
                continue;
            while(valid_pos(r, c) && board[r][c] == opp)
                r += step[j][0], c += step[j][1];
            if(valid_pos(r, c) && board[r][c] == cur)
            {
                r -= step[j][0], c -= step[j][1];
                while(board[r][c] == opp)
                {
                    board[r][c] = cur;
                    r -= step[j][0], c -= step[j][1];
                    ++d;
                }
                f = true;
                cur == 'B' ? (nb += d, nw -= d) : (nw += d, nb -= d);
            }
        }
        if(f)
        {
            board[r0][c0] = cur;
            cur == 'B' ? ++nb : ++nw;
            cur = opp, opp = get_opponent();
            break;
        }
        cur = opp, opp = get_opponent();
    }
    printf("Black - %2d White - %2d\n", nb, nw);
}

int main()
{
    int i, tc;
    char str[8];
    scanf("%d", &tc);
    while(tc--)
    {
        for(i = 0; i < 8; i++)
            scanf("%s", board[i]);
        scanf("%s", str);
        cur = str[0];
        init();
        for(;;)
        {
            scanf("%s", str);
            if(str[0] == 'Q')
                break;
            if(str[0] == 'L')
                list_moves();
            else if(str[0] == 'M')
                move(str[1]-1-'0', str[2]-1-'0');
        }
        for(i = 0; i < 8; i++)
            puts(board[i]);
        if(tc)
            putchar('\n');
    }
    return 0;
}

