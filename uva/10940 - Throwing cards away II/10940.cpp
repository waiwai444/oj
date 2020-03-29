#include <stdio.h>

int ans[500001];

void solve()
{
	int i;
	ans[1] = 1;
	for(i = 2; i <= 500000; i++)
	{
		if(i&1)
			ans[i] = ans[i/2] == i/2 ? 2 : (ans[i/2]+1)*2;
		else
			ans[i] = ans[i/2]*2;
	}
}

int main()
{
	int n;
	solve();
	while(scanf("%d", &n), n)
	{
		printf("%d\n", ans[n]);
	}
	return 0;
}

