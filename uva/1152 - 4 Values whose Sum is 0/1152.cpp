#include <stdio.h>
#include <utility>

int n;
int li[4][4000];
const int hash_mask = 0xffffff;

std::pair<int, int> hash_table[hash_mask+1];

int find_hash_pos(int x)
{
    int h = x&hash_mask;
    while (hash_table[h].second > 0 && hash_table[h].first != x)
        h = (h+1)&hash_mask;
    return h;
}

long long solve()
{
    int i, j, h, x;
    long long res = 0;

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
        {
            x = li[0][i]+li[1][j];
            h = find_hash_pos(x);
            hash_table[h].first = x;
            ++hash_table[h].second;
        }

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
        {
            x = li[2][i]+li[3][j];
            h = find_hash_pos(-x);
            res += hash_table[h].second;
        }

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
        {
            x = li[0][i]+li[1][j];
            h = find_hash_pos(x);
            while (hash_table[h].second > 0)
            {
                hash_table[h].second = 0;
                h = (h+1)&hash_mask;
            }
        }

    return res;
}

int main()
{
    int i, t;
    long long ans;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (i = 0; i < n; ++i)
            scanf("%d%d%d%d", &li[0][i], &li[1][i], &li[2][i], &li[3][i]);
        ans = solve();
        printf("%lld\n", ans);
        if (t)
            putchar('\n');
    }
    return 0;
}