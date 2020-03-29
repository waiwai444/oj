#include <cstdio>
#include <vector>
#include <queue>
#include <utility>

int n, m;
std::vector<char> trees[1000];
std::vector<int> monkeys[1000];
std::queue<std::pair<int, int> > q;

const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

void bfs(int sr, int sc, int num)
{
    int i, r, c;
    char t = trees[sr][sc];
    std::pair<int, int> p;
    q.push(std::make_pair(sr, sc));
    trees[sr][sc] = 0;
    monkeys[sr][sc] = num;
    while(!q.empty())
    {
        p = q.front(), q.pop();
        for(i = 0; i < 8; i++)
        {
            r = p.first+dx[i], c = p.second+dy[i];
            if(r < 0 || r >= n || c < 0 || c >= m)
                continue;
            if(trees[r][c] != t)
                continue;
            q.push(std::make_pair(r, c));
            trees[r][c] = 0;
            monkeys[r][c] = num;
        }
    }
}

void solve()
{
    int i, j, num = 1;
    for(i = 0; i < n; i++)
        monkeys[i].resize(m);
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            if(trees[i][j] == 0)
                continue;
            bfs(i, j, num++);
        }
    }
}

int get_width(int x)
{
    int r = 0;
    while(x)
    {
        ++r;
        x /= 10;
    }
    return r;
}

void print_ans()
{
    int i, j;
    int *width = new int[m];
    for(j = 0; j < m; j++)
    {
        width[j] = get_width(monkeys[0][j]);
        for(i = 0; i < n; i++)
        {
            int w = get_width(monkeys[i][j]);
            if(w > width[j])
                width[j] = w;
        }
    }
    for(i = 0; i < n; i++)
    {
        printf("%*d", width[0], monkeys[i][0]);
        for(j = 1; j < m; j++)
            printf(" %*d", width[j], monkeys[i][j]);
        printf("\n");
    }
    printf("%%\n");
    delete[] width;
}

int main()
{
    int i, c;
    for(;;)
    {
        n = m = 0;
        while((c = fgetc(stdin)) != EOF)
        {
            if(c == '%')
            {
                fgetc(stdin);
                break;
            }
            trees[n].push_back(c);
            c = fgetc(stdin);
            if(c == '\n')
                ++n;
        }
        m = trees[0].size();
        solve();
        print_ans();
        if(c == EOF)
            break;
        for(i = 0; i < n; i++)
        {
            trees[i].clear();
            monkeys[i].clear();
        }
    }
    return 0;
}

