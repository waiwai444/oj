#include <stdio.h>

int main()
{
	int tc, d, i, p, l;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d", &d, &i);
		i--;
		p = 1;
		l = 1;
		while(l < d)
		{
			p *= 2;
			if((i&1) == 1)
				p++;
			i /= 2;
			l++;
		}
		printf("%d\n", p);
	}
	return 0;
}