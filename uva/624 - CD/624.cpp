#include <stdio.h>
#include <string.h>

#define MAX 5000

int sp, nt, tr[20];
int v[MAX], dp[MAX];

void solve()
{
	int i, j, p = 1, q, t;
	v[0] = 0;
	memset(dp, 0, sizeof(dp));
	for(i = 0; i < nt; i++)
	{
		q = p;
		for(j = 0; j < p; j++)
		{
			t = v[j]+tr[i];
			if(t <= sp && dp[t] == 0)
			{
				v[q++] = t;
				dp[t] = dp[v[j]] | 1<<i;
			}
		}
		p = q;
	}
}

void output()
{
	int i, sum = 0;
	for(i = sp; i > 0; i--)
		if(dp[i] != 0)
		{
			sum = i;
			break;
		}
	for(i = 0; i < nt; i++)
		if((dp[sum] & 1<<i )!= 0)
			printf("%d ", tr[i]);
	printf("sum:%d\n", sum);
}

int main()
{
	int i;
	while(scanf("%d%d", &sp, &nt) != EOF)
	{
		for(i = 0; i < nt; i++)
			scanf("%d", &tr[i]);
		solve();
		output();
	}
	return 0;
}
