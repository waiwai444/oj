#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979324

int main()
{
	int a, b, s, m, n;
	double angle, velocity;
	while(scanf("%d%d%d%d%d", &a, &b, &s, &m, &n), a)
	{
		int sx = m*a;
		int sy = n*b;
		angle = atan((double)sy/sx)/PI*180;
		velocity = sqrt((double)sx*sx+(double)sy*sy)/s;
		printf("%.2lf %.2lf\n", angle, velocity);
	}
	return 0;
}