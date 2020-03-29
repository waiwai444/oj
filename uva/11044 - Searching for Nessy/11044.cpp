#include <stdio.h>

int main()
{
	int n, m, tc, x, y;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d", &n, &m);
		n -= 2;
		m -= 2;
		x = m/3;
		if(m%3 != 0)
			x += 1;
		y = n/3;
		if(n%3 != 0)
			y += 1;
		printf("%d\n", x*y);
	}
	return 0;
}
