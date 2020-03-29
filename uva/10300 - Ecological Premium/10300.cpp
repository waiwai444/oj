#include <stdio.h>

int main()
{
	int n, f, size, animal, env, sum;
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", &f);
		sum = 0;
		while(f--)
		{
			scanf("%d%d%d", &size, &animal, &env);
			sum += size*env;
		}
		printf("%d\n", sum);
	}
	return 0;
}
