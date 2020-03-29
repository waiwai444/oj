#include <stdio.h>

#define EPS 1e-9

struct Point
{
	double x, y;
};

inline bool ccw(Point p1, Point p2, Point p3)
{
	return p1.x*p2.y+p2.x*p3.y+p3.x*p1.y-p1.x*p3.y-p2.x*p1.y-p3.x*p2.y > EPS;
}

inline bool colinear(Point p1, Point p2, Point p3)
{
	double t = p1.x*p2.y+p2.x*p3.y+p3.x*p1.y-p1.x*p3.y-p2.x*p1.y-p3.x*p2.y;
	return t <= EPS && t >= -EPS;
}

inline bool on_edge(Point e1, Point e2, Point p)
{
	if(e1.x < e2.x)
		return colinear(e1, e2, p) && e1.x <= p.x && p.x <= e2.x;
	else if(e1.x > e2.x)
		return colinear(e1, e2, p) && e2.x <= p.x && p.x <= e1.x;
	else if(e1.y < e2.y)
		return colinear(e1, e2, p) && e1.y <= p.y && p.y <= e2.y;
	else
		return colinear(e1, e2, p) && e2.y <= p.y && p.y <= e1.y;
}

inline void reorder_vertices(Point &p1, Point &p2, Point &p3)
{
	if(!ccw(p1, p2, p3))
	{
		Point t = p1;
		p1 = p3;
		p3 = t;
	}
}

inline int left_border(Point p1, Point p2, Point p3)
{
	int left = (int)p1.x;
	if((int)p2.x < left)
		left = (int)p2.x;
	if((int)p3.x < left)
		left = (int)p3.x;
	return left;
}

inline int right_border(Point p1, Point p2, Point p3)
{
	int right = (int)p1.x;
	if((int)p2.x > right)
		right = (int)p2.x;
	if((int)p3.x > right)
		right = (int)p3.x;
	return right+1;
}

inline int bottom_border(Point p1, Point p2, Point p3)
{
	int bottom = (int)p1.y;
	if((int)p2.y < bottom)
		bottom = (int)p2.y;
	if((int)p3.y < bottom)
		bottom = (int)p3.y;
	return bottom;
}

inline int top_border(Point p1, Point p2, Point p3)
{
	int top = (int)p1.y;
	if((int)p2.y > top)
		top = (int)p2.y;
	if((int)p3.y > top)
		top = (int)p3.y;
	return top+1;
}

int main()
{
	Point p1, p2, p3;
	int i, j, ntrees;
	while(scanf("%lf%lf%lf%lf%lf%lf", &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y))
	{
		if(p1.x == 0 && p1.y == 0 && p2.x == 0 && p2.y == 0 && p3.x == 0 && p3.y == 0)
			break;
		ntrees = 0;
		reorder_vertices(p1, p2, p3);
		int left = left_border(p1, p2, p3);
		if(left < 1) left = 1;
		int right = right_border(p1, p2, p3);
		if(right > 99) right = 99;
		int bottom = bottom_border(p1, p2, p3);
		if(bottom < 1) bottom = 1;
		int top = top_border(p1, p2, p3);
		if(top > 99) top = 99;
		for(i = left; i <= right; i++)
		{
			for(j = bottom; j <= top; j++)
			{
				Point tree = { (double)i, (double)j };
				if(on_edge(p1, p2, tree) || on_edge(p2, p3, tree) || on_edge(p3, p1, tree)
					|| ccw(p1, p2, tree) && ccw(p2, p3, tree) && ccw(p3, p1, tree))
				{
					ntrees++;
				}
			}
		}
		printf("%4d\n", ntrees);
	}
	return 0;
}
