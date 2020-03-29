#include <cstdio>

int gcd(int a, int b, int &x, int &y)
{
	if(b==0)
	{
		x = 1;
		y = 0;
		return a;
	}
	int x1, y1;
	int d = gcd(b, a%b, x1, y1);
	x = y1;
	y = x1-a/b*y1;
	return d;
}

int main()
{
	int i;
	int a, b;
	int x, y, d;
	while(scanf("%d %d", &a, &b)!=EOF)
	{
		d = gcd(a, b, x, y);
		printf("%d %d %d\n", x, y, d);
	}
	return 0;
}