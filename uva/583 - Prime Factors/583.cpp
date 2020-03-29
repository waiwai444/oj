#include <cstdio>

char is_prime[50000];
int np, prime_list[50000];

void get_all_prime_list()
{
    int i, j;
    for(i = 3; i < 50000; i += 2)
        is_prime[i] = 1;
    for(i = 3; i < 50000; i += 2)
    {
        if(!is_prime[i])
            continue;
        for(j = i+i; j < 50000; j += i)
            is_prime[j] = 0;
    }
    prime_list[np++] = 2;
    for(i = 3; i < 50000; i += 2)
        if(is_prime[i])
            prime_list[np++] = i;
}

int main()
{
    int i, n;
    bool f;
    get_all_prime_list();
    while(std::scanf("%d", &n) != EOF && n)
    {
        std::printf("%d =", n);
        f = true;
        if(n < 0)
        {
            std::printf(" -1");
            f = false;
            n = -n;
        }
        for(i = 0; i < np; ++i)
        {
            if(prime_list[i]*prime_list[i] > n)
                break;
            while(n%prime_list[i] == 0)
            {
                if(f)
                    f = false;
                else
                    std::printf(" x");
                std::printf(" %d", prime_list[i]);
                n /= prime_list[i];
            }
        }
        if(n > 1)
        {
            if(!f)
                std::printf(" x");
            std::printf(" %d", n);
        }
        std::putchar('\n');
    }
    return 0;
}
