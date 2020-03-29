#include <stdio.h>
#include <math.h>

#define EPS 1e-11

int main()
{
	double l, w;
	while(scanf("%lf%lf", &l, &w) != EOF)
		printf("%.3lf 0.000 %.3lf\n", (w+l-sqrt(l*l+w*w-w*l))/6+EPS, (w < l ? w : l)/2+EPS);
	return 0;
}
