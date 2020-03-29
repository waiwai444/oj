#include <cstdint>
#include <cstdio>
#include <cstring>
#include <utility>

int n;
typedef std::pair<long long, long long> pu64;
pu64 resv;
int ans;

void read_reserv_tab()
{
    int i, j;
    char tab[5][21];
    resv.first = resv.second = 0;
    for(i = 0; i < 5; ++i)
        std::scanf("%s", tab[i]);
    for(i = 0; i < n && i < 12; ++i)
        for(j = 0; j < 5; ++j)
            if(tab[j][i] == 'X')
                resv.first |= (1ll<<(i*5+j));
    for(; i < n; ++i)
        for(j = 0; j < 5; ++j)
            if(tab[j][i] == 'X')
                resv.second |= (1ll<<((i-12)*5+j));
}

pu64 shift_clock_tab(pu64 x)
{
    pu64 t;
    t.first = (x.first>>5)|((x.second&0x1f)<<55);
    t.second = x.second>>5;
    return t;
}

inline bool is_schedulable(pu64 tab)
{
    return (tab.first&resv.first) == 0 && (tab.second&resv.second) == 0;
}

void dfs(int task, pu64 clock_tab, int length)
{
    if(task == 10)
    {
        ans = length;
        return;
    }
    for(int i = length-n+1; i <= length; ++i)
    {
        if(task == 5 && i+length >= ans)
            break;
        if(i+n+9-task >= ans)
            break;
        clock_tab = shift_clock_tab(clock_tab);
        if(is_schedulable(clock_tab))
        {
            pu64 tmp = clock_tab;
            tmp.first |= resv.first;
            tmp.second |= resv.second;
            dfs(task+1, tmp, i+n);
        }
    }
}

void solve()
{
    ans = n*10;
    dfs(1, resv, n);
}

int main()
{
    while(std::scanf("%d", &n) != EOF)
    {
        if(n == 0)
            break;
        read_reserv_tab();
        solve();
        std::printf("%d\n", ans);
    }
    return 0;
}
