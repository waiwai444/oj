#include <stdint.h>
#include <stdio.h>

int n;
int num[100001];

struct rec_t
{
    int num;
    int left;
    uint64_t sum;
    rec_t(int num, int left, uint64_t sum)
        : num(num), left(left), sum(sum)
    {}
    rec_t() {}
};
rec_t st[100001];
int st_top;

void solve()
{
    int i;
    uint64_t s;
    uint64_t max = 0;
    int left = 0, right = 0, l;
    num[n] = 0;
    st_top = 0;
    st[st_top++] = rec_t(num[0], 0, num[0]);
    for(i = 1; i <= n; ++i)
    {
        if(num[i] > num[i - 1])
        {
            st[st_top++] = rec_t(num[i], i, num[i]);
        }
        else
        {
            s = 0;
            l = 0;
            while(st_top > 0 && st[st_top - 1].num >= num[i])
            {
                rec_t r = st[--st_top];
                s += r.sum;
                l = r.left;
                if(s * r.num > max)
                {
                    max = s * r.num;
                    left = l;
                    right = i - 1;
                }
            }
            st[st_top++] = rec_t(num[i], l, s + num[i]);
        }
    }

    printf("%llu\n", max);
    printf("%d %d\n", left + 1, right + 1);
}

int main()
{
    int i;
    bool first = true;
    while(scanf("%d", &n) != EOF)
    {
        for(i = 0; i < n; ++i)
            scanf("%d", &num[i]);
        if(first)
            first = false;
        else
            printf("\n");
        solve();
    }
    return 0;
}
