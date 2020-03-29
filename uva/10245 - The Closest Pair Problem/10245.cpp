#include <stdio.h>
#include <math.h>
#include <algorithm>

#define MAX 2e10

struct Point
{
	double x, y;
};

int n;
Point point[10000];

bool cmp(const Point& p1, const Point& p2)
{
	return p1.x < p2.x;
}

inline double distance2(const Point& p1, const Point& p2)
{
	return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}

int main()
{
	int i, j;
	double min_dist, dist;
	while(scanf("%d", &n) && n)
	{
		for(i = 0; i < n; i++)
			scanf("%lf%lf", &point[i].x, &point[i].y);
		min_dist = MAX;
		if(n > 1)
		{
			std::sort(point, point+n, cmp);
			min_dist = MAX;
			for(i = 0; i < n-1; i++)
			{
				for(j = i+1; j < n; j++)
				{
					if((point[j].x-point[i].x)*(point[j].x-point[i].x) >= min_dist)
						break;
					dist = distance2(point[i], point[j]);
					if(dist < min_dist)
						min_dist = dist;
				}
			}
			min_dist = sqrt(min_dist);
		}
		if(min_dist >= 10000)
			printf("INFINITY\n");
		else
			printf("%.4lf\n", min_dist);
	}
	return 0;
}
