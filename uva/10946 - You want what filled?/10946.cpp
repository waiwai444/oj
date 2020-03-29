#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

int x, y;
char map[50][50];
std::vector<std::pair<int, char> > ans;
std::queue<std::pair<int, int> > q;
const int dx[4] = { -1, 0, 0, 1 };
const int dy[4] = { 0, -1, 1, 0 };

inline bool valid_pos(int r, int c)
{
    return r >= 0 && r < x && c >= 0 && c < y;
}

int bfs(int sr, int sc)
{
    int i, r, c, ret = 1;
    char ch = map[sr][sc];
    std::pair<int, int> p;
    q.push(std::make_pair(sr, sc));
    map[sr][sc] = '.';
    while(!q.empty())
    {
        p = q.front(), q.pop();
        for(i = 0; i < 4; i++)
        {
            r = p.first+dx[i], c = p.second+dy[i];
            if(!valid_pos(r, c) || map[r][c] != ch)
                continue;
            q.push(std::make_pair(r, c));
            map[r][c] = '.';
            ++ret;
        }
    }
    return ret;
}

void solve()
{
    int i, j;
    char ch;
    ans.clear();
    for(i = 0; i < x; i++)
    {
        for(j = 0; j < y; j++)
        {
            if(map[i][j] == '.')
                continue;
            ch = map[i][j];
            ans.push_back(std::make_pair(-bfs(i, j), ch));;
        }
    }
    sort(ans.begin(), ans.end());
}

void print_ans()
{
    for(int i = 0; i < ans.size(); i++)
    {
        printf("%c %d\n", ans[i].second, -ans[i].first);
    }
}

int main()
{
    int i, j, c = 0;
    char line[51];
    while(scanf("%d%d", &x, &y), x || y)
    {
        for(i = 0; i < x; i++)
        {
            scanf("%s", line);
            memcpy(map[i], line, y);
        }
        solve();
        printf("Problem %d:\n", ++c);
        print_ans();
    }
    return 0;
}

