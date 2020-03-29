#include <stdio.h>

int main()
{
	int a, b, c = 0;
	while(scanf("%d%d", &a, &b), a)
		printf("Case %d: %lld\n", ++c, (long long)a*(a-1)/2*b*(b-1)/2);
	return 0;
}
