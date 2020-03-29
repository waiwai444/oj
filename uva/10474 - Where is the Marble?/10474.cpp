#include <stdio.h>
#include <string.h>

int main()
{
	int counter[10001];
	int acc[10001];
	int i, n, q, t, max_num, tc(0);
	while(scanf("%d%d", &n, &q), n || q)
	{
		memset(counter, 0, sizeof(counter));
		memset(acc, 0, sizeof(acc));
		max_num = 0;
		for(i = 0; i < n; i++)
		{
			scanf("%d", &t);
			counter[t]++;
			if(t > max_num)
				max_num = t;
		}
		for(i = 1; i <= max_num; i++)
		{
			acc[i] = acc[i-1]+counter[i-1];
		}
		printf("CASE# %d:\n", ++tc);
		for(i = 0; i < q; i++)
		{
			scanf("%d", &t);
			if(counter[t] > 0)
				printf("%d found at %d\n", t, acc[t]+1);
			else
				printf("%d not found\n", t);
		}
	}
	return 0;
}