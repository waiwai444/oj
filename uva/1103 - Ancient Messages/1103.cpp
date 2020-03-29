#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

int h, w;
char img[200][201];
const char *bin[16] = { "0000", "0001", "0010", "0011",
                        "0100", "0101", "0110", "0111",
                        "1000", "1001", "1010", "1011",
                        "1100", "1101", "1110", "1111" };
const int dx[4] = { -1, 0, 0, 1 };
const int dy[4] = { 0, -1, 1, 0 };
std::queue<std::pair<int, int> > q;
std::vector<std::pair<int, int> > bd;
std::vector<char> ans;

void expand_line(int l, const char *str)
{
    int i;
    const char *p;
    char *q;
    for(p = str, q = img[l]; *p; ++p, q += 4)
    {
        i = *p >= 'a' ? *p-'a'+10 : *p-'0';
        strcpy(q, bin[i]);
    }
}

bool valid_pos(int r, int c)
{
    return r >= 0 && r < h && c >= 0 && c < w;
}

char get_ch(int i)
{
    switch(i)
    {
    case 0:
        return 'W';
    case 1:
        return 'A';
    case 2:
        return 'K';
    case 3:
        return 'J';
    case 4:
        return 'S';
    case 5:
        return 'D';
    }
    return 0;
}

void floodfill(int r, int c, char ch)
{
    int i;
    std::pair<int, int> p;
    char t = img[r][c];
    if(t == ch)
        return;
    img[r][c] = ch;
    q.push(std::make_pair(r, c));
    while(!q.empty())
    {
        p = q.front(), q.pop();
        for(i = 0; i < 4; i++)
        {
            r = p.first+dx[i], c = p.second+dy[i];
            if(!valid_pos(r, c) || img[r][c] != t)
                continue;
            img[r][c] = ch;
            q.push(std::make_pair(r, c));
        }
    }
}

void mark_outer_area()
{
    int i;
    for(i = 0; i < w; i++)
    {
        if(img[0][i] == '0')
            floodfill(0, i, '.');
        if(img[h-1][i] == '0')
            floodfill(h-1, i, '.');
    }
    for(i = 0; i < h; i++)
    {
        if(img[i][0] == '0')
            floodfill(i, 0, '.');
        if(img[i][w-1] == '0')
            floodfill(i, w-1, '.');
    }
}

char identify(int r, int c)
{
    int i, hole = 0;
    std::pair<int, int> p;
    bd.clear();
    img[r][c] = '.';
    q.push(std::make_pair(r, c));
    while(!q.empty())
    {
        p = q.front(), q.pop();
        for(i = 0; i < 4; i++)
        {
            r = p.first+dx[i], c = p.second+dy[i];
            if(!valid_pos(r, c))
                continue;
            if(img[r][c] == '1')
            {
                img[r][c] = '.';
                q.push(std::make_pair(r, c));
            }
            else if(img[r][c] == '0')
                bd.push_back(std::make_pair(r, c));
        }
    }
    for(i = 0; i < bd.size(); i++)
    {
        p = bd[i];
        if(img[p.first][p.second] != '0')
            continue;
        ++hole;
        floodfill(p.first, p.second, '.');
    }
    return get_ch(hole);
}

void solve()
{
    int i, j;
    mark_outer_area();
    ans.clear();
    for(i = 0; i < h; i++)
        for(j = 0; j < w; j++)
            if(img[i][j] == '1')
                ans.push_back(identify(i, j));
    std::sort(ans.begin(), ans.end());
}

int main()
{
    int i, c = 0;
    char line[55];
    while(scanf("%d%d", &h, &w), h)
    {
        w *= 4;
        for(i = 0; i < h; i++)
        {
            scanf("%s", line);
            expand_line(i, line);
        }
        solve();
        printf("Case %d: ", ++c);
        for(i = 0; i < ans.size(); i++)
            printf("%c", ans[i]);
        printf("\n");
    }
    return 0;
}

