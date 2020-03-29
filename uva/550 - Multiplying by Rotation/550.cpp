#include <stdio.h>

int main()
{
	int base, a, a1, c, d, carry;
	while(scanf("%d%d%d", &base, &a, &c) != EOF)
	{
		carry = 0;
		a1 = a;
		d = 1;
		while((a1 = a1*c+carry) != a)
		{
			carry = a1/base;
			a1 %= base;
			d++;
		}
		printf("%d\n", d);
	}
	return 0;
}
