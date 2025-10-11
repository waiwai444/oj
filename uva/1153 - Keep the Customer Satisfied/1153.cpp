#include <algorithm>
#include <queue>
#include <stdio.h>

int n;

struct order_t
{
    int q, d;
} orders[800001];

bool cmp(order_t &j1, order_t &j2)
{
    return j1.d < j2.d;
}

void solve()
{
    int i, d = 0;
    std::priority_queue<int> pq;
    std::sort(&orders[0], &orders[n], cmp);
    for(i = 0; i < n; ++i)
    {
        if(d + orders[i].q > orders[i].d)
        {
            if(pq.size() > 0 && orders[i].q < pq.top())
            {
                d -= pq.top();
                pq.pop();
                d += orders[i].q;
                pq.push(orders[i].q);
            }
        }
        else
        {
            d += orders[i].q;
            pq.push(orders[i].q);
        }
    }
    printf("%d\n", (int)pq.size());
}

int main()
{
    int i, tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d", &n);
        for(i = 0; i < n; ++i)
            scanf("%d%d", &orders[i].q, &orders[i].d);
        solve();
        if(tc)
            printf("\n");
    }
    return 0;
}
