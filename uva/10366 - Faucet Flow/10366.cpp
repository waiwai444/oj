#include <cstdio>

int left, right;
int div[1000];

inline int divh(int d)
{
    return div[(d-left)/2];
}

inline void left_highest(int from, int *l, int *h)
{
    *h = 0;
    for(int i = from; i >= left; i -= 2)
        if(divh(i) > *h)
            *l = i, *h = divh(i);
}

inline void right_highest(int from, int *r, int *h)
{
    *h = 0;
    for(int i = from; i <= right; i += 2)
        if(divh(i) > *h)
            *r = i, *h = divh(i);
}

int solve()
{
    int i, l, r, hl, hr, t = 0;
    left_highest(-1, &l, &hl);
    right_highest(1, &r, &hr);
    if(hl < hr)
    {
        r = 0;
        for(i = 1; i <= right; i += 2)
        {
            if(r == 0 && divh(i) >= hl)
                r = i;
            if(divh(i) > hl)
                break;
        }
        t += (r-l)*hl;
        int tr = (i-r)*hl*2;
        while(l != left)
        {
            int l2 = l;
            left_highest(l-2, &l, &hl);
            if(tr > 0)
            {
                int t2 = (l2-l)*hl*2;
                t += t2 <= tr ? t2 : tr+(t2-tr)/2;
                tr -= t2;
            }
            else
                t += (l2-l)*hl;
        }
    }
    else if(hl > hr)
    {
        l = 0;
        for(i = -1; i >= left; i -= 2)
        {
            if(l == 0 && divh(i) >= hr)
                l = i;
            if(divh(i) > hr)
                break;
        }
        t += (r-l)*hr;
        int tl = (l-i)*hr*2;
        while(r != right)
        {
            int r2 = r;
            right_highest(r+2, &r, &hr);
            if(tl > 0)
            {
                int t2 = (r-r2)*hr*2;
                t += t2 <= tl ? t2 : tl+(t2-tl)/2;
                tl -= t2;
            }
            else
                t += (r-r2)*hr;
        }
    }
    else
    {
        t += (r-l)*hl;
        int tl = 0;
        while(l != left)
        {
            int l2 = l;
            left_highest(l-2, &l, &hl);
            tl += (l2-l)*hl*2;
        }
        int tr = 0;
        while(r != right)
        {
            int r2 = r;
            right_highest(r+2, &r, &hr);
            tr += (r-r2)*hr*2;
        }
        t += tl <= tr ? tl : tr;
    }
    return t;
}

int main()
{
    int i, nd;
    while(scanf("%d%d", &left, &right), left)
    {
        nd = (right+1)/2+(-left+1)/2;
        for(i = 0; i < nd; i++)
            scanf("%d", &div[i]);
        printf("%d\n", solve());
    }
    return 0;
}

