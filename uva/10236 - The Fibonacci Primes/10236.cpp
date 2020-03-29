#include <stdio.h>
#include <math.h>

#define MAXN 250000
#define MAXP 22000
#define MAXSF 45
#define THRESHOLD 1e10

int n;
int prime[MAXP];
bool ispri[MAXN];
int fib[MAXN];

int extract(long double x)
{
	while(x >= 1e9)
		x /= 10;
	while(x < 1e8)
		x *= 10;
	return (int)x;
}

void get_fibs()
{
	int i;
	long double x, y, z;
	fib[1] = 1;
	for(i = 2; i < MAXSF; i++)
		fib[i] = fib[i-1]+fib[i-2];
	x = fib[i-2];
	y = fib[i-1];
	for(; i < MAXN; i++)
	{
		z = x+y;
		fib[i] = extract(z);
		x = y;
		y = z;
		if(x >= THRESHOLD)
		{
			x /= THRESHOLD;
			y /= THRESHOLD;
		}
	}
}

void get_primes()
{
	int i, j, k, p, m;
	ispri[2] = true;
	prime[0] = 2;
	for(i = 3; i < MAXN; i += 2)
		ispri[i] = true;
	m = sqrt(MAXN);
	for(i = 3, p = 1; i <= m ; i += 2)
	{
		if(ispri[i])
		{
			prime[p++] = i;
			j = i;
			while((k = i*j) < MAXN)
			{
				ispri[k] = false;
				j += 2;
			}
		}
	}
	for(; i < MAXN; i += 2)
		if(ispri[i])
			prime[p++] = i;
}

int main()
{
	get_fibs();
	get_primes();
	while(scanf("%d", &n) != EOF)
	{
		if(n == 1 || n == 2)
			printf("%d\n", n+1);
		else
			printf("%d\n", fib[prime[n-1]]);
	}
	return 0;
}

