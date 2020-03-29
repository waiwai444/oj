#include <cstdio>
#include <cstring>
#include <cctype>

int year;
bool map[2][20][20];
const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

bool valid_pos(int r, int c)
{
    return r >= 0 && r < 20 && c >= 0 && c < 20;
}

int count_neighbors(int r, int c, int t)
{
    int i, r1, c1, n = 0;
    for(i = 0; i < 8; i++)
    {
        r1 = r+dx[i], c1 = c+dy[i];
        if(!valid_pos(r1, c1))
            continue;
        if(map[t][r1][c1])
            ++n;
    }
    return n;
}

void print_map(int t)
{
    int i, j;
    for(i = 0; i < 20; i++)
    {
        for(j = 0; j < 20; j++)
            printf("%c", map[t][i][j] ? 'O' : ' ');
        printf("\n");
    }
}

void solve()
{
    int i, j, k, t = 0, n;
    for(i = 0; i < year; i++)
    {
        puts("********************");
        print_map(t);
        for(j = 0; j < 20; j++)
        {
            for(k = 0; k < 20; k++)
            {
                n = count_neighbors(j, k, t);
                if(map[t][j][k])
                {
                    if(n == 2 || n == 3)
                        map[1-t][j][k] = true;
                    else if(n >= 4 || n <= 1)
                        map[1-t][j][k] = false;
                }
                else
                {
                    if(n == 3)
                        map[1-t][j][k] = true;
                    else
                        map[1-t][j][k] = false;
                }
            }
        }
        t = 1-t;
    }
    puts("********************");
}

int main()
{
    int tc, r, c;
    char line[10];
    scanf("%d", &tc);
    fgets(line, sizeof(line), stdin);
    fgets(line, sizeof(line), stdin);
    while(tc--)
    {
        fgets(line, sizeof(line), stdin);
        sscanf(line, "%d", &year);
        memset(map, false, sizeof(map));
        while(fgets(line, sizeof(line), stdin))
        {
            if(!isdigit(line[0]))
                break;
            sscanf(line, "%d%d", &r, &c);
            map[0][r-1][c-1] = true;
        }
        solve();
        if(tc)
            puts("");
    }
    return 0;
}

