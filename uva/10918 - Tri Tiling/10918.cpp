#include <stdio.h>

int n;
int ans[31];

void solve()
{
	int i, j;
	ans[0] = 1;
	for(i = 2; i <= 30; i += 2)
	{
		ans[i] = 3*ans[i-2];
		for(j = i-4; j >= 0; j -= 2)
		{
			ans[i] += 2*ans[j];
		}
	}
}

int main()
{
	solve();
	while(scanf("%d", &n), n >= 0)
	{
		printf("%d\n", ans[n]);
	}
	return 0;
}

