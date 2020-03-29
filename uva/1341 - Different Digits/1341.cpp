#include <cstdio>
#include <cstring>

#define MAXD 65535

using namespace std;

int n;

struct bigint_t
{
    char dig[MAXD];
    int len;
};

int compare(const bigint_t &x, const bigint_t &y)
{
    if(x.len < y.len)
        return -1;
    if(x.len > y.len)
        return 1;
    for(int i = x.len-1; i >= 0; i--)
        if(x.dig[i] < y.dig[i])
            return -1;
        else if(x.dig[i] > y.dig[i])
            return 1;
    return 0;
}

bigint_t res;

bool one_digit(int len)
{
    int i, j;
    int rem[10];
    bool suc = false;
    memset(rem, 0, sizeof(rem));
    for(i = 1; i <= len; i++)
    {
        for(j = 1; j <= 9; j++)
        {
            rem[j] = (rem[j]*10+j)%n;
            if(rem[j] == 0)
            {
                suc = true;
                break;
            }
        }
        if(suc)
            break;
    }
    if(suc)
    {
        res.len = i;
        for(i = 0; i < res.len; i++)
            res.dig[i] = j;
    }
    return suc;
}

struct bfs_node_t
{
    char dig;
    int mod;
    int prev;
    int dep;
    bfs_node_t() {};
    bfs_node_t(char dig, int mod, int prev, int dep) : dig(dig), mod(mod), prev(prev), dep(dep) {}
} que[MAXD];// It suffices.
int fr, ta;
bool vis[MAXD];
bigint_t tmp_res;

void two_digits()
{
    int i, j, r, t, u = n%10 ? 9 : 1;
    res.len = MAXD+1;
    for(i = 0; i < u; i++)
    {
        for(j = i+1; j <= 9; j++)
        {
            memset(vis, false, sizeof(vis));
            fr = ta = 0;
            if(i != 0)
            {
                que[ta++] = bfs_node_t(i, i%n, -1, 1);
                vis[i%n] = true;
            }
            que[ta++] = bfs_node_t(j, j%n, -1, 1);
            vis[j%n] = true;
            while(fr != ta)
            {
                bfs_node_t &e = que[fr];
                if(e.mod == 0)
                    break;
                if(e.dep+1 <= res.len)
                {
                    r = (e.mod*10+i)%n;
                    if(!vis[r])
                    {
                        que[ta++] = bfs_node_t(i, r, fr, e.dep+1);
                        vis[r] = true;
                    }
                    r = (e.mod*10+j)%n;
                    if(!vis[r])
                    {
                        que[ta++] = bfs_node_t(j, r, fr, e.dep+1);
                        vis[r] = true;
                    }
                }
                ++fr;
            }
            if(fr != ta)
            {
                tmp_res.len = 0;
                t = fr;
                while(t >= 0)
                {
                    tmp_res.dig[tmp_res.len++] = que[t].dig;
                    t = que[t].prev;
                }
                if(compare(tmp_res, res) < 0)
                {
                    res = tmp_res;
                }
            }
        }
    }
}

void solve()
{
    if(n%10 != 0)
        if(one_digit((n&1) ? n : n/2))
            return;
    two_digits();
}

char buf[65536];
void print_result()
{
    int i, j;
    for(i = res.len-1, j = 0; i >= 0; i--, j++)
        buf[j] = res.dig[i]+'0';
    buf[res.len] = '\0';
    printf("%s\n", buf);
}

int main()
{
    while(scanf("%d", &n), n)
    {
        solve();
        print_result();
    }
    return 0;
}

