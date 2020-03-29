#include <cstdio>
#include <climits>

long n, sp, sq;

int main()
{
    int i, j, a, b;
    long long k, qofs;
    while(scanf("%ld%ld%ld", &n, &sp, &sq) != EOF)
    {
        k = LLONG_MAX;
        for(i = 0; i < 32; i++)
        {
            for(j = 0; j < 32; j++)
            {
                qofs = (sp+(sp<<i))>>j;
                if(sq > qofs)
                    continue;
                qofs = (((n-1)*sp+(((n-1)*sp)<<i))>>j)+sq;
                if(qofs < k)
                {
                    k = qofs;
                    a = i, b = j;
                }
            }
        }
        printf("%lld %d %d\n", k, a, b);
    }
    return 0;
}

