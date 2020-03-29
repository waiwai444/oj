#include <stdio.h>
#include <math.h>

int main()
{
	long long n, k, r, denom, num;
	while(scanf("%lld", &n) != EOF)
	{
		k = (long long)ceil((sqrt(8*(double)n+1)-1)/2);
		r = n-k*(k-1)/2;
		num = k-r+1;
		denom = r;
		printf("%lld/%lld\n", num, denom);
	}
	return 0;
}
