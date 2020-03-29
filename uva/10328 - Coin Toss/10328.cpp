#include <stdio.h>
#include <string.h>

struct biguint
{
	char d[50];
	int m;
};

void assign_1(biguint *x)
{
	x->m = x->d[0] = 1;
}

void add(biguint *x, const biguint *y)
{
	int i;
	char c = 0;
	if(y->m > x->m)
		x->m = y->m;
	for(i = 0; i < x->m; i++)
	{
		x->d[i] += y->d[i]+c;
		if(x->d[i] >= 10)
		{
			x->d[i] -= 10;
			c = 1;
		}
		else
			c = 0;
	}
	if(c > 0)
		x->d[x->m++] = 1;
}

void mul_2(biguint *x)
{
	int i;
	char c = 0;
	for(i = 0; i < x->m; i++)
	{
		x->d[i] = x->d[i]*2+c;
		if(x->d[i] >= 10)
		{
			x->d[i] -= 10;
			c = 1;
		}
		else
			c = 0;
	}
	if(c > 0)
		x->d[x->m++] = 1;
}

void print_uint(const biguint &x)
{
	int i;
	static char buf[51];
	for(i = 0; i < x.m; i++)
	{
		buf[i] = x.d[x.m-i-1]+'0';
	}
	buf[x.m] = '\0';
	printf("%s\n", buf);
}

biguint ans[101][101];

void solve()
{
	int i, j, k;
	assign_1(&ans[0][0]);
	for(i = 1; i <= 100; i++)
	{
		ans[i][0] = ans[i-1][0];
		mul_2(&ans[i][0]);
		for(j = 1; j <= i; j++)
		{
			for(k = 0; k < j; k++)
			{
				add(&ans[i][j], &ans[i-k-1][j]);
			}
			add(&ans[i][j], &ans[i-j][0]);
		}
	}
}

int main()
{
	int n, k;
	solve();
	while(scanf("%d%d", &n, &k) != EOF)
	{
		print_uint(ans[n][k]);
	}
	return 0;
}
