#include <cstdio>
#include <algorithm>

#define MAXN 1000000
#define SQRT_MAXN 1000
#define MAXNP 100000

bool is_pr[MAXN+1];
int pr[MAXNP], np;
int sq[SQRT_MAXN+1], nsq;
int mu[MAXN+1];
int m[MAXN+1];

void get_primes()
{
    int i, j;
    std::fill_n(is_pr, MAXN+1, true);
    pr[np++] = 2;
    for(i = 3; i <= MAXN; i += 2)
    {
        if(is_pr[i])
        {
            pr[np++] = i;
            if(i <= SQRT_MAXN)
                for(j = i; i*j <= MAXN; j += 2)
                    is_pr[i*j] = false;
        }
    }
}

void get_squares()
{
    for(int i = 2; i <= SQRT_MAXN; i++)
        sq[nsq++] = i*i;
}

void init()
{
    int i, j, k;
    get_primes();
    get_squares();
    for(i = 1; i <= MAXN; i++)
        mu[i] = 1;
    for(i = 0; i < np; i++)
    {
        for(j = 1; (k = pr[i]*j) <= MAXN; j++)
            mu[k] = -mu[k];
    }
    for(i = 0; i < nsq; i++)
    {
        for(j = 1; (k = sq[i]*j) <= MAXN; j++)
            mu[k] = 0;
    }
    m[1] = 1;
    for(i = 2; i <= MAXN; i++)
        m[i] = m[i-1]+mu[i];
}

int main()
{
    int n;
    init();
    while(scanf("%d", &n), n)
        printf("%8d%8d%8d\n", n, mu[n], m[n]);
    return 0;
}

