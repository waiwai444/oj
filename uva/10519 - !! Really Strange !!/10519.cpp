#include <stdio.h>
#include <string.h>

char n[102];

struct biguint
{
	char d[201];
	int m;
};

void sub_by_1(biguint *x)
{
	int i;
	for(i = 0; i < x->m; i++)
	{
		if(x->d[i] > 0)
		{
			--x->d[i];
			break;
		}
		x->d[i] = 9;
	}
	if(x->m > 1 && x->d[x->m-1] == 0)
		--x->m;
}

void add_by_2(biguint *x)
{
	int i;
	x->d[0] += 2;
	if(x->d[0] >= 10)
	{
		for(i = 1; i < x->m; i++)
		{
			++x->d[i];
			if(x->d[i] < 10)
				break;
			x->d[i] -= 10;
		}
		if(i == x->m)
			x->d[x->m++] = 1;
	}
}

void mul(biguint *x, const biguint *y)
{
	int i, j;
	char c;
	biguint r;
	memset(&r, 0, sizeof(r));
	for(i = 0; i < x->m; i++)
	{
		c = 0;
		for(j = 0; j < y->m; j++)
		{
			r.d[i+j] += x->d[i]*y->d[j]+c;
			if(r.d[i+j] >= 10)
			{
				c = r.d[i+j]/10;
				r.d[i+j] %= 10;
			}
			else
				c = 0;
		}
		if(c > 0)
			r.d[i+j] = c;
	}
	r.m = i+j-1;
	if(r.d[r.m] > 0)
		++r.m;
	*x = r;
}

void print_ans(const biguint &x)
{
	int i;
	static char buf[202];
	for(i = 0; i < x.m; i++)
	{
		buf[i] = x.d[x.m-i-1]+'0';
	}
	buf[x.m] = '\0';
	printf("%s\n", buf);
}

void solve()
{
	int i;
	biguint x, t;
	x.m = strlen(n);
	for(i = 0; i < x.m; i++)
		x.d[i] = n[x.m-i-1]-'0';

	if(!(x.m == 1 && x.d[0] == 0))
	{
		t = x;
		sub_by_1(&t);
		mul(&x, &t);
		add_by_2(&x);
	}
	else
		x.d[0] = 1;
	print_ans(x);
}

int main()
{
	while(scanf("%s", n) != EOF)
	{
		solve();
	}
	return 0;
}

