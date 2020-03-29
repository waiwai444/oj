#include <stdio.h>
#include <math.h>

#define EPS 1e-6

int p, q, r, s, t, u;

inline double f(double x)
{
	return p*exp(-x)+q*sin(x)+r*cos(x)+s*tan(x)+t*x*x+u;
}

int main()
{
	double x, x0, x1, y;
	while(scanf("%d%d%d%d%d%d", &p, &q, &r, &s, &t, &u) != EOF)
	{
		if(f(1) > 0 || f(0) < 0)
		{
			printf("No solution\n");
			continue;
		}
		x0 = 0;
		x1 = 1;
		y = 1;
		while(fabs(y) > EPS)
		{
			x = (x0+x1)/2;
			y = f(x);
			if(y > 0)
				x0 = x;
			else if(y < 0)
				x1 = x;
			else
				break;
		}
		printf("%.4lf\n", x);
	}
	return 0;
}
