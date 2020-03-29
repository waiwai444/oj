#include <stdio.h>
#include <algorithm>

int n, deg[10000];
int pre_sum[10000];

bool cmp(int x, int y)
{
	return x > y;
}

bool is_graphic()	// Erdos-Gallai theorem
{
	int i, k, sum = 0;
	for(i = 0; i < n; i++)
		sum += deg[i];
	if(sum & 1)
		return false;
	
	std::sort(deg, deg+n, cmp);
	while(deg[n-1] == 0)
		n--;
	
	pre_sum[0] = deg[0];
	for(i = 1; i < n; i++)
		pre_sum[i] = pre_sum[i-1]+deg[i];
	
	for(k = 1; k <= n; k++)
	{
		sum = k*(k-1);
		for(i = k+1; i <= n; i++)
			sum += (deg[i-1] < k ? deg[i-1] : k);
		if(pre_sum[k-1] > sum)
			return false;
	}
	
	return true;
}

int main()
{
	int i;
	while(scanf("%d", &n), n)
	{
		for(i = 0; i < n; i++)
			scanf("%d", &deg[i]);
		if(is_graphic())
			printf("Possible\n");
		else
			printf("Not possible\n");
	}
	return 0;
}
