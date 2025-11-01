#include <algorithm>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int n, m;
int north, south, west, east;

int64_t solve()
{
    int i, j, s, t, u, v;
    int64_t a, b, sum = 0;
    s = std::min(north, south) * 2;
    t = abs(north - south);
    if(north != south)
        ++s, --t;
    u = std::min(west, east) * 2;
    v = abs(west - east);
    if(west != east)
        ++u, --v;
    if(north + south == 0)
        t = -1;
    if(west + east == 0)
        v = -1;
    i = j = 0;
    while(i < t + 1 || j < v + 1)
    {
        a = b = -1;
        if(i == 0)
            a = (int64_t)(n - 1) * s;
        else if(i < t + 1)
            a = n - i - 1 >= 0 ? n - i - 1 : -1;
        if(j == 0)
            b = (int64_t)(m - 1) * u;
        else if(j < v + 1)
            b = m - j - 1 >= 0 ? m - j - 1 : -1;
        if(i < t + 1 && a >= b)
        {
            if(i == 0)
                sum += (int64_t)n * (m - j) + (int64_t)(n - 1) * (m - j) * (s - 1);
            else
                sum += (a + 1) * (m - j);
            ++i;
        }
        else
        {
            if(j == 0)
                sum += (int64_t)m * (n - i) + (int64_t)(m - 1) * (n - i) * (u - 1);
            else
                sum += (b + 1) * (n - i);
            ++j;
        }
    }
    return sum;
}

int main()
{
    int tc = 0;
    while(scanf("%d%d", &n, &m) != EOF)
    {
        if(n == 0)
            break;
        scanf("%d%d%d%d", &north, &south, &west, &east);
        printf("Case %d: %lld\n", ++tc, solve());
    }
    return 0;
}
