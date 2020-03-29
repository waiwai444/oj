#include <stdio.h>
#include <math.h>

#define MAXP 20
#define EPSILON 1e-10

struct Point
{
	double x, y;
};

struct Polygon
{
	int n;
	Point p[MAXP];
};

struct Line
{
	double a, b, c;
};

Polygon bread;
int k, h;

Line dip_line[MAXP];	// n dip lines corresponding to n edges of the bread

inline bool ccw(const Point& p1, const Point& p2, const Point& p3)
{
	return p1.x*p2.y+p2.x*p3.y+p3.x*p1.y-p1.x*p3.y-p2.x*p1.y-p3.x*p2.y > 0;
}

double get_area(const Polygon& polygon)
{
	if(polygon.n < 3)
		return 0;
	double area = polygon.p[polygon.n-1].x*polygon.p[0].y-polygon.p[0].x*polygon.p[polygon.n-1].y;
	for(int i = 1; i < polygon.n; i++)
	{
		area += polygon.p[i-1].x*polygon.p[i].y-polygon.p[i].x*polygon.p[i-1].y;
	}
	return area/2.0;
}

bool get_intersect_point(const Line& line1, const Line& line2, Point& its)
{
	if(line1.a == 0 && line2.a == 0 || line1.b == 0 && line2.b == 0 || line1.b != 0 && line2.b != 0 && line1.a*line2.b == line1.b*line2.a)	// parallel
		return false;
	its.x = (line1.b*line2.c-line2.b*line1.c)/(line1.a*line2.b-line1.b*line2.a);
	if(line1.b != 0)
		its.y = (-line1.a*its.x-line1.c)/line1.b;
	else
		its.y = (-line2.a*its.x-line2.c)/line2.b;
	return true;
}

inline Line get_line(const Point& p1, const Point& p2)	// note the direction of (a,b)
{
	Line line;
	line.a = p1.y-p2.y;
	line.b = p2.x-p1.x;
	line.c = -line.b*p1.y-line.a*p1.x;
	return line;
}

Point get_normal_vector(const Line& line, int len)
{
	Point nvec;
	double norm = sqrt(line.a*line.a+line.b*line.b);
	nvec.x = line.a*len/norm;
	nvec.y = line.b*len/norm;
	return nvec;
}

void get_dip_lines()
{
	Line edge;
	Point nvec;			
	for(int i = 0; i < bread.n; i++)
	{
		edge = get_line(bread.p[i > 0 ? i-1 : bread.n-1], bread.p[i]);
		nvec = get_normal_vector(edge, h);	// normal vector always points into the inner part of the polygon
		dip_line[i].a = edge.a;
		dip_line[i].b = edge.b;
		dip_line[i].c = edge.c-edge.a*nvec.x-edge.b*nvec.y;
	}
}

bool in_segment(const Point& p1, const Point& p2, const Point& p)
{
	if(p1.x > p2.x)
	{
		if(p.x >= p2.x && p.x <= p1.x)
			return true;
	}
	else if(p1.x < p2.x)
	{
		if(p.x <= p2.x && p.x >= p1.x)
			return true;
	}
	else if(p1.y > p2.y)
	{
		if(p.y >= p2.y && p.y <= p1.y)
			return true;
	}
	else
	{
		if(p.y <= p2.y && p.y >= p1.y)
			return true;
	}
	return false;
}

bool area_half_plane_intersect(const Polygon& polygon, const Line& line, Polygon& new_polygon)
{
	int i, j, k;
	Line edge;
	Point its[2];
	int idx[2];

	for(i = k = 0; i < polygon.n; i++)
	{
		j = i > 0 ? i-1 : polygon.n-1;
		edge = get_line(polygon.p[j], polygon.p[i]);
		if(get_intersect_point(line, edge, its[k]) && (its[k].x != polygon.p[j].x || its[k].y != polygon.p[j].y) && in_segment(polygon.p[j], polygon.p[i], its[k]))
		{
			idx[k] = i;	// record which segment this intersection point is in
			if(++k == 2)
				break;
		}
	}

	new_polygon.n = 0;
	if(k == 2)
	{
		Point ref_p = {its[0].x+line.a, its[0].y+line.b};
		if(ccw(its[1], its[0], ref_p))
			i = 0, j = 1;
		else
			i = 1, j = 0;
		k = idx[i];
		while(k != idx[j])
		{
			new_polygon.p[new_polygon.n++] = polygon.p[k];
			k = (k+1)%polygon.n;
		}
		new_polygon.p[new_polygon.n++] = its[j];
		if(polygon.p[idx[i]].x != its[i].x || polygon.p[idx[i]].y != its[i].y)
			new_polygon.p[new_polygon.n++] = its[i];
		return true;
	}
	else
	{
		double sign = polygon.p[0].x*line.a+polygon.p[0].y*line.b+line.c;
		if(sign > -EPSILON && sign < EPSILON)
			sign = polygon.p[2].x*line.a+polygon.p[2].y*line.b+line.c;
		if(sign > 0)
			return false;
		else
			return true;
	}
}

double try_dip(const Polygon& remainder, int dip_idx, double total_area, double dipped_area, int times)
{
	int i;	
	if(times >= k)
		return dipped_area;	
	double new_dipped_area, max_area = dipped_area;
	Polygon smaller;
	for(i = dip_idx; i < bread.n; i++)
	{
		if(!area_half_plane_intersect(remainder, dip_line[i], smaller))	// no intersection
			continue;
		new_dipped_area = total_area-get_area(smaller);
		if(new_dipped_area == total_area)
		{
			max_area = total_area;
			break;
		}
		if(i < bread.n-1)
		{
			new_dipped_area = try_dip(smaller, i+1, total_area, new_dipped_area, times+1);
		}
		if(new_dipped_area > max_area)
			max_area = new_dipped_area;
	}
	return max_area;
}

int main()
{
	int i, x, y;
	while(scanf("%d%d%d", &bread.n, &k, &h) && bread.n)
	{
		if(k > bread.n)
			k = bread.n;
		for(i = 0; i < bread.n; i++)
		{
			scanf("%d%d", &x, &y);
			bread.p[i].x = (double)x;
			bread.p[i].y = (double)y;
		}
		if(k == 0 || h == 0)
		{
			printf("0.00\n");
		}
		else
		{			
			get_dip_lines();
			printf("%.2lf\n", try_dip(bread, 0, get_area(bread), 0, 0));
		}
	}
	return 0;
}
