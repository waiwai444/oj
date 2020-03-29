#include <stdio.h>

int main()
{
	int k, m, n, x, y;
	while(scanf("%d", &k), k)
	{
		scanf("%d%d", &m, &n);
		while(k--)
		{
			scanf("%d%d", &x, &y);
			if(x == m || y == n)
				printf("divisa\n");
			else if(x < m && y > n)
				printf("NO\n");
			else if(x > m && y > n)
				printf("NE\n");
			else if(x > m && y < n)
				printf("SE\n");
			else
				printf("SO\n");
		}
	}
	return 0;
}
