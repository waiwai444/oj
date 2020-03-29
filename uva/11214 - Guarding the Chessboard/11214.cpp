#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <utility>
#include <vector>

int n, m, mark_cnt;
char board[10][11];
std::vector<int> guard[10][10];
char vis[10][10];

bool dfs(int cur, int max)
{
    int i, j, k;
    std::vector<std::pair<int, int> > arr;
    std::vector<int>::iterator it;
    if(mark_cnt == 0)
        return true;
    if(cur == max)
        return false;
    for(i = 0; i < n; ++i)
        for(j = 0; j < m; ++j)
            if(!vis[i][j])
            {
                int c = 0;
                for(it = guard[i][j].begin(); it != guard[i][j].end(); ++it)
                    if(board[*it/10][*it%10] == 'X')
                        ++c;
                if(c)
                    arr.push_back(std::make_pair(c, i*10+j));
            }
    std::sort(arr.begin(), arr.end(), std::greater<std::pair<int, int> >());
    for(k = 0; k < arr.size(); ++k)
    {
        if(arr[k].first*(max-cur) < mark_cnt)
            break;
        i = arr[k].second/10, j = arr[k].second%10;
        for(it = guard[i][j].begin(); it != guard[i][j].end(); ++it)
        {
            int x = *it/10, y = *it%10;
            if(board[x][y] == 'X')
            {
                board[x][y] = cur+1;
                --mark_cnt;
            }
        }
        if(dfs(cur+1, max))
            return true;
        vis[i][j] = cur+1;
        for(it = guard[i][j].begin(); it != guard[i][j].end(); ++it)
        {
            int x = *it/10, y = *it%10;
            if(board[x][y] == cur+1)
            {
                board[x][y] = 'X';
                ++mark_cnt;
            }
        }
    }
    for(i = 0; i < n; ++i)
        for(j = 0; j < m; ++j)
            if(vis[i][j] == cur+1)
                vis[i][j] = 0;
    return false;
}

int iddfs()
{
    int i = 0;
    while(true)
    {
        std::memset(vis, 0, sizeof(vis));
        if(dfs(0, i))
            return i;
        ++i;
    }
    return -1;
}

int solve()
{
    int i, j, k, l;
    mark_cnt = 0;
    for(i = 0; i < n; ++i)
        for(j = 0; j < m; ++j)
            if(board[i][j] == 'X')
                ++mark_cnt;
    for(i = 0; i < n; ++i)
        for(j = 0; j < m; ++j)
            guard[i][j].clear();
    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < m; ++j)
        {
            for(k = 0; k < n; ++k)
                if(board[k][j] == 'X')
                    guard[i][j].push_back(k*10+j);
            for(l = 0; l < m; ++l)
                if(board[i][l] == 'X' && l != j)
                    guard[i][j].push_back(i*10+l);
            for(k = i-1, l = j-1; k >= 0 && l >= 0; --k, --l)
                if(board[k][l] == 'X')
                    guard[i][j].push_back(k*10+l);
            for(k = i+1, l = j+1; k < n && l < m; ++k, ++l)
                if(board[k][l] == 'X')
                    guard[i][j].push_back(k*10+l);
            for(k = i-1, l = j+1; k >= 0 && l < m; --k, ++l)
                if(board[k][l] == 'X')
                    guard[i][j].push_back(k*10+l);
            for(k = i+1, l = j-1; k < n && l >= 0; ++k, --l)
                if(board[k][l] == 'X')
                    guard[i][j].push_back(k*10+l);
        }
    }
    return iddfs();
}

int main()
{
    int i, tc = 0;
    while(std::scanf("%d%d", &n, &m) != EOF && n)
    {
        for(i = 0; i < n; ++i)
            std::scanf("%s", board[i]);
        int ans = solve();
        std::printf("Case %d: %d\n", ++tc, ans);
    }
    return 0;
}
