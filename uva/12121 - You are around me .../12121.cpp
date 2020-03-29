#include <stdio.h>
#include <float.h>
#include <math.h>
#include <algorithm>

#define PI 3.14159265358979324

int n;
double e, theta;
struct Coord
{
	double x, y;
} center[15000];

bool cmp_x(const Coord &c1, const Coord &c2)
{
	if(c1.x < c2.x)
		return true;
	if(c1.x > c2.x)
		return false;
	return c1.y < c2.y;
}

void rotate_x()
{
	double theta_r = theta/180*PI, r, a0;
	for(int i = 0; i < n; i++)
	{
		r = sqrt(center[i].x*center[i].x+center[i].y*center[i].y);
		a0 = atan2(center[i].y, center[i].x);
		center[i].x = r*cos(a0-theta_r);
		center[i].y = r*sin(a0-theta_r);
	}
}

double get_max_area()
{
	int i, j;
	double max = DBL_MAX, cur, xm, ym, a, b, bound_x = DBL_MAX, bound_y = DBL_MAX;
	std::sort(center, center+n, cmp_x);
	for(i = 0; i < n; i++)
	{
		for(j = i+1; j < n; j++)
		{
			if((center[i].x-center[j].x >= bound_x) || (center[j].x-center[i].x >= bound_x))
				break;
			if((center[i].y-center[j].y >= bound_y) || (center[j].y-center[i].y >= bound_y))
				continue;
			xm = (center[i].x+center[j].x)/2;
			ym = (center[i].y+center[j].y)/2;
			a = sqrt((xm-center[i].x)*(xm-center[i].x)+(ym-center[i].y)*(ym-center[i].y)/(1-e*e));
			b = a*sqrt(1-e*e);
			cur = PI*a*b;
			if(cur < max)
			{
				max = cur;
				bound_x = 2*a;
				bound_y = 2*b;
			}
		}
	}
	return max;
}

int main()
{
	int i, tc = 1;
	while(scanf("%d%lf%lf", &n, &e, &theta), n)
	{
		for(i = 0; i < n; i++)
			scanf("%lf%lf", &center[i].x, &center[i].y);
		if(e == 1)
		{
			printf("Case %d:\n0.000000\n", tc++);
			continue;
		}
		rotate_x();
		printf("Case %d:\n%.6lf\n", tc++, get_max_area());
	}
	return 0;
}