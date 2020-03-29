#include <stdio.h>
#include <math.h>

int main()
{
	double x1, y1, x2, y2, x3, y3, x4, y4;
	while(scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2) != EOF)
	{
		double d = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))/2;
		double xm = (x1+x2)/2;
		double ym = (y1+y2)/2;
		if(y1 == y2)
		{
			if(x1 == x2)
				printf("Impossible.\n");
			else
				printf("%.10lf %.10lf %.10lf %.10lf\n", xm, ym+d, xm, ym-d);
		}
		else
		{
			double k = (x1-x2)/(y1-y2);
			double tmp = d/sqrt(1+k*k);
			x3 = tmp+xm;
			y3 = -k*x3+k*xm+ym;
			x4 = -tmp+xm;
			y4 = -k*x4+k*xm+ym;
			printf("%.10lf %.10lf %.10lf %.10lf\n", x3, y3, x4, y4);
		}
	}
	return 0;
}
