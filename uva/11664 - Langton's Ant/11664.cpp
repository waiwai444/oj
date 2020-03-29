#include <cstdio>
#include <cstring>

#define N 0
#define E 1
#define S 2
#define W 3
const int dx[4] = { 0, 1, 0, -1 };
const int dy[4] = { 1, 0, -1, 0 };

int n;
char grid[16][16];

char div_by_2(char c[], int *l)
{
    int i;
    char r = 0;
    for(i = *l-1; i >= 0; i--)
    {
        c[i] += r*10;
        r = c[i]%2;
        c[i] /= 2;
    }
    while(*l > 0 && c[*l-1] == 0)
        --*l;
    return r;
}

void convert(char c[], int l)
{
    int i;
    char t;
    for(i = l/2-1; i >= 0; i--)
        t = c[i], c[i] = c[l-i-1], c[l-i-1] = t;
    for(i = 0; i < l; i++)
        c[i] -= '0';
}

void parse_config(char c[])
{
    int i, j, l = strlen(c);
    convert(c, l);
    for(j = n-1; j >= 0; j--)
        for(i = n-1; i >= 0; i--)
            grid[i][j] = div_by_2(c, &l);
}

bool valid_pos(int x, int y)
{
    return x >= 0 && x < n && y >= 0 && y < n;
}

bool target(int x, int y)
{
    return x == n-1 && y == n-1;
}

int turn_right(int dir)
{
    ++dir;
    return dir > W ? N : dir;
}

int turn_left(int dir)
{
    --dir;
    return dir < N ? W : dir;
}

bool go(int x, int y)
{
    int dir = N;
    for(;;)
    {
        if(!valid_pos(x, y))
            return false;
        if(target(x, y))
            return true;
        if(grid[x][y] == 0) // blue
        {
            grid[x][y] = 1-grid[x][y];
            dir = turn_left(dir);
            x += dx[dir], y += dy[dir];
        }
        else // red
        {
            grid[x][y] = 1-grid[x][y];
            dir = turn_right(dir);
            x += dx[dir], y += dy[dir];
        }
    }
}

int main()
{
    char c[80];
    int x, y;
    while(scanf("%d%s%d%d", &n, c, &x, &y), n)
    {
        parse_config(c);
        if(go(x-1, y-1))
            puts("Yes");
        else
            puts("Kaputt!");
    }
    return 0;
}

