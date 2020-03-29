#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979324

int main()
{
	int D, V;
	while(scanf("%d%d", &D, &V), D)
		printf("%.3lf\n", pow(D*D*D-V*6/PI, 1.0/3));
	return 0;
}
