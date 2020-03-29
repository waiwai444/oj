#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793

int main()
{
	double a, x, y, z;
	while(scanf("%lf", &a) != EOF)
	{
		z = (1-sqrt(3.0)/4-PI/6)*a*a;
		y = (1-PI/4)*a*a-2*z;
		x = a*a-4*z-4*y;
		printf("%.3lf %.3lf %.3lf\n", x, 4*y, 4*z);
	}
	return 0;
}
