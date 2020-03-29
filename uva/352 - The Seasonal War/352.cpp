#include <cstdio>
#include <queue>
#include <utility>

int n;
char img[25][26];

std::queue<std::pair<int, int> > q;
static const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
static const int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

int solve()
{
    int i, j, k, cnt = 0;
    std::pair<int, int> p;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(img[i][j] != '1')
                continue;
            ++cnt;
            q.push(std::make_pair(i, j));
            img[i][j] = 0;
            while(!q.empty())
            {
                p = q.front(), q.pop();
                for(k = 0; k < 8; k++)
                {
                    int u = p.first+dx[k], v = p.second+dy[k];
                    if(u < 0 || u >= n || v < 0 || v >= n)
                        continue;
                    if(img[u][v] != '1')
                        continue;
                    q.push(std::make_pair(u, v));
                    img[u][v] = 0;
                }
            }
        }
    }
    return cnt;
}

int main()
{
    int i, c = 0;
    while(scanf("%d", &n) != EOF)
    {
        for(i = 0; i < n; i++)
            scanf("%s", img[i]);
        int ans = solve();
        printf("Image number %d contains %d war eagles.\n", ++c, ans);
    }
    return 0;
}

