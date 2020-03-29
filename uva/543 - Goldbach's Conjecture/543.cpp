#include <stdio.h>
#include <algorithm>

bool prime[1000000];

void prime_sieve()
{
	int i, j;
    std::fill(prime, prime+1000000, true);
	prime[1] = false;
	for(i = 4; i < 1000000; i += 2)
		prime[i] = false;
	for(i = 3; i < 1000; i += 2)
	{
		if(prime[i])
		{
			j = i;
			while(i*j < 1000000)
			{
				if(prime[i*j])
					prime[i*j] = false;
				j += 2;
			}
		}
	}
}

int main()
{
	int i, n, t;
	prime_sieve();
	while(scanf("%d", &n), n)
	{
		t = n/2;
		for(i = 3; i <= t; i += 2)
		{
			if(prime[i] && prime[n-i])
			{
				printf("%d = %d + %d\n", n, i, n-i);
				break;
			}
		}
		if(i > t)
			printf("Goldbach's conjecture is wrong.\n");
	}
	return 0;
}
