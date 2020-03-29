#include <cstdio>
#include <cstring>

int cnt[10];

int main()
{
    int i, t, n, m, d, c, r;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d", &n);
        memset(cnt, 0, sizeof(cnt));
        d = 1;
        m = n;
        while(m)
        {
            c = m/10;
            r = m%10;
            for(i = 0; i <= 9; i++)
                cnt[i] += c*d;
            for(i = 1; i <= r; i++)
                cnt[i] += d;
            cnt[r] -= (m+1)*d-1-n;
            m /= 10;
            d *= 10;
        }
        printf("%d", cnt[0]);
        for(i = 1; i <= 9; i++)
            printf(" %d", cnt[i]);
        printf("\n");
    }
    return 0;
}

