#include <stdint.h>
#include <stdio.h>
#include <unordered_map>

#define MAXSTATE 13000

int64_t c;
int m, n, k;
struct stock_t
{
    char name[6];
    int k;
    int64_t price[100];
} stock[8];

struct dp_value_t
{
    int64_t cash;
    int from;
    int act;
};

dp_value_t dp[101][MAXSTATE];
int max_idx;
std::unordered_map<int, int> state2idx;
int idx2state[MAXSTATE];
int next_buy_sidx[MAXSTATE][8];
int next_sell_sidx[MAXSTATE][8];

int64_t parse_currency(const char *str)
{
    int64_t v = 0;
    const char *p;
    for(p = str; *p && *p != '.'; ++p)
        v = v*10+*p-'0';
    v *= 100;
    if(*p == '.')
    {
        if(*(p+1))
        {
            v += (*(p+1)-'0')*10;
            if(*(p+2))
                v += *(p+2)-'0';
        }
    }
    return v;
}

void assign_state_index(int total_cnt, int cur_stock, int cur_state)
{
    if(total_cnt == k || cur_stock == n)
    {
        state2idx[cur_state] = max_idx;
        idx2state[max_idx] = cur_state;
        ++max_idx;
        return;
    }
    for(int i = 0; i <= stock[cur_stock].k; ++i)
    {
        if(total_cnt+i > k)
            break;
        assign_state_index(total_cnt+i, cur_stock+1, cur_state|(i<<cur_stock*4));
    }
}

void init()
{
    int i, j;
    state2idx.clear();
    max_idx = 0;
    assign_state_index(0, 0, 0);
    for(i = 0; i < max_idx; ++i)
    {
        int cur_state = idx2state[i];
        for(j = 0; j < n; ++j)
        {
            next_buy_sidx[i][j] = next_sell_sidx[i][j] =  -1;
            int next_state = cur_state+(1<<j*4);
            if(state2idx.find(next_state) != state2idx.end())
                next_buy_sidx[i][j] = state2idx[next_state];
            next_state = cur_state-(1<<j*4);
            if(state2idx.find(next_state) != state2idx.end())
                next_sell_sidx[i][j] = state2idx[next_state];
        }
    }
}

void print_actions(int day, int sidx)
{
    if(day > 1)
        print_actions(day-1, dp[day][sidx].from);
    if(dp[day][sidx].act > 0)
        printf("BUY %s\n", stock[dp[day][sidx].act-1].name);
    else if(dp[day][sidx].act < 0)
        printf("SELL %s\n", stock[-dp[day][sidx].act-1].name);
    else
        puts("HOLD");
}

void solve()
{
    int i, j, s;
    init();
    for(i = 0; i <= m; ++i)
        for(j = 0; j < max_idx; ++j)
            dp[i][j] = dp_value_t{-1, 0, 0};
    dp[0][0] = dp_value_t{c, 0, 0};
    for(i = 0; i < m; ++i)
    {
        for(s = 0; s < max_idx; ++s)
        {
            auto &v = dp[i][s];
            if(v.cash < 0)
                continue;
            if(dp[i+1][s].cash < v.cash)
                dp[i+1][s] = dp_value_t{v.cash, s, 0};
            for(j = 0; j < n; ++j)
            {
                int64_t tp = stock[j].price[i];
                int next_sidx = next_buy_sidx[s][j];
                if(next_sidx >= 0 && v.cash >= tp && dp[i+1][next_sidx].cash < v.cash-tp)
                    dp[i+1][next_sidx] = dp_value_t{v.cash-tp, s, j+1};
                next_sidx = next_sell_sidx[s][j];
                if(next_sidx >= 0 && dp[i+1][next_sidx].cash < v.cash+tp)
                    dp[i+1][next_sidx] = dp_value_t{v.cash+tp, s, -(j+1)};
            }
        }
    }
    printf("%lld.%02d\n", dp[m][state2idx[0]].cash/100, (int)(dp[m][state2idx[0]].cash%100));
    print_actions(m, state2idx[0]);
}

int main()
{
    int i, j, s;
    char str[16];
    bool first = true;
    while(scanf("%s%d%d%d", str, &m, &n, &k) != EOF)
    {
        if(first)
            first = false;
        else
            putchar('\n');
        c = parse_currency(str);
        for(i = 0; i < n; ++i)
        {
            scanf("%s%d%d", stock[i].name, &s, &stock[i].k);
            for(j = 0; j < m; ++j)
            {
                scanf("%s", str);
                stock[i].price[j] = parse_currency(str)*s;
            }
        }
        solve();
    }
    return 0;
}
