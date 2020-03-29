#include <cstdio>
#include <cstring>

using namespace std;

struct bigint_t
{
    char dig[305];
    int len;
};

struct count_t
{
    bigint_t c00, c01;
} ans[1001];

inline void assign_1(bigint_t &x)
{
    memset(&x, 0, sizeof(x));
    x.dig[0] = x.len = 1;
}

void add_to(bigint_t &x, const bigint_t &y)
{
    int i;
    char c = 0;
    for(i = 0; i < y.len; i++)
    {
        x.dig[i] += y.dig[i]+c;
        c = x.dig[i] >= 10 ? x.dig[i] -= 10, c = 1 : c = 0;
    }
    while(c)
    {
        ++x.dig[i];
        if(x.dig[i] < 10)
            c = 0;
        ++i;
    }
    if(i > x.len)
        x.len = i;
}

void solve()
{
    int i;
    bigint_t k;
    assign_1(ans[1].c01);
    assign_1(k);
    for(i = 2; i <= 1000; i++)
    {
        add_to(ans[i].c01, k);
        add_to(ans[i].c00, ans[i-1].c01);
        add_to(ans[i].c01, ans[i-1].c00);
        add_to(k, k);
    }
}

void print_ans(int n)
{
    if(ans[n].c00.len == 0)
        printf("0\n");
    else
    {
        char buf[310];
        for(int i = 0; i < ans[n].c00.len; i++)
            buf[i] = ans[n].c00.dig[ans[n].c00.len-i-1]+'0';
        buf[ans[n].c00.len] = 0;
        printf("%s\n", buf);
    }
}

int main()
{
    int n;
    solve();
    while(scanf("%d", &n) != EOF)
    {
        print_ans(n);
    }
    return 0;
}

