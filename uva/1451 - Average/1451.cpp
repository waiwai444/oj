#include <cstdio>

#define MAXN 100000

int n, L;
char input[MAXN+2];
int sum[MAXN+1], p[MAXN];

int compare(int l1, int r1, int l2, int r2)
{
    return (sum[r1]-sum[l1])*(r2-l2)-(sum[r2]-sum[l2])*(r1-l1);
}

void solve()
{
    int i, j, k;
    int ans_l = 1, ans_r = L;

    for(i = 1; i <= n; ++i)
        sum[i] = sum[i-1]+input[i]-'0';

    j = k = 0;
    for(i = L+1; i <= n; ++i)
    {
        while(k > j && compare(p[k], i-L, p[k-1], p[k]) < 0)
            --k;
        p[++k] = i-L;
        while(j < k && compare(p[j], i, p[j+1], i) <= 0)
            ++j;
        int c = compare(p[j], i, ans_l-1, ans_r);
        if(c > 0 || c == 0 && i-p[j] < ans_r-ans_l+1)
            ans_l = p[j]+1, ans_r = i;
    }

    printf("%d %d\n", ans_l, ans_r);
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d%s", &n, &L, input+1);
        solve();
    }
    return 0;
}

