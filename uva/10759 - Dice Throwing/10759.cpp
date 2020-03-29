#include <stdio.h>

int n, x;
long long total[25];
long long cnt[25][151][2];

long long gcd(long long x, long long y)
{
	return y == 0 ? x : gcd(y, x%y);
}

void solve()
{
	int i, j, k;
	long long d;
	total[0] = 1;
	for(i = 1; i <= 24; i++)
		total[i] = total[i-1]*6;
	cnt[0][0][0] = 1;
	for(i = 1; i <= 24; i++)
		for(j = 6*i; j > 0; j--)
			for(k = 1; k <= 6 && k <= j; k++)
				cnt[i][j][0] += cnt[i-1][j-k][0];
	for(i = 1; i <= 24; i++)
		for(j = 6*i; j >= 0; j--)
			cnt[i][j][0] += cnt[i][j+1][0];
	for(i = 1; i <= 24; i++)
	{
		for(j = 6*i; j >= 0; j--)
		{
			d = gcd(total[i], cnt[i][j][0]);
			cnt[i][j][0] /= d;
			cnt[i][j][1] = total[i]/d;
		}
	}
}

int main()
{
	solve();
	while(scanf("%d%d", &n, &x), n)
	{
		if(cnt[n][x][1] == 1)
			printf("1\n");
		else if(cnt[n][x][0] == 0)
			printf("0\n");
		else
			printf("%lld/%lld\n", cnt[n][x][0], cnt[n][x][1]);
	}
	return 0;
}

