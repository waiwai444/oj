#include <stdio.h>

int main()
{
	int n;
	while(scanf("%d", &n), n >= 0)
		printf("%lld\n", (long long)n*(n+1)/2+1);
	return 0;
}

