#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>

#define MAX 300000

long l, h;
long len[MAX+1];

void init()
{
    memset(len, -1, sizeof(len));
    len[1] = 0;
}

long compute(long x)
{
    if(x <= MAX && len[x] >= 0)
        return len[x];
    long t = (x&1) ? compute(3*x+1)+1 : compute(x/2)+1;
    return x <= MAX ? len[x] = t : t;
}

void solve()
{
    long i, longest = -1, r, t;
    if(l > h)
        std::swap(l, h);
    for(i = l; i <= h; i++)
    {
        if(i == 1)
            t = 3;
        else if(i <= MAX && len[i] >= 0)
            t = len[i];
        else
            t = compute(i);
        if(t > longest)
        {
            longest = t;
            r = i;
        }
    }
    printf("Between %ld and %ld, %ld generates the longest sequence of %ld values.\n", l, h, r, longest);
}

int main()
{
    init();
    while(scanf("%ld%ld", &l, &h), l || h)
        solve();
    return 0;
}

