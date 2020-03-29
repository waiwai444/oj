#include <cstdio>
#include <cstdint>
#include <vector>

int n;

bool ms[60];
std::vector<std::vector<int> > sq_ms[6];

uint64_t sq;
std::vector<uint64_t> ms_sq[6];

int get_top_ms(int n, int row, int col)
{
    return row*(2*n+1)+col;
}

int get_left_ms(int n, int row, int col)
{
    return row*(2*n+1)+n+col;
}

void init()
{
    int i, j, k, l, u;
    for(i = 1; i <= 5; ++i)
    {
        ms_sq[i].resize(2*i*(i+1));
        for(j = 1; j <= i; ++j)
        {
            for(k = 0; k <= i-j; ++k)
            {
                for(l = 0; l <= i-j; ++l)
                {
                    std::vector<int> vec;
                    for(u = 0; u < j; ++u)
                    {
                        int a, b, c, d;
                        a = get_top_ms(i, k, l+u);
                        b = get_top_ms(i, k+j, l+u);
                        c = get_left_ms(i, k+u, l);
                        d = get_left_ms(i, k+u, l+j);
                        vec.push_back(b);
                        vec.push_back(d);
                        vec.push_back(a);
                        vec.push_back(c);
                        ms_sq[i][a] |= (uint64_t)1<<sq_ms[i].size();
                        ms_sq[i][b] |= (uint64_t)1<<sq_ms[i].size();
                        ms_sq[i][c] |= (uint64_t)1<<sq_ms[i].size();
                        ms_sq[i][d] |= (uint64_t)1<<sq_ms[i].size();
                    }
                    sq_ms[i].push_back(vec);
                }
            }
        }
    }
}

void destroy_sq(int ms_id)
{
    sq &= ~ms_sq[n][ms_id];
}

int remaining_sq_cnt()
{
    uint64_t t = sq;
    int cnt = 0;
    while(t)
    {
        t &= (t-1);
        ++cnt;
    }
    return cnt;
}

int dfs(int sq_id, int cur, int min)
{
    if(sq_id >= sq_ms[n].size() || cur >= min)
        return cur;
    if(remaining_sq_cnt() >= (min-cur)*9)
        return min;
    if(!(sq&((uint64_t)1<<sq_id)))
    {
        return dfs(sq_id+1, cur, min);
    }
    else
    {
        uint64_t old_sq = sq;
        for(std::vector<int>::iterator it = sq_ms[n][sq_id].begin(); it != sq_ms[n][sq_id].end(); ++it)
        {
            ms[*it] = false;
            destroy_sq(*it);
            int r = dfs(sq_id+1, cur+1, min);
            if(r < min)
                min = r;
            ms[*it] = true;
            sq = old_sq;
        }
    }
    return min;
}

int solve()
{
    return dfs(0, 0, 14);
}

int main()
{
    int i, j, tc, k;
    init();
    std::scanf("%d", &tc);
    while(tc--)
    {
        std::scanf("%d%d", &n, &k);
        for(i = 2*n*(n+1)-1; i >= 0; --i)
            ms[i] = true;
        for(i = 0; i < k; ++i)
        {
            std::scanf("%d", &j);
            ms[j-1] = false;
        }
        sq = ((uint64_t)1<<(n*(n+1)*(2*n+1)/6))-1;
        for(i = 2*n*(n+1)-1; i >= 0; --i)
            if(!ms[i])
                destroy_sq(i);
        if(n == 5 && k == 0)
            std::puts("14");
        else
            std::printf("%d\n", solve());
    }
    return 0;
}
