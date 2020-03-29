#include <stdio.h>

int main()
{
	long long n, s2, r2, s3, r3, s4, r4;
	while(scanf("%lld", &n) != EOF)
	{
		s2 = n*(n+1)*(2*n+1)/6;
		r2 = (n+1)*(n+1)*n*n/4-s2;
		s3 = s2+r2;
		r3 = s3*(n+1)*n/2-s3;
		s4 = n*(n*n*(n*(6*n+15)+10)-1)/30;
		r4 = (r3+s3)*(n+1)*n/2-s4;
		printf("%lld %lld %lld %lld %lld %lld\n", s2, r2, s3, r3, s4, r4);
	}
	return 0;
}
