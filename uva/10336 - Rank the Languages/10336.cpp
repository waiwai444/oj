#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <utility>
#include <functional>

int h, w;
char *map;
std::pair<int, char> ans[26];
std::queue<std::pair<int, int> > q;
const int dx[4] = { -1, 0, 0, 1 };
const int dy[4] = { 0, -1, 1, 0 };

#define mat(i, j) (*(map+(i)*w+(j)))

inline bool valid_pos(int r, int c)
{
    return r >= 0 && r < h && c >= 0 && c < w;
}

void bfs(int sr, int sc)
{
    int i, r, c;
    char ch = mat(sr, sc);
    std::pair<int, int> p;
    q.push(std::make_pair(sr, sc));
    mat(sr, sc) = 0;
    while(!q.empty())
    {
        p = q.front(), q.pop();
        for(i = 0; i < 4; i++)
        {
            r = p.first+dx[i], c = p.second+dy[i];
            if(!valid_pos(r, c) || mat(r, c) == 0 || mat(r, c) != ch)
                continue;
            q.push(std::make_pair(r, c));
            mat(r, c) = 0;
        }
    }
}

void solve()
{
    int i, j;
    for(i = 0; i < 26; i++)
        ans[i].first = 0, ans[i].second = 'a'+i;
    for(i = 0; i < h; i++)
    {
        for(j = 0; j < w; j++)
        {
            if(mat(i, j) == 0)
                continue;
            --ans[mat(i, j)-'a'].first;
            bfs(i, j);
        }
    }
    std::sort(ans, ans+26);
}

void print_ans()
{
    for(int i = 0; i < 26; i++)
    {
        if(ans[i].first == 0)
            break;
        printf("%c: %d\n", ans[i].second, -ans[i].first);
    }
}

int main()
{
    int i, j, tc;
    char *line;
    scanf("%d", &tc);
    for(i = 1; i <= tc; i++)
    {
        scanf("%d%d", &h, &w);
        map = new char[h*w];
        line = new char[w+1];
        for(j = 0; j < h; j++)
        {
            scanf("%s", line);
            memcpy(map+j*w, line, w);
        }
        solve();
        printf("World #%d\n", i);
        print_ans();
        delete[] line;
        delete[] map;
    }
    return 0;
}

