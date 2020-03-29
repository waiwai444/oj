#include <stdio.h>

int main()
{
	int n, i, j, tc;
	double p, r, t;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%lf%d", &n, &p, &i);
		if(p == 0)
			r = 0;
		else
		{
			r = p;
			for(j = 1; j <= i-1; j++)
				r *= (1-p);
			t = 1;
			for(j = 1; j <= n; j++)
				t *= (1-p);
			r /= (1-t);
		}
		printf("%.4f\n", r);
	}
	return 0;
}

