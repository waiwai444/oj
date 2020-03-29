#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	int n, k, tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d", &k);
		if(k == 0)
			n = 3;
		else
		{
			k = abs(k);
			n = (int)ceil((sqrt((8*(double)k+1))-1)/2-(1e-9));
			int t = n*(n+1)/2;
			int pt = t&1, pk = k&1, pn = n&1;
			if(pt^pk == 1)
			{
				if(pn == 0)
					n++;
				else
					n += 2;
			}
		}
		if(tc > 0)
			printf("%d\n\n", n);
		else		
			printf("%d\n", n);
	}
	return 0;
}
