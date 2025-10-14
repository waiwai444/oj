#include <algorithm>
#include <stdint.h>
#include <stdio.h>

int n;

struct intv_t
{
    int a, b;
} intv[100001];

bool cmp(intv_t &r1, intv_t &r2)
{
    return r1.a < r2.a;
}

uint64_t bcd(uint64_t x, uint64_t y)
{
    if(y == 0)
        return x;
    return bcd(y, x % y);
}

void reduce(uint64_t x, uint64_t y, uint64_t *xo, uint64_t *yo)
{
    uint64_t d = bcd(x, y);
    *xo = x / d;
    *yo = y / d;
}

void solve()
{
    int i, j, k, b = 0;
    uint64_t p, q, pt, qt;
    std::sort(&intv[0], &intv[n], cmp);
    p = intv[0].b - intv[0].a;
    q = 1;
    for(i = 0; i < n; ++i)
    {
        pt = intv[i].a;
        qt = 1;
        for(j = i; j < n; ++j)
        {
            if(pt * q + p * qt <= intv[j].b * qt * q)
            {
                pt = pt * q + p * qt;
                qt = q * qt;
                reduce(pt, qt, &pt, &qt);
            }
            else
            {
                p = intv[j].b - intv[i].a;
                q = j - i + 1;
                reduce(p, q, &p, &q);
                pt = intv[j].b;
                qt = 1;
                b = j;
            }
            if((j + 1 < n && pt <= intv[j + 1].a * qt) || j == n - 1)
                break;
        }
        if(b > i)
        {
            pt = intv[i].a;
            qt = 1;
            for(k = i; k < b; ++k)
            {
                if(pt * q + p * qt <= intv[k + 1].a * qt * q)
                {
                    p = intv[b].b - intv[k + 1].a;
                    q = b - k;
                    reduce(p, q, &p, &q);
                    pt = intv[k + 1].a;
                    qt = 1;
                }
                else
                {
                    pt = pt * q + p * qt;
                    qt = qt * q;
                    reduce(pt, qt, &pt, &qt);
                }
            }
        }
        i = j;
    }
    printf("%d/%d\n", (int)p, (int)q);
}

int main()
{
    int i;
    while(scanf("%d", &n) != EOF)
    {
        for(i = 0; i < n; ++i)
        {
            scanf("%d%d", &intv[i].a, &intv[i].b);
        }
        solve();
    }
    return 0;
}
