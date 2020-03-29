#include <stdio.h>
#include <algorithm>

bool prime[32768];

void prime_sieve()
{
	int i, j;
    std::fill_n(prime, sizeof(prime)/sizeof(bool), true);
	prime[1] = false;
	for(i = 4; i < 32768; i += 2)
		prime[i] = false;
	for(i = 3; i < 182; i += 2)
	{
		if(prime[i])
		{
			j = i;
			while(i*j < 32768)
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
	int i, n, t, cnt;
	prime_sieve();
	while(scanf("%d", &n), n)
	{
		if(n == 4)
		{
			printf("1\n");
			continue;
		}
		t = n/2;
		cnt = 0;
		for(i = 3; i <= t; i += 2)
		{
			if(prime[i] && prime[n-i])
				cnt++;
		}
		printf("%d\n", cnt);
	}
	return 0;
}
