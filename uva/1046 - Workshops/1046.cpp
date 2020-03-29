#include <cstdio>
#include <cstring>
#include <algorithm>

int nw, nr;
struct workshop_t { int p, d; } ws[1000];
struct room_t { int s, t; } rm[1000];
bool used[1000];

int ans_t, ans_p;

bool cmp_ws(const workshop_t &w1, const workshop_t &w2)
{
    return w1.p > w2.p;
}

bool cmp_rm(const room_t &r1, const room_t &r2)
{
    return r1.s > r2.s;
}

void solve()
{
    int i, j, k, min_t;
    ans_t = ans_p = 0;
    memset(used, false, sizeof(used));
    std::sort(&ws[0], &ws[nw], cmp_ws);
    std::sort(&rm[0], &rm[nr], cmp_rm);
    for(i = 0; i < nw; i++)
    {
        k = -1, min_t = 999;
        for(j = 0; j < nr; j++)
        {
            if(rm[j].s < ws[i].p)
                break;
            if(!used[j] && rm[j].t >= ws[i].d && rm[j].t < min_t)
            {
                min_t = rm[j].t;
                k = j;
            }
        }
        if(k >= 0)
        {
            used[k] = true;
        }
        else
        {
            ++ans_t;
            ans_p += ws[i].p;
        }
    }
}

int main()
{
    int i, hh, mm, tc = 0;
    while(scanf("%d", &nw), nw)
    {
        for(i = 0; i < nw; i++)
            scanf("%d%d", &ws[i].p, &ws[i].d);
        scanf("%d", &nr);
        for(i = 0; i < nr; i++)
        {
            scanf("%d%d:%d", &rm[i].s, &hh, &mm);
            rm[i].t = (hh-14)*60+mm;
        }
        solve();
        printf("Trial %d: %d %d\n\n", ++tc, ans_t, ans_p);
    }
    return 0;
}

