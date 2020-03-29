#include <cstdio>

int nr, nc, n;
char map[2][100][101];
const int dx[4] = { -1, 0, 0, 1 };
const int dy[4] = { 0, -1, 1, 0 };

bool valid_pos(int r, int c)
{
    return r >= 0 && r < nr && c >= 0 && c < nc;
}

bool occupy(char cur, char nei)
{
    return cur == 'R' && nei == 'S'
        || cur == 'S' && nei == 'P'
        || cur == 'P' && nei == 'R';
}

void solve()
{
    int i, j, k, t = 0, r, c;
    while(n--)
    {
        for(i = 0; i < nr; i++)
        {
            for(j = 0; j < nc; j++)
            {
                for(k = 0; k < 4; k++)
                {
                    r = i+dx[k], c = j+dy[k];
                    if(!valid_pos(r, c))
                        continue;
                    if(occupy(map[t][r][c], map[t][i][j]))
                    {
                        map[1-t][i][j] = map[t][r][c];
                        break;
                    }
                }
                if(k == 4)
                    map[1-t][i][j] = map[t][i][j];
            }
        }
        t = 1-t;
    }
    for(i = 0; i < nr; i++)
        puts(map[t][i]);
}

int main()
{
    int i, tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d%d%d", &nr, &nc, &n);
        for(i = 0; i < nr; i++)
            scanf("%s", map[0][i]);
        solve();
        if(tc)
            puts("");
    }
    return 0;
}

