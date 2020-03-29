#include <stdio.h>
#include <math.h>
#include <algorithm>

bool prime[801];
int largest_prime_factor[801];
int largest_prime_pow[801];

void sieve()
{
    std::fill_n(prime, 801, true);
	prime[1] = false;
	int i, j, t;
	for(i = 4; i <= 800; i += 2)
		prime[i] = false;
	for(i = 3; i < 800; i += 2)
	{
		if(!prime[i])
			continue;
		j = i;
		while((t = i*j) < 800)
		{
			prime[t] = false;
			j += 2;
		}
	}
}

int main()
{
	int i, n, b, ndigits, ntzeros, mp, t;
	double ls;
	sieve();
	while(scanf("%d%d", &n, &b) != EOF)
	{
		if(n > 0)
		{
			ls = 0;
			for(i = 1; i <= n; i++)
				ls += log((double)i)/log((double)b);
			ndigits = (int)ceil(ls+(1e-9));
		}
		else
			ndigits = 1;

		if(largest_prime_factor[b] == 0)
		{
			for(i = b; i > 0; i--)
				if(prime[i] && b%i == 0)
					break;
			largest_prime_factor[b] = i;
			t = b;
			while(t%largest_prime_factor[b] == 0)
			{
				t /= largest_prime_factor[b];
				largest_prime_pow[b]++;
			}
		}
		
		mp = largest_prime_factor[b];
		ntzeros = 0;
		for(i = 2; i <= n; i++)
		{
			t = i;
			while(t%mp == 0)
			{
				t /= mp;
				ntzeros++;
			}
		}
		ntzeros /= largest_prime_pow[b];

		printf("%d %d\n", ntzeros, ndigits);
	}
	return 0;
}
