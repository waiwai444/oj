#include <stdio.h>
#include <math.h>

int main()
{
	double a, b, c, r, alpha, beta;
	while(scanf("%lf%lf%lf", &a, &b, &c) != EOF)
	{
		if(a+b <= c || a+c <= b || b+c <= a)
			r = 0.0;
		else
		{
			alpha = acos((b*b+c*c-a*a)/(2*b*c))/2;
			beta = acos((a*a+c*c-b*b)/(2*a*c))/2;
			r = c*sin(alpha)*sin(beta)/sin(alpha+beta);
		}
		printf("The radius of the round table is: %.3lf\n", r);
	}
	return 0;
}
