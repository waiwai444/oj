#include <stdio.h>

int main()
{
	long long x, y;
	while(scanf("%lld%lld", &x, &y) != EOF)
	{
		if(y >= x)
			printf("%lld\n", y-x);
		else
			printf("%lld\n", x-y);
	}
	return 0;
}
