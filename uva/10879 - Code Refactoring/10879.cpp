#include <stdio.h>

int main()
{
	int i, tc, c, n;
	scanf("%d", &tc);
	for(c = 1; c <= tc; c++)
	{
		scanf("%d", &n);
		printf("Case #%d: %d = ", c, n);
		if(n%2 == 0)
		{
			printf("%d * %d = ", 2, n/2);
			for(i = 3; i < n; i++)
				if(n%i == 0)
				{
					printf("%d * %d\n", i, n/i);
					break;
				}
		}
		else
		{
			for(i = 3; ; i += 2)
				if(n%i == 0)
				{
					printf("%d * %d = ", i, n/i);
					break;
				}
			for(i += 2; ; i += 2)
				if(n%i == 0)
				{
					printf("%d * %d\n", i, n/i);
					break;
				}
		}
	}
	return 0;
}