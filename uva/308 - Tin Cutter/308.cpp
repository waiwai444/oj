#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <algorithm>
#include <utility>

#define MAXN 100

int n;

struct line_t
{
    int x1, y1, x2, y2;
} line[MAXN];

char grid[6*MAXN+1][6*MAXN+1];
int h, w;

typedef std::pair<int, int> pii;
std::map<int, int> xmap, ymap;
std::queue<pii> q;

void construct_grid()
{
    int i, j, u1, u2, v1, v2;
    std::map<int, int>::iterator it;
    xmap.clear(), ymap.clear();
    for(i = 0; i < n; i++)
    {
        if(line[i].x1 == line[i].x2)
            xmap[line[i].x1] = ymap[line[i].y1] = ymap[line[i].y2] = 0;
        else
            xmap[line[i].x1] = xmap[line[i].x2] = ymap[line[i].y1] = 0;
    }
    for(w = 1, it = xmap.begin(); it != xmap.end(); ++it, w += 2)
        it->second = w;
    for(h = 1, it = ymap.begin(); it != ymap.end(); ++it, h += 2)
        it->second = h;

    memset(grid, 0, sizeof(grid));
    for(i = 0; i < n; i++)
    {
        if(line[i].y1 == line[i].y2)
        {
            u1 = xmap[line[i].x1];
            u2 = xmap[line[i].x2];
            if(u1 > u2) std::swap(u1, u2);
            v1 = ymap[line[i].y1];
            for(j = u1; j <= u2; j++)
                grid[j][v1] = 'x';
        }
        else
        {
            u1 = xmap[line[i].x1];
            v1 = ymap[line[i].y1];
            v2 = ymap[line[i].y2];
            if(v1 > v2) std::swap(v1, v2);
            for(j = v1; j <= v2; j++)
                grid[u1][j] = 'x';
        }
    }
}

void mark_outer_area()
{
    int i, j, k;
    pii p;
    q.push(std::make_pair(0, 0));
    while(!q.empty())
    {
        p = q.front(), q.pop();
        if(grid[p.first][p.second] != 0)
            continue;
        for(j = p.second-1; j >= 0; j--)
            if(grid[p.first][j] == 'x')
                break;
        for(k = p.second+1; k < h; k++)
            if(grid[p.first][k] == 'x')
                break;
        for(i = j+1; i < k; i++)
        {
            grid[p.first][i] = 'o';
            if(p.first > 0 && grid[p.first-1][i] == 0)
                q.push(std::make_pair(p.first-1, i));
            if(p.first < w-1 && grid[p.first+1][i] == 0)
                q.push(std::make_pair(p.first+1, i));
        }
    }
}

void mark_hole(int u, int v)
{
    int i, j, k;
    pii p;
    q.push(std::make_pair(u, v));
    while(!q.empty())
    {
        p = q.front(), q.pop();
        if(grid[p.first][p.second] != 0)
            continue;
        for(j = p.second-1; j > 1; j--)
            if(grid[p.first][j] == 'o')
                break;
        for(k = p.second+1; k < h-2; k++)
            if(grid[p.first][k] == 'o')
                break;
        for(i = j+1; i < k; i++)
        {
            if(grid[p.first][i] == 'x')
                continue;
            grid[p.first][i] = 'o';
            char c = grid[p.first-1][i];
            if(c == 0)
                q.push(std::make_pair(p.first-1, i));
            else if(c == 'x' && grid[p.first-2][i] == 0)
                q.push(std::make_pair(p.first-2, i));
            c = grid[p.first+1][i];
            if(c == 0)
                q.push(std::make_pair(p.first+1, i));
            else if(c == 'x' && grid[p.first+2][i] == 0)
                q.push(std::make_pair(p.first+2, i));
        }
    }
}

int count_holes()
{
    int i, j, c = 0;
    for(i = 2; i < w-2; i++)
    {
        for(j = 2; j < h-2; j++)
        {
            if(grid[i][j] == 0)
            {
                ++c;
                mark_hole(i, j);
            }
        }
    }
    return c;
}

int solve()
{
    construct_grid();
    mark_outer_area();
    return count_holes();
}

int main()
{
    int i;
    while(scanf("%d", &n), n)
    {
        for(i = 0; i < n; i++)
            scanf("%d%d%d%d", &line[i].x1, &line[i].y1, &line[i].x2, &line[i].y2);
        printf("%d\n", solve());
    }
    return 0;
}

