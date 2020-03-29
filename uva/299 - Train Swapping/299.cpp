#include <stdio.h>

int main()
{
	int n, l, i, j, r;
	int train[50];
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", &l);
		r = 0;
		for(i = 0; i < l; i++)
		{
			scanf("%d", &train[i]);
		}
		r = 0;
		for(i = 0; i < l; i++)
		{
			for(j = i+1; j < l; j++)
			{
				if(train[i] > train[j])
					r++;
			}
		}
		printf("Optimal train swapping takes %d swaps.\n", r);
	}
	return 0;
}