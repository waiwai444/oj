#include <cstdio>
#include <cstring>
#include <cctype>
#include <queue>

int width, height, n;
char board[256];
int adj[256][5];
int deg[256];
int init;
int dest;

int dist[2][1<<24];

const int dx[5] = {0, -1, 0, 1, 0};
const int dy[5] = {0, 0, -1, 0, 1};

int move(int p, int d)
{
    return p == 0 ? 0 : (p+dx[d]&15)+((p>>4)+dy[d]<<4);
}

int get_state(int a, int b, int c)
{
    return a+(b<<8)+(c<<16);
}

void get_pos(int st, int *a, int *b, int *c)
{
    *a = st&255, *b = (st>>8)&255, *c = (st>>16)&255;
}

int search(std::queue<int> *q, int dir, int cnt, int *next_cnt)
{
    int i, j, k, s, t;
    int a, b, c, a2, b2, c2;
    *next_cnt = 0;
    while(!q[dir].empty() && cnt > 0)
    {
        s = q[dir].front(), q[dir].pop();
        --cnt;
        if(dist[1-dir][s] >= 0)
            return dist[dir][s]+dist[1-dir][s];
        get_pos(s, &a, &b, &c);
        for(i = 0; i < deg[a]; ++i)
        {
            a2 = adj[a][i];
            for(j = 0; j < deg[b]; ++j)
            {
                b2 = adj[b][j];
                if(a2 == b2 || a2 == b && b2 == a)
                    continue;
                for(k = 0; k < deg[c]; ++k)
                {
                    c2 = adj[c][k];
                    if(c2 != 0 && (a2 == c2 || b2 == c2 || c2 == a && a2 == c || c2 == b && b2 == c))
                        continue;
                    t = get_state(a2, b2, c2);
                    if(dist[dir][t] < 0)
                    {
                        dist[dir][t] = dist[dir][s]+1;
                        q[dir].push(t);
                        ++*next_cnt;
                    }
                }
            }
        }
    }
    return -1;
}

int bbfs()
{
    int ret, cnt_f, cnt_b;
    std::queue<int> q[2];
    std::memset(dist, -1, sizeof(dist));
    if(init == dest)
        return 0;
    q[0].push(init);
    q[1].push(dest);
    dist[0][init] = dist[1][dest] = 0;
    cnt_f = cnt_b = 1;
    while(!q[0].empty() && !q[1].empty())
    {
        if((ret = search(q, 0, cnt_f, &cnt_f)) >= 0)
            return ret;
        if((ret = search(q, 1, cnt_b, &cnt_b)) >= 0)
            return ret;
    }
    return -1;
}

int main()
{
    int i, j, k, s[3], t[3], p, q;
    char line[20];
    while(std::scanf("%d%d%d", &width, &height, &n))
    {
        if(width == 0 && height == 0 && n == 0)
            break;
        s[0] = s[1] = s[2] = t[0] = t[1] = t[2] = 0;
        std::memset(deg, 0, sizeof(deg));
        std::fgets(line, sizeof(line), stdin);
        for(i = 0; i < height; ++i)
        {
            std::fgets(line, sizeof(line), stdin);
            for(j = 0; j < width; ++j)
            {
                p = i+(j<<4);
                if(std::isupper(line[j]))
                    t[line[j]-'A'] = p, board[p] = ' ';
                else if(std::islower(line[j]))
                    s[line[j]-'a'] = p, board[p] = ' ';
                else
                    board[p] = line[j];
            }
        }
        for(i = 0; i < height; ++i)
        {
            for(j = 0; j < width; ++j)
            {
                p = i+(j<<4);
                if(board[p] == ' ')
                    for(k = 0; k < 5; ++k)
                        if(board[q = move(p, k)] == ' ')
                            adj[p][deg[p]++] = q;
            }
        }
        board[0] = ' ';
        adj[0][0] = 0, deg[0] = 1;
        init = get_state(s[0], s[1], s[2]), dest = get_state(t[0], t[1], t[2]);
        std::printf("%d\n", bbfs());
    }
    return 0;
}

