#include <stdio.h>

int n;
int ans[11];

void solve()
{
	int i, j, u;
	ans[0] = ans[1] = 1;
	for(i = 2; i <= 10; i++)
	{
		u = 2*i;
		for(j = 1; j < u; j += 2)
		{
			ans[i] += ans[(j-1)/2]*ans[(u-j-1)/2];
		}
	}
}

int main()
{
	bool first = true;
	solve();
	while(scanf("%d", &n) != EOF)
	{
		if(first)
			first = false;
		else
			printf("\n");
		printf("%d\n", ans[n]);
	}
	return 0;
}

