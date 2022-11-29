#include <cstdio>

#define MAXN 200000

int n;
int num[MAXN], fw[MAXN], bw[MAXN], min[MAXN+1];

int solve()
{
    int i, k, ans = 0;
    for(bw[0] = 1, i = 1; i < n; ++i)
        bw[i] = num[i] > num[i-1] ? bw[i-1]+1 : 1;
    for(fw[n-1] = 1, i = n-2; i >= 0; --i)
        fw[i] = num[i] < num[i+1] ? fw[i+1]+1 : 1;
    k = 0;
    for(i = 0; i < n; ++i)
    {
        int l = 1, h = k, m;
        while(l <= h)
        {
            m = (l+h)/2;
            if(min[m] >= num[i])
                h = m-1;
            else
                l = m+1;
        }
        if(h+fw[i] > ans)
            ans = h+fw[i];
        if(bw[i] > k)
            min[++k] = num[i];
        else if(min[bw[i]] > num[i])
            min[bw[i]] = num[i];
    }
    return ans;
}

int main()
{
    int i, z;
    scanf("%d", &z);
    while(z--)
    {
        scanf("%d", &n);
        for(i = 0; i < n; ++i)
            scanf("%d", &num[i]);
        printf("%d\n", solve());
    }
    return 0;
}

