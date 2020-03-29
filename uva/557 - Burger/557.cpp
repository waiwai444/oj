#include <stdio.h>

double ans[50001];

void solve()
{
	int i, n;
	ans[1] = 0;
	for(i = 2; i <= 50000; i++)
	{
		n = 2*i;
		ans[i] = 1-(1-ans[i-1])*(n-2)*(n-3)/(n/2-1)/(n/2-1)/4;
	}
}

int main()
{
	int n, tc;
	solve();
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d", &n);
		printf("%.4f\n", ans[n/2]);
	}
	return 0;
}

