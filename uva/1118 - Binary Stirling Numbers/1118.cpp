#include <cstdio>

using namespace std;

int n, m;

int count(int block, int col)
{
    if(block == 1 && col == 1)
        return 1;
    int b = block>>1;
    if(col > b)
        return count(b, col-b);
    return count(b, col)<<1;
}

bool solve()
{
    int i, c, r;
    c = (m+1)/2-1;
    if(c == 0)
        return 1;
    r = n-m+1;
    int s = 0;
    int p = 1<<30;
    while(r)
    {
        int b = 0;
        for(; p; p >>= 1)
        {
            if(c&p)
            {
                b = c > p ? p<<1 : p;
                break;
            }
        }
        int half = b>>1;
        int t = (r+half)/b;
        if(t)
            s += t*count(b, c);
        r %= b;
        if(r >= half)
            break;
        b = half;
        c -= b;
    }
    return s&1;
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &m);
        printf("%d\n", solve());
    }
    return 0;
}

