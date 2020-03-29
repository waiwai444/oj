#include <cstdio>
#include <cstring>

int R, C;
char puz[15][16];
char ans[32];
int ans_len;
int max_len;
char cur[32];
const int dr[4] = {0, 0, -1, 1};
const int dc[4] = {1, -1, 0, 0};
char vis[15][15];

int remain(int r, int c)
{
    vis[r][c] = 1;
    int cnt = 1;
    for(int i = 0; i < 4; ++i)
    {
        int r1 = r+dr[i], c1 = c+dc[i];
        if(r1 < 0 || r1 >= R || c1 < 0 || c1 >= C || puz[r1][c1] == '#' || puz[r1][c1] > '9' || vis[r1][c1])
            continue;
        cnt += remain(r1, c1);
    }
    return cnt;
}

bool dfs(int r, int c, int dep, int cmp)
{
    bool ret = false;
    if(dep < ans_len && cmp == 0 && puz[r][c] < ans[dep])
        return ret;
    std::memset(vis, 0, sizeof(vis));
    if(dep+remain(r, c) < max_len)
        return ret;
    cur[dep] = puz[r][c];
    puz[r][c] += 10;
    for(int i = 0; i < 4; ++i)
    {
        int r1 = r+dr[i], c1 = c+dc[i];
        if(r1 < 0 || r1 >= R || c1 < 0 || c1 >= C || puz[r1][c1] == '#' || puz[r1][c1] > '9')
            continue;
        if(dfs(r1, c1, dep+1, cur[dep] > ans[dep] ? 1 : cmp))
        {
            ret = true;
            cmp = 0;
        }
    }
    if(dep+1 == max_len)
    {
        std::memcpy(ans, cur, max_len);
        ans_len = max_len;
        ret = true;
    }
    puz[r][c] -= 10;
    return ret;
}

void solve()
{
    int i, j;
    max_len = R*C;
    for(i = 0; i < R; ++i)
        for(j = 0; j < C; ++j)
            if(puz[i][j] == '#')
                --max_len;
    ans_len = 1;
    ans[0] = '0';
    while(ans_len < max_len)
    {
        int first = 9;
        while(first)
        {
            for(i = 0; i < R; ++i)
            {
                for(j = 0; j < C; ++j)
                {
                    if(puz[i][j] == first+'0')
                    {
                        dfs(i, j, 0, 0);
                    }
                }
            }
            if(ans_len == max_len)
                break;
            --first;
        }
        --max_len;
    }
}

int main()
{
    int i;
    while(std::scanf("%d%d", &R, &C) != EOF)
    {
        if(!R || !C)
            break;
        for(i = 0; i < R; ++i)
            std::scanf("%s", puz[i]);
        solve();
        ans[ans_len] = 0;
        std::printf("%s\n", ans);
    }
    return 0;
}
