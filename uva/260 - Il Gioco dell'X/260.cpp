#include <cstdio>
#include <queue>
#include <utility>

int n;
char board[200][200];
std::queue<std::pair<int, int> > q;

char solve()
{
    int i, j, r, c;
    bool w_win = false;
    std::pair<int, int> p;
    static const int dr[6] = { -1, -1, 0, 0, 1, 1 };
    static const int dc[6] = { -1, 0, -1, 1, 0, 1 };
    while(!q.empty())
        q.pop();
    for(i = 0; i < n; i++)
    {
        if(board[i][0] != 'w')
            continue;
        q.push(std::make_pair(i, 0));
        board[i][0] = 0;
        while(!q.empty())
        {
            p = q.front(), q.pop();
            if(p.second == n-1)
            {
                w_win = true;
                break;
            }
            for(j = 0; j < 6; j++)
            {
                r = p.first+dr[j];
                c = p.second+dc[j];
                if(r < 0 || r >= n || c < 0 || c >= n)
                    continue;
                if(board[r][c] != 'w')
                    continue;
                q.push(std::make_pair(r, c));
                board[r][c] = 0;
            }
        }
        if(w_win)
            break;
    }
    return w_win ? 'W' : 'B';
}

int main()
{
    int i, j, c = 0;
    char line[210];
    while(scanf("%d", &n), n)
    {
        for(i = 0; i < n; i++)
        {
            scanf("%s", line);
            for(j = 0; j < n; j++)
                board[i][j] = line[j];
        }
        char res = solve();
        printf("%d %c\n", ++c, res);
    }
    return 0;
}

