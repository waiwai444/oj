#include <cstdio>
#include <cstdlib>

int n;
int tup[15];

bool zero()
{
    for(int i = 0; i < n; ++i)
        if(tup[i])
            return false;
    return true;
}

void next()
{
    int i, t;
    t = tup[0];
    for(i = 0; i < n-1; ++i)
        tup[i] = abs(tup[i]-tup[i+1]);
    tup[n-1] = abs(tup[n-1]-t);
}

int solve()
{
    int i;
    if(n == 4 || n == 8)
        return 0;
    if(zero())
        return 0;
    for(i = 1; i <= 1000; ++i)
    {
        next();
        if(zero())
            return 0;
    }
    return 1;
}

int main()
{
    int i, tc;
    scanf("%d", &tc);
    while(tc--)
    {
        scanf("%d", &n);
        for(i = 0; i < n; ++i)
            scanf("%d", &tup[i]);
        if(solve())
            puts("LOOP");
        else
            puts("ZERO");
    }
    return 0;
}

