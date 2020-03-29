#include <stdio.h>
#include <math.h>

#define LIMIT 0.000001
#define PI 3.14159265358979324

inline double incircle_radius(double b, double h)
{
	//return (-b*b+b*sqrt(b*b+4*h*h))/(4*h);	// WA
	//return tan(atan(2*h/b)/2)*b/2;	// AC
	return 2*h/(b+sqrt(4*h*h+b*b))*b/2;	// AC
}

int main()
{
	int tc;
	double b, h, r, sum, d;
	scanf("%d", &tc);
	while(tc--)
	{	
		scanf("%lf%lf", &b, &h);
		sum = 0;
		r = incircle_radius(b, h);
		while(r >= LIMIT)
		{
			d = 2*r;
			sum += d;
			h -= d;
			b = b*h/(h+d);
			r = incircle_radius(b, h);
		}
		if(tc > 0)
			printf("%13.6lf\n\n", sum*PI);
		else
			printf("%13.6lf\n", sum*PI);
	}
	return 0;
}