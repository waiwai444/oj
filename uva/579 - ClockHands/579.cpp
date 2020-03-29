#include <stdio.h>
#include <math.h>

int main()
{
	int h, m;
	double ah, am, da;
	while(scanf("%d:%d", &h, &m), h)
	{
		if(h == 12)
			h = 0;
		ah = 360.0/60/12*m+360.0/12*h;
		am = 360.0/60*m;
		da = fabs(ah-am);
		if(da > 180)
			da = 360-da;
		printf("%.3lf\n", da);
	}
	return 0;
}