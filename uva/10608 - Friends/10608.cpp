#include <cstdio>

int n, m;
int repr[30001];
int rank[30001];
int cnt[30001];

int find(int x)
{
    return repr[x] == x ? x : repr[x] = find(repr[x]);
}

void union_set(int x, int y)
{
    int rx = find(x), ry = find(y);
    if(rx == ry)
        return;
    if(rank[rx] >= rank[ry])
    {
        repr[ry] = rx;
        if(rank[rx] == rank[ry])
            ++rank[rx];
        cnt[rx] += cnt[ry];
    }
    else
    {
        repr[rx] = ry;
        cnt[ry] += cnt[rx];
    }
}

int main()
{
    int i, tc, u, v;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d%d", &n, &m);
        for(i = 1; i <= n; i++)
        {
            repr[i] = i;
            rank[i] = 0;
            cnt[i] = 1;
        }
        for(i = 0; i < m; i++)
        {
            scanf("%d%d", &u, &v);
            union_set(u, v);
        }
        int ans = 0;
        for(i = 1; i <= n; i++)
            if(cnt[i] > ans)
                ans = cnt[i];
        printf("%d\n", ans);
    }
    return 0;
}

