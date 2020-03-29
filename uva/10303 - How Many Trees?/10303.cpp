#include <stdio.h>

struct biguint
{
	int d[1000];
	int m;
};

biguint ans[1001];

void solve()
{
	int i, j;
	ans[0].d[0] = 1;
	ans[0].m = 0;
	for(i = 1; i <= 1000; i++)
	{
		ans[i].m = -1;
		for(j = 0; j <= ans[i-1].m; j++)
		{
			ans[i].d[j] += ans[i-1].d[j]*(4*i-2);
			ans[i].d[j+1] += ans[i].d[j]/10;
			ans[i].d[j] %= 10;
		}
		while(ans[i].d[j] > 0)
		{
			ans[i].d[j+1] += ans[i].d[j]/10;
			ans[i].d[j] %= 10;
			j++;
		}
		for(j--; j >= 0; j--)
		{
			ans[i].d[j-1] += ans[i].d[j]%(i+1)*10;
			ans[i].d[j] /= (i+1);
			if(ans[i].m < 0 && ans[i].d[j] > 0)
				ans[i].m = j;
		}
	}
}

void print_biguint(const biguint &x)
{
	char d[1000];
	for(int i = x.m; i >= 0; i--)
		d[x.m-i] = x.d[i]+'0';
	d[x.m+1] = '\0';
	printf("%s\n", d);
}

int main()
{
	int n;
	solve();
	while(scanf("%d", &n) != EOF)
	{
		print_biguint(ans[n]);
	}
	return 0;
}

