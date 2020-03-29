#include <stdio.h>

struct biguint
{
	char d[1000];
	int len;
} ans[2001], sum;
int n;

void solve()
{
	int i, j, k;
	char c;
	ans[0].d[0] = ans[1].d[0] = 1;
	ans[0].len = ans[1].len = 1;
	sum.d[0] = 2;
	sum.len = 1;
	for(i = 2; i <= 2000; i++)
	{
		for(j = 0; j < ans[i-1].len; j++)
			ans[i].d[j] = ans[i-1].d[j];
		ans[i].len = ans[i-1].len;
		c = 0;
		for(j = 0; j < sum.len; j++)
		{
			ans[i].d[j] += sum.d[j]+c;
			if(ans[i].d[j] >= 10)
			{
				c = ans[i].d[j]/10;
				ans[i].d[j] %= 10;
			}
			else
				c = 0;
		}
		if(c > 0)
			ans[i].d[j++] = c;
		ans[i].len = j;
		c = 0;
		for(j = 0; j < ans[i].len; j++)
		{
			sum.d[j] += ans[i].d[j]+c;
			if(sum.d[j] >= 10)
			{
				c = sum.d[j]/10;
				sum.d[j] %= 10;
			}
			else
				c = 0;
		}
		if(c > 0)
			sum.d[j++] = c;
		sum.len = j;
	}
}

void print_ans()
{
	int i;
	char buf[1001];
	for(i = 0; i < ans[n].len; i++)
		buf[i] = ans[n].d[ans[n].len-i-1]+'0';
	buf[i] = '\0';
	printf("%s\n", buf);
}

int main()
{
	solve();
	while(scanf("%d", &n), n)
	{
		print_ans();
	}
	return 0;
}

