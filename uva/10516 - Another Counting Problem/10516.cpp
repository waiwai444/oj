#include <stdio.h>
#include <string.h>

class biguint
{
	char d[200];
	int m;

public:
	biguint &operator = (unsigned int x);
	biguint &operator += (const biguint &x);
	biguint &operator *= (const biguint &x);
	biguint operator + (const biguint &x);
	biguint operator * (const biguint &x);
	void print();
};

biguint &biguint::operator = (unsigned int x)
{
	memset(this, 0, sizeof(*this));
	do {
		d[m++] = x%10;
		x /= 10;
	} while(x);
	return *this;
}

biguint &biguint::operator += (const biguint &x)
{
	int i;
	char c = 0;
	if(x.m > m)
		m = x.m;
	for(i = 0; i < m; i++)
	{
		d[i] += x.d[i]+c;
		if(d[i] >= 10)
		{
			d[i] -= 10;
			c = 1;
		}
		else
			c = 0;
	}
	if(c > 0)
		d[m++] = 1;
	return *this;
}

biguint &biguint::operator *= (const biguint &x)
{
	int i, j;
	char c;
	biguint r;
	memset(&r, 0, sizeof(r));
	for(i = 0; i < m; i++)
	{
		c = 0;
		for(j = 0; j < x.m; j++)
		{
			r.d[i+j] += d[i]*x.d[j]+c;
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
	r.m = m+x.m-1;
	if(c > 0)
		++r.m;
	return *this = r;
}

biguint biguint::operator + (const biguint &x)
{
	biguint t = *this;
	return t += x;
}

biguint biguint::operator * (const biguint &x)
{
	biguint t = *this;
	return t *= x;
}

void biguint::print()
{
	int i;
	static char buf[201];
	for(i = 0; i < m; i++)
		buf[i] = d[m-i-1]+'0';
	buf[m] = '\0';
	printf("%s\n", buf);
}

int n, d;
biguint ans[33][17];
biguint sum[33][17];

#define NODE_LIM 1024

void solve()
{
	int i, j, k, l;
	int p;
	biguint t1, t2;
	for(i = 1; i <= 32; i++)
	{
		sum[i][0] = ans[i][0] = ans[i][1] = 1;
		sum[i][1] = 2;
		p = i;
		for(j = 2; j <= 16; j++)
		{
			p *= i;
			ans[i][j] = 0;
			if(p > NODE_LIM)
				break;
			for(k = 1; k <= i; k++)
			{
				t1 = t2 = 1;
				for(l = 1; l < k; l++)
					t1 *= sum[i][j-2];
				for(l = 1; l <= i-k; l++)
					t2 *= sum[i][j-1];
				ans[i][j] += t1*ans[i][j-1]*t2;
			}
			sum[i][j] = sum[i][j-1]+ans[i][j];
		}
	}
}

int main()
{
	solve();
	while(scanf("%d%d", &n, &d), n)
	{
		printf("%d %d ", n, d);
		ans[n][d].print();
	}
	return 0;
}

