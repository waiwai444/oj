#include <stdio.h>
#include <algorithm>

#define MAXP 100

struct Point
{
	int x, y;
};

struct Polygon
{
	int n;
	Point p[MAXP];
};

inline double signed_area(const Point& p1, const Point& p2, const Point& p3)
{
	return (p1.x*p2.y+p2.x*p3.y+p3.x*p1.y-p1.x*p3.y-p2.x*p1.y-p3.x*p2.y)/2.0;
}

inline bool ccw(const Point& p1, const Point& p2, const Point& p3)
{
	return signed_area(p1, p2, p3) > 0;
}

inline double distance2(const Point& p1, const Point& p2)
{
	return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}

Point left_bottom;	// the first point for Graham's algorithm

bool cmp_angle(const Point& p1, const Point& p2)
{
	double area = signed_area(left_bottom, p1, p2);
	if(area == 0)
		return distance2(left_bottom, p1) < distance2(left_bottom, p2);
	return area > 0;
}

int find_left_bottom(const Polygon& pg)
{
	int i, t = 0;
	for(i = 1; i < pg.n; i++)
	{
		if(pg.p[i].x < pg.p[t].x || pg.p[i].x == pg.p[t].x && pg.p[i].y < pg.p[t].y)
			t = i;
	}
	return t;
}

void get_convex_hull(const Polygon& pg, Polygon& hull)
{
	int i, j, lb;
	
	for(i = 0; i < pg.n; i++)
		hull.p[i] = pg.p[i];

	lb = find_left_bottom(pg);
	left_bottom = hull.p[lb];
	hull.p[lb] = hull.p[0];
	hull.p[0] = left_bottom;
	std::sort(hull.p+1, hull.p+pg.n, cmp_angle);
	
	hull.n = 2;
	for(i = 2; i < pg.n; i++)
	{
		for(j = hull.n-1; j >= 1; j--)
		{
			if(ccw(hull.p[j-1], hull.p[j], hull.p[i]))
				break;
		}
		hull.p[j+1] = hull.p[i];
		hull.n = j+2;
	}
}

double get_area(const Polygon& pg)
{
	int i;
	double area = pg.p[pg.n-1].x*pg.p[0].y-pg.p[pg.n-1].y*pg.p[0].x;
	for(i = 1; i < pg.n; i++)
		area += pg.p[i-1].x*pg.p[i].y-pg.p[i-1].y*pg.p[i].x;
	return area/2.0;
}

int main()
{
	int i, tc = 0;
	Polygon pg, hull;
	double hull_area, area;
	while(scanf("%d", &pg.n), pg.n)
	{
		for(i = 0; i < pg.n; i++)
			scanf("%d%d", &pg.p[i].x, &pg.p[i].y);
		
		get_convex_hull(pg, hull);
		hull_area = get_area(hull);
		area = get_area(pg);
		if(area < 0)
			area = -area;
		
		printf("Tile #%d\nWasted Space = %.2lf %%\n\n", ++tc, 100-area/hull_area*100);
	}
	return 0;
}
