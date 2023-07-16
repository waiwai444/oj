#include <stdio.h>
#include <string.h>
#include <algorithm>

int n, m;
char map[1000][1010];
int left[1000], up[1000];
int max[1000];
int cnt[2001];

void solve()
{
    int i, j, k, l;

    memset(cnt, 0, (n+m+1)*sizeof(int));
    for(j = 0; j < m; ++j)
        up[j] = -1;

    for(i = 0; i < n; ++i)
    {
        l = -1;
        for(j = 0; j < m; ++j)
            if(map[i][j] == '.')
            {
                left[j] = up[j]+1 == i ? l : std::max(l, left[j]);
                max[j] = i-up[j]+j-left[j];
                if(l < left[j])
                {
                    k = max[left[j]]+j-left[j];
                    if(max[j] < k)
                        max[j] = k;
                }
                ++cnt[max[j]];
            }
            else
            {
                up[j] = i;
                l = j;
            }
    }

    for(i = 1; i <= n+m; ++i)
        if(cnt[i])
            printf("%d x %d\n", cnt[i], i<<1);
}

int main()
{
    int tc, i;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d%d", &n, &m);
        fgets(map[0], sizeof(map[0]), stdin);
        for(i = 0; i < n; ++i)
        {
            fgets(map[i], sizeof(map[i]), stdin);
        }
        solve();
    }
    return 0;
}