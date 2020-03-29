#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	int n, m, r1, r2, c1, c2, t;
	double dist_h, dist_v;
	const double height = sqrt((double)3)/2;
	while(scanf("%d%d", &n, &m) != EOF)
	{
		r1 = (int)sqrt((double)n);
		r2 = (int)sqrt((double)m);
		c1 = n-r1*r1;
		c2 = m-r2*r2;
		if(r1 > r2)
		{
			t = r1;
			r1 = r2;
			r2 = t;
			t = c1;
			c1 = c2;
			c2 = t;
		}
		if(c1%2==0)
		{
			if(c2%2==0)
			{
				dist_v = (r2-r1)*height;
			}
			else
			{
				dist_v = (r2-r1-1)*height+2*height/3;
			}
		}
		else
		{
			if(c2%2==0)
			{
				dist_v = (r2-r1-1)*height+4*height/3;
			}
			else
			{
				dist_v = (r2-r1)*height;
			}
		}
		dist_h = abs(c1+r2-r1-c2)*0.5;
		printf("%.3lf\n", sqrt(dist_h*dist_h+dist_v*dist_v));
	}
	return 0;
}
