#include <stdio.h>

#define MAX 10000

int result[MAX];
int tmp[MAX/2];

void recur_calc(int first, int last)
{
	if(first+1 >= last)
		return;
	int i, j, k = 0;
	for(i = j = first; i <= last; i++)
	{
		if(i & 1)
			tmp[k++] = result[i];
		else
			result[j++] = result[i];
	}
	for(i = j; i <= last; i++)
		result[i] = tmp[i-j];
	recur_calc(first, j-1);
	recur_calc(j, last);
}

void pre_calc()
{
	for(int i = 0; i < MAX; i++)
		result[i] = i;
	recur_calc(0, MAX-1);
}

void solve(int n)
{
	printf("%d:", n);
	for(int i = 0; i < MAX; i++)
		if(result[i] < n)
			printf(" %d", result[i]);
	printf("\n");
}

int main()
{
	int n;
	pre_calc();
	while(scanf("%d", &n), n)
		solve(n);
	return 0;
}
