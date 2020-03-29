#include <stdio.h>

#define EPS 1e-9

int main()
{
	int i, n, p, littlest, init_height, t1, t2;
	while(scanf("%d%d", &init_height, &littlest), init_height)
	{
		if(littlest == 1)
		{
			n = 1;
			p = 0;
			int tmp = init_height;
			while(tmp > 1)
			{
				tmp >>= 1;
				p++;
			}
		}
		else
		{
			n = 2;
			for(n = 2; ; n++)
			{
				t1 = n, t2 = n+1;
				p = 1;
				while(t1 < littlest && t2 < init_height)
				{
					t1 *= n;
					t2 *= (n+1);
					p++;
				}
				if(t1 == littlest && t2 == init_height)
					break;
			}
		}
		for(t1 = n, i = 1; i < p; i++)
			t1 *= n;
		int noworking = n > 1 ? (int)((t1-1)/(n-1)+EPS) : p;
		int total_height = (n+1)*init_height-t1*n;
		printf("%d %d\n", noworking, total_height);
	}
	return 0;
}
