#include <cstdio>

long long all[31];

void init()
{
    int i;
    all[0] = 1;
    for(i = 1; i <= 30; ++i)
        all[i] = all[i-1]*3;
}

long long solve(int k, int a, int b)
{
    if(k == 0)
        return 1;
    if(a == 1 && b == (1<<k))
        return all[k];
    if(a <= (1<<k)/2)
    {
        if(b <= (1<<k)/2)
            return 2*solve(k-1, a, b);
        else
        {
            long long ans = 2*solve(k-1, a, (1<<k)/2);
            return ans+solve(k-1, 1, b-(1<<k)/2);
        }
    }
    else
        return solve(k-1, a-(1<<k)/2, b-(1<<k)/2);
}

int main()
{
    int i, T, K, A, B;
    init();
    scanf("%d", &T);
    for(i = 1; i <= T; ++i)
    {
        scanf("%d%d%d", &K, &A, &B);
        printf("Case %d: %lld\n", i, solve(K, A, B));
    }
    return 0;
}
