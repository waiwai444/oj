#include <stdio.h>

struct biguint
{
	char d[100];
	int m;
} ans[251];

void add(biguint *px, const biguint *py)
{
	int i, m = px->m >= py->m ? px->m : py->m;
	char c = 0;
	for(i = 0; i < m; i++)
	{
		px->d[i] += py->d[i]+c;
		if(px->d[i] >= 10)
		{
			px->d[i] -= 10;
			c = 1;
		}
		else
			c = 0;
	}
	if(c > 0)
		px->d[i++] = c;
	px->m = i;
}

void print_ans(int n)
{
	int i;
	static char buf[101];
	for(i = 0; i < ans[n].m; i++)
	{
		buf[ans[n].m-1-i] = ans[n].d[i]+'0';
	}
	buf[i] = '\0';
	printf("%s\n", buf);
}

void solve()
{
	int i;
	ans[0].d[0] = ans[0].m = 1;
	ans[1].d[0] = ans[1].m = 1;
	for(i = 2; i <= 250; i++)
	{
		add(&ans[i], &ans[i-1]);
		add(&ans[i], &ans[i-2]);
		add(&ans[i], &ans[i-2]);
	}
}

int main()
{
	int n;
	solve();
	while(scanf("%d", &n) != EOF)
	{
		print_ans(n);
	}
	return 0;
}

