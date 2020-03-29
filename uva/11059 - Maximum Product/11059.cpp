#include <cstdio>

int N;
int seq[18];

long long solve()
{
    int i, j;
    long long ans = 0, prod;
    for(i = 0; i < N; ++i)
    {
        if(seq[i] == 0)
            continue;
        prod = 1;
        for(j = i; j < N; ++j)
        {
            if(seq[j] == 0)
                break;
            prod *= seq[j];
            if(prod > ans)
                ans = prod;
        }
    }
    return ans;
}

int main()
{
    int i, tc = 0;
    while(std::scanf("%d", &N) != EOF)
    {
        for(i = 0; i < N; ++i)
            std::scanf("%d", &seq[i]);
        std::printf("Case #%d: The maximum product is %lld.\n\n", ++tc, solve());
    }
    return 0;
}

