#include <cstdio>
#include <cstring>
#include <cctype>
#include <queue>
#include <utility>

int n, m;
char grid[100][100];
int idx[100][100];
int nw, area[100*100];
std::queue<std::pair<int, int> > q;

const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
const int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

void solve(int r, int c)
{
    int i, u, v;
    std::pair<int, int> p;
    area[nw] = 1;
    idx[r][c] = nw;
    q.push(std::make_pair(r, c));
    while(!q.empty())
    {
        p = q.front(), q.pop();
        for(i = 0; i < 8; i++)
        {
            u = p.first+dx[i], v = p.second+dy[i];
            if(u < 0 || u >= n || v < 0 || v >= m)
                continue;
            if(grid[u][v] != 'W' || idx[u][v] >= 0)
                continue;
            idx[u][v] = nw;
            ++area[nw];
            q.push(std::make_pair(u, v));
        }
    }
    ++nw;
}

int main()
{
    int tc, r, c;
    char line[110];
    scanf("%d", &tc);
    fgets(line, sizeof(line), stdin);
    fgets(line, sizeof(line), stdin);
    while(tc--)
    {
        n = m = 0;
        while(fgets(line, sizeof(line), stdin))
        {
            if(isdigit(line[0]) || isspace(line[0]))
                break;
            if(m == 0)
            {
                m = strlen(line);
                while(isspace(line[m-1]))
                    --m;
            }
            memcpy(grid[n++], line, m);
        }
        nw = 0;
        memset(idx, -1, sizeof(idx));
        while(isdigit(line[0]))
        {
            sscanf(line, "%d%d", &r, &c);
            --r, --c;
            if(grid[r][c] == 'W')
            {
                if(idx[r][c] < 0)
                    solve(r, c);
                printf("%d\n", area[idx[r][c]]);
            }
            else
                puts("0");
            if(!fgets(line, sizeof(line), stdin))
                break;
        }
        if(tc)
            puts("");
    }
    return 0;
}

