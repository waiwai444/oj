#include <stdio.h>
#include <string.h>

#define MAX_FIB 102

struct fibinary
{
	char d[MAX_FIB];
	int l;
	fibinary() : l(1) { memset(d, 0, sizeof(d)); }
};

struct biguint
{
	char d[30];
	int l;
	biguint() : l(1) { memset(d, 0, sizeof(d)); }
};

biguint fib[MAX_FIB];

void add(biguint &x, const biguint &y, const biguint &z)
{
	int i;
	char c = 0;
	x.l = y.l >= z.l ? y.l : z.l;
	for(i = 0; i < x.l; i++)
	{
		x.d[i] = y.d[i]+z.d[i]+c;
		if(x.d[i] >= 10)
		{
			x.d[i] -= 10;
			c = 1;
		}
		else
			c = 0;
	}
	if(c > 0)
		x.d[x.l++] = c;
}

void add(biguint &x, const biguint &y)
{
	add(x, x, y);
}

void sub(biguint &x, const biguint &y)
{
	int i;
	char c = 0;
	for(i = 0; i < x.l; i++)
	{
		x.d[i] -= y.d[i]+c;
		if(x.d[i] < 0)
		{
			x.d[i] += 10;
			c = 1;
		}
		else
			c = 0;
	}
	while(x.l > 1 && x.d[x.l-1] == 0)
		--x.l;
}

bool less(const biguint &x, const biguint &y)
{
	if(x.l < y.l)
		return true;
	if(x.l > y.l)
		return false;
	for(int i = x.l-1; i >= 0; i--)
		if(x.d[i] < y.d[i])
			return true;
		else if(x.d[i] > y.d[i])
			return false;
	return false;
}

void fbin_to_uint(const fibinary &fbin, biguint &bint)
{
	int i;
	memset(&bint, 0, sizeof(bint));
	bint.l = 1;
	for(i = 0; i < fbin.l; i++)
	{
		if(fbin.d[i] == 1)
			add(bint, fib[i]);
	}
}

void uint_to_fbin(const biguint &bint, fibinary &fbin)
{
	int i;
	biguint x = bint;
	for(i = MAX_FIB-1; i >= 0; i--)
	{
		if(less(x, fib[i]))
		{
			fbin.d[i] = 0;
		}
		else
		{
			fbin.d[i] = 1;
			sub(x, fib[i]);
		}
	}
	for(i = MAX_FIB-1; i > 0; i--)
		if(fbin.d[i] != 0)
			break;
	fbin.l = i+1;
}

void add(fibinary &x, const fibinary &y, const fibinary &z)
{
	biguint xi, yi, zi;
	fbin_to_uint(y, yi);
	fbin_to_uint(z, zi);
	add(xi, yi, zi);
	uint_to_fbin(xi, x);
}

bool read_input(fibinary &fn1, fibinary &fn2)
{
	int i;
	char n1[101], n2[101];
	if(scanf("%s%s", n1, n2) == EOF)
		return false;
	memset(&fn1, 0, sizeof(fn1));
	memset(&fn2, 0, sizeof(fn2));
	fn1.l = strlen(n1);
	fn2.l = strlen(n2);
	for(i = 0; i < fn1.l; i++)
		fn1.d[i] = n1[fn1.l-i-1]-'0';
	for(i = 0; i < fn2.l; i++)
		fn2.d[i] = n2[fn2.l-i-1]-'0';
	return true;
}

void get_all_fibs()
{
	int i;
	fib[0].d[0] = 1;
	fib[0].l = 1;
	fib[1].d[0] = 2;
	fib[1].l = 1;
	for(i = 2; i < MAX_FIB; i++)
	{
		add(fib[i], fib[i-1], fib[i-2]);
	}
}

void print_fbin(const fibinary &x)
{
	char buf[MAX_FIB+1];
	for(int i = 0; i < x.l; i++)
		buf[x.l-i-1] = x.d[i]+'0';
	buf[x.l] = '\0';
	printf("%s\n", buf);
}

int main()
{
	bool first = true;
	fibinary fn1, fn2, ans;
	get_all_fibs();
	while(read_input(fn1, fn2))
	{
		add(ans, fn1, fn2);
		if(!first)
			printf("\n");
		else
			first = false;
		print_fbin(ans);
	}
	return 0;
}

