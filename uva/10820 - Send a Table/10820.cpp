#include <stdio.h>

#define MAX 50001

int cnt[MAX];

void solve()
{
	int i, j;
	cnt[1] = 1;
	for(i = 2; i < MAX; i++)
	{
		if(cnt[i] == 0)
		{
			cnt[i] = i-1;
			for(j = i+i; j < MAX; j += i)
			{
				if(cnt[j] == 0)
					cnt[j] = j;
				cnt[j] = cnt[j]/i*(i-1);
			}
		}
		cnt[i] = cnt[i]*2+cnt[i-1];
	}
}

int main()
{
	int n;
	solve();
	while(scanf("%d", &n), n)
		printf("%d\n", cnt[n]);
	return 0;
}
