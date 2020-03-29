#include <stdio.h>

long double get_first_recur(int e, long double c)
{
	if(e == 0)
		return 1;
	long double r = get_first_recur(e/2, c);
	r *= r;
	if(e&1)
		r *= c;
	while(r >= 10)
		r /= 10;
	return r;
}

int get_first(unsigned int n, int e)
{
	long double c = n;
	while(c >= 10)
		c /= 10;
	return get_first_recur(e, c)*100;
}

int get_last(int n, int e)
{
	if(e == 0)
		return 1;
	int r = get_last(n, e/2);
	r = (r*r)%1000;
	if(e&1)
		r = (r*n)%1000;
	return r;
}

int main()
{
	int tc, k, l, t;
	unsigned int n;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%u%d", &n, &k);
		l = get_first(n, k);
		t = get_last(n%1000, k);
		printf("%d...%03d\n", l, t);
	}
	return 0;
}
