#include <cstdio>
#include <cstring>
#include <string>

int sr, sc;
int maze[4][6];
int vis[4][6];
std::string path;

const int dr[4] = {0, -1, 0, 1};
const int dc[4] = {-1, 0, 1, 0};
const int dir[4] = {1, 2, 4, 8};
const char dir_ch[4] = {'W', 'N', 'E', 'S'};

bool in_maze(int r, int c)
{
    return r >= 0 && r < 4 && c >= 0 && c < 6;
}

bool dfs(int r, int c, int cur_dep, int max_dep)
{
    int i, r2, c2, r3, c3;
    bool push;

    if(cur_dep > max_dep)
        return !in_maze(r, c);

    if(vis[r][c])
        return false;
    vis[r][c] = 1;

    for(i = 0; i < 4; ++i)
    {
        r2 = r+dr[i], c2 = c+dc[i], r3 = r2+dr[i], c3 = c2+dc[i];
        push = false;
        if(!(maze[r][c] & dir[i]) || (push = (in_maze(r2, c2) && !(maze[r2][c2] & dir[i]))))
        {
            if(push)
            {
                maze[r][c] -= dir[i];
                maze[r2][c2] += dir[i]-dir[(i+2)%4];
                if(in_maze(r3, c3))
                    maze[r3][c3] += dir[(i+2)%4];
            }
            path.push_back(dir_ch[i]);
            if(dfs(r2, c2, cur_dep+1, max_dep))
                return true;
            path.pop_back();
            if(push)
            {
                maze[r][c] += dir[i];
                maze[r2][c2] -= dir[i]-dir[(i+2)%4];
                if(in_maze(r3, c3))
                    maze[r3][c3] -= dir[(i+2)%4];
            }
        }
    }
    vis[r][c] = 0;

    return false;
}

void solve()
{
    int d = 1;
    path.clear();
    while(d <= 25)
    {
        std::memset(vis, 0, sizeof(vis));
        if(dfs(sr, sc, 1, d++))
            break;
    }
}

int main()
{
    int i, j;
    path.reserve(50);
    while(std::scanf("%d%d", &sc, &sr) && sr)
    {
        --sr, --sc;
        for(i = 0; i < 4; ++i)
            for(j = 0; j < 6; ++j)
                std::scanf("%d", &maze[i][j]);
        solve();
        std::printf("%s\n", path.c_str());
    }
    return 0;
}
