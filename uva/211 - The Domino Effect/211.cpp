#include <cstdio>

int layout[7][8];
int map_cnt;
int map[7][8];
bool domino_used[29];

int get_domino_number(int x, int y)
{
    if(x > y)
    {
        int t = x;
        x = y, y = t;
    }
    return (15-x)*x/2+(y-x+1);
}

void print_map()
{
    int i, j;
    for(i = 0; i < 7; ++i)
    {
        for(j = 0; j < 8; ++j)
            std::printf("%4d", map[i][j]);
        std::printf("\n");
    }
    std::printf("\n");
}

void next_pos(int r, int c, int *r2, int *c2)
{
    if(c < 7)
        *r2 = r, *c2 = c+1;
    else
        *r2 = r+1, *c2 = 0;
}

void dfs(int r, int c)
{
    if(r == 7)
    {
        ++map_cnt;
        print_map();
        return;
    }
    int r2, c2;
    if(map[r][c] >= 0)
    {
        next_pos(r, c, &r2, &c2);
        dfs(r2, c2);
        return;
    }
    if(c < 7 && map[r][c+1] < 0)
    {
        int d = get_domino_number(layout[r][c], layout[r][c+1]);
        if(!domino_used[d])
        {
            domino_used[d] = true;
            map[r][c] = map[r][c+1] = d;
            next_pos(r, c, &r2, &c2), next_pos(r2, c2, &r2, &c2);
            dfs(r2, c2);
            domino_used[d] = false;
            map[r][c] = map[r][c+1] = -1;
        }
    }
    if(r < 6)
    {
        int d = get_domino_number(layout[r][c], layout[r+1][c]);
        if(!domino_used[d])
        {
            domino_used[d] = true;
            map[r][c] = map[r+1][c] = d;
            next_pos(r, c, &r2, &c2);
            dfs(r2, c2);
            domino_used[d] = false;
            map[r][c] = map[r+1][c] = -1;
        }
    }
}

void solve()
{
    int i, j;
    map_cnt = 0;
    for(i = 0; i < 7; ++i)
        for(j = 0; j < 8; ++j)
            map[i][j] = -1;
    for(i = 1; i <= 28; ++i)
        domino_used[i] = false;
    dfs(0, 0);
}

int main()
{
    int i, j, tc = 0;
    while(std::scanf("%d", &layout[0][0]) != EOF)
    {
        for(i = 0; i < 7; ++i)
            for(j = (i == 0 ? 1 : 0); j < 8; ++j)
                std::scanf("%d", &layout[i][j]);
        if(tc)
            std::printf("\n\n\n");
        std::printf("Layout #%d:\n\n", ++tc);
        for(i = 0; i < 7; ++i)
        {
            for(j = 0; j < 8; ++j)
                std::printf("%4d", layout[i][j]);
            std::printf("\n");
        }
        std::printf("\n");
        std::printf("Maps resulting from layout #%d are:\n\n", tc);
        solve();
        std::printf("There are %d solution(s) for layout #%d.\n", map_cnt, tc);
    }
    return 0;
}
