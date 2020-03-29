#include <stdio.h>
#include <algorithm>

bool is_prime[1000000];
int nprimes;
int prime[200000];

void sieve()
{
    std::fill_n(is_prime, 1000000, true);
	is_prime[1] = false;
	long long i, j, t;
	for(i = 4; i < 1000000; i += 2)
		is_prime[i] = false;
	for(i = 3; i < 1000000; i += 2)
	{
		if(is_prime[i] == false)
			continue;
		j = i;
		while((t = i*j) < 1000000)
		{
			if(is_prime[t])
				is_prime[t] = false;
			j += 2;
		}
	}
	prime[0] = 2;
	nprimes = 1;
	for(i = 3; i < 1000000; i += 2)
		if(is_prime[i])
			prime[nprimes++] = i;
}

int main()
{
	int i, j, nfactors;
	long long n, factor[64];
	char output[1000], *ptr;
	sieve();
	while(scanf("%lld", &n), n > 0)
	{
		nfactors = 0;
		for(i = 0; i < nprimes; i++)
		{
			while(n%prime[i] == 0)
			{
				factor[nfactors++] = (long long)prime[i];
				n /= prime[i];
			}
		}
		if(n > 1)
			factor[nfactors++] = n;
		
		ptr = output;
		for(i = 0; i < nfactors; i++)
		{
			j = sprintf(ptr, "    %lld\n", factor[i]);
			ptr += j;
		}
		*ptr = '\0';
		printf("%s\n", output);
	}
	return 0;
}
