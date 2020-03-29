#include <cstdio>

#define MAXN 1e7

using namespace std;

int exgcd(int a, int b, int *x, int *y)
{
    if(b == 0)
    {
        *x = 1, *y = 0;
        return a;
    }
    int r = exgcd(b, a%b, x, y);
    int t = *x;
    *x = *y;
    *y = t-(a/b)*(*y);
    return r;
}

int solve(int a, int b)
{
    int d, x, y, sum = 0;
    if(a == 0 || b == 0) // a+b>0
        return MAXN+1;
    d = exgcd(a, b, &x, &y);
    int ad = a/d, bd = b/d;

    int k1 = -x/bd;
    if(x+(long long)k1*bd < 0)
        ++k1;
    int k2 = (MAXN-x)/bd;
    if(x+(long long)k2*bd > MAXN)
        --k2;
    if(y-(long long)k1*ad > 0)
    {
        k1 = y/ad;
        if(y-(long long)k1*ad > 0)
            ++k1;
    }
    if(y-(long long)k2*ad < -MAXN)
    {
        k2 = (y+MAXN)/ad;
        if(y-(long long)k2*ad < -MAXN)
            --k2;
    }
    if(k1 <= k2)
        sum += k2-k1+1;

    k1 = (-MAXN-x)/bd;
    if(x+(long long)k1*bd < -MAXN)
        ++k1;
    k2 = -x/bd;
    if(x+(long long)k2*bd > 0)
        --k2;
    if(y-(long long)k1*ad > MAXN)
    {
        k1 = (y-MAXN)/ad;
        if(y-(long long)k1*ad > MAXN)
            ++k1;
    }
    if(y-(long long)k2*ad < 0)
    {
        k2 = y/ad;
        if(y-(long long)k2*ad < 0)
            --k2;
    }
    if(k1 <= k2)
        sum += k2-k1+1;
    return sum;
}

int main()
{
    int a, b;
    while(scanf("%d%d", &a, &b), a || b)
    {
        printf("%d\n", solve(a, b));
    }
    return 0;
}

