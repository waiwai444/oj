#include <cstdio>
#include <cstring>
#include <queue>

const int jump[16][6][5] = {
    {},
    {{2, 4, 7, 11}, {3, 6, 10, 15}},
    {{4, 7, 11}, {5, 9, 14}},
    {{5, 8, 12}, {6, 10, 15}},
    {{2, 1}, {5, 6}, {7, 11}, {8, 13}},
    {{8, 12}, {9, 14}},
    {{3, 1}, {5, 4}, {9, 13}, {10, 15}},
    {{4, 2, 1}, {8, 9, 10}},
    {{5, 3}, {9, 10}},
    {{5, 2}, {8, 7}},
    {{6, 3, 1}, {9, 8, 7}},
    {{7, 4, 2, 1}, {12, 13, 14, 15}},
    {{8, 5, 3}, {13, 14, 15}},
    {{8, 4}, {9, 6}, {12, 11}, {14, 15}},
    {{9, 5, 2}, {13, 12, 11}},
    {{10, 6, 3, 1}, {14, 13, 12, 11}}
};

struct state_t
{
    unsigned short c;
    char l;
    unsigned char s[13];
};

int e;
char vis[(1<<16)-1];

state_t res;

bool bfs(int init_c)
{
    int i, j, k;
    std::memset(vis, 0, sizeof(vis));
    std::queue<state_t> st_q;
    state_t st;
    st.c = init_c, st.l = 0;
    st_q.push(st);
    vis[st.c] = 1;
    while(!st_q.empty())
    {
        st = st_q.front(), st_q.pop();
        for(i = 1; i <= 15; ++i)
        {
            if(!(st.c&(1<<i)))
                continue;
            for(j = 0; jump[i][j][0]; ++j)
            {
                if(!(st.c&(1<<jump[i][j][0])))
                    continue;
                for(k = 1; jump[i][j][k] && (st.c&(1<<jump[i][j][k])); ++k)
                    continue;
                if(jump[i][j][k])
                {
                    res = st;
                    res.c &= ~(1<<i);
                    for(int u = 0; u < k; ++u)
                        res.c &= ~(1<<jump[i][j][u]);
                    res.c |= (1<<jump[i][j][k]);
                    res.s[res.l] = i+(jump[i][j][k]<<4);
                    ++res.l;
                    if(res.c == (1<<e))
                        return true;
                    if(!vis[res.c])
                    {
                        st_q.push(res);
                        vis[res.c] = 1;
                    }
                }
            }
        }
    }
    return false;
}

int main()
{
    int tc;
    std::scanf("%d", &tc);
    while(tc--)
    {
        std::scanf("%d", &e);
        int c = ((1<<16)-2)&~(1<<e);
        if(bfs(c))
        {
            std::printf("%d\n", res.l);
            std::printf("%d %d", res.s[0]&15, (res.s[0]>>4)&15);
            for(int i = 1; i < res.l; ++i)
                std::printf(" %d %d", res.s[i]&15, (res.s[i]>>4)&15);
            std::putchar('\n');
        }
        else
            std::puts("IMPOSSIBLE");
    }
    return 0;
}
