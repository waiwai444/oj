#include <cstdio>
#include <cstring>
#include <algorithm>

int n, m;
int q[100], p[100];
int f, b;

inline void incr(int &x)
{
    if(++x >= n)
        x = 0;
}

int solve()
{
    int l, u, ans = 1;
    bool t;
    memcpy(p, q, sizeof(q));
    std::sort(&p[0], &p[n]);
    q[m] = -q[m];
    f = 0, b = l = n-1;
    for(;;)
    {
        u = q[f], t = u < 0 ? u = -u, true : false;
        if(u < p[l])
            incr(b), q[b] = q[f];
        else
        {
            if(t)
                break;
            ++ans, --l;
        }
        incr(f);
    }
    return ans;
}

int main()
{
    int i, tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d%d", &n, &m);
        for(i = 0; i < n; ++i)
            scanf("%d", &q[i]);
        printf("%d\n", solve());
    }
    return 0;
}

