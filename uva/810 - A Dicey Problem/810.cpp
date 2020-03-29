#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>

char name[25];
int R, C, start_row, start_col;
int init_top, init_front;
int maze[12][12];
std::vector<std::pair<int, int> > path;
char vis[12][12][7][7];

struct dice_t
{
    char front, back, left, right, top, bottom;
};

const int left[6][6] = {
    { 0, 4, 2, 5, 3, 0 },
    { 3, 0, 6, 1, 0, 4 },
    { 5, 1, 0, 0, 6, 2 },
    { 2, 6, 0, 0, 1, 5 },
    { 4, 0, 1, 6, 0, 3 },
    { 0, 3, 5, 2, 4, 0 }
};

dice_t get_dice(int top, int front)
{
    dice_t d;
    d.top = top, d.front = front;
    d.bottom = 7-top, d.back = 7-front;
    d.left = left[top-1][front-1];
    d.right = 7-d.left;
    return d;
}

dice_t move_left(dice_t d)
{
    dice_t r = { d.front, d.back, d.top, d.bottom, d.right, d.left };
    return r;
}

dice_t move_right(dice_t d)
{
    dice_t r = { d.front, d.back, d.bottom, d.top, d.left, d.right };
    return r;
}

dice_t move_front(dice_t d)
{
    dice_t r = { d.top, d.bottom, d.left, d.right, d.back, d.front };
    return r;
}

dice_t move_back(dice_t d)
{
    dice_t r = { d.bottom, d.top, d.left, d.right, d.front, d.back };
    return r;
}

const int step[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };
dice_t (*move[4])(dice_t) = { move_back, move_front, move_left, move_right };

bool dfs(int r, int c, int s, dice_t d)
{
    int i, next_r, next_c;
    path.push_back(std::make_pair(r, c));
    if(s > 0 && r == start_row && c == start_col)
        return true;
    if(vis[r][c][d.top][d.front])
    {
        path.pop_back();
        return false;
    }
    vis[r][c][d.top][d.front] = 1;
    for(i = 0; i < 4; ++i)
    {
        next_r = r+step[i][0], next_c = c+step[i][1];
        if(maze[next_r][next_c] == -1 || maze[next_r][next_c] == d.top)
        {
            dice_t next_d = move[i](d);
            if(dfs(next_r, next_c, s+1, next_d))
                return true;
        }
    }
    path.pop_back();
    return false;
}

void solve()
{
    dice_t d = get_dice(init_top, init_front);
    std::memset(vis, 0, sizeof(vis));
    path.clear();
    dfs(start_row, start_col, 0, d);
}

int main()
{
    int i, j;
    while(std::scanf("%s", name) != EOF)
    {
        if(std::strcmp(name, "END") == 0)
            break;
        std::scanf("%d%d%d%d%d%d", &R, &C, &start_row, &start_col, &init_top, &init_front);
        std::memset(maze, 0, sizeof(maze));
        for(i = 1; i <= R; ++i)
            for(j = 1; j <= C; ++j)
                std::scanf("%d", &maze[i][j]);
        solve();
        std::puts(name);
        if(path.size() == 0)
            std::puts("  No Solution Possible");
        else
        {
            for(i = 0; i < path.size(); ++i)
            {
                if(i%9 == 0)
                    std::printf("  ");
                std::printf("(%d,%d)", path[i].first, path[i].second);
                if(i != path.size()-1)
                    std::putchar(',');
                if((i+1)%9 == 0 || i == path.size()-1)
                    std::putchar('\n');
            }
        }
    }
    return 0;
}

