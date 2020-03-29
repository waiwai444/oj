#include <stdio.h>

#define SIZE 10
#define MAXP 60

struct Point
{
	double x, y;
	bool operator ==(const Point& p)
	{
		return x == p.x && y == p.y;
	}
	bool operator !=(const Point& p)
	{
		return !(*this == p);
	}
};

struct Line
{
	double a, b, c;
};

struct Polygon
{
	int n;
	Point p[MAXP];
};

Line make_line(const Point& p1, const Point& p2)	// p1 != p2
{
	Line line;
	if(p1.x == p2.x)
	{
		line.a = 1;
		line.b = 0;
		line.c = -p1.x;
	}
	else
	{
		line.a = (p2.y-p1.y)/(p2.x-p1.x);
		line.b = -1;
		line.c = p1.y-line.a*p1.x;
	}
	return line;
}

Line midperpendicular(const Point& p1, const Point& p2)	// p1 != p2
{
	Line mpline;
	if(p1.y == p2.y)
	{
		mpline.a = 1;
		mpline.b = 0;
		mpline.c = -(p1.x+p2.x)/2;
	}
	else
	{
		double k = -(p2.x-p1.x)/(p2.y-p1.y);
		Point mid_p = {(p1.x+p2.x)/2, (p1.y+p2.y)/2};
		double b = mid_p.y-k*mid_p.x;
		mpline.a = k;
		mpline.b = -1;
		mpline.c = b;
	}
	return mpline;
}

inline bool parallel(const Line& line1, const Line& line2)
{
	return line1.b == 0 && line2.b == 0 || line1.b != 0 && line2.b != 0 && line1.a/line1.b == line2.a/line2.b;
}

inline bool collinear_point_in_segment(const Point& sp1, const Point& sp2, const Point& p)	// sp1 != sp2, three points collinear
{
	if(sp1.x != sp2.x)
		return p.x-sp1.x >= 0 && p.x-sp2.x <= 0 || p.x-sp1.x <= 0 && p.x-sp2.x >= 0;
	else
		return p.y-sp1.y >= 0 && p.y-sp2.y <= 0 || p.y-sp1.y <= 0 && p.y-sp2.y >= 0;
}

bool intersect(const Line& line1, const Line& line2, Point* p)
{
	if(parallel(line1, line2))	// include the case that line1 and line2 are the same line
		return false;
	if(line1.b == 0)
	{
		p->x = -line1.c/line1.a;
		p->y = (-line2.c-line2.a*p->x)/line2.b;
	}
	else if(line2.b == 0)
	{
		p->x = -line2.c/line2.a;
		p->y = (-line1.c-line1.a*p->x)/line1.b;
	}
	else
	{
		double k1 = -line1.a/line1.b;
		double k2 = -line2.a/line2.b;
		double b1 = -line1.c/line1.b;
		double b2 = -line2.c/line2.b;
		p->x = (b2-b1)/(k1-k2);
		p->y = k1*p->x+b1;
	}
	return true;
}

int intersect(const Polygon& polygon, const Line& line, Point* ip, int np, int *idx_edge_start)	// idx_edge_start is the index of the starting point of the segment the intersect point located.
{
	int i, j, t = 0;
	Line edge_line;
	Point tmp_p;
	for(i = 0; i < polygon.n; i++)
	{
		if(i == polygon.n-1)
			j = 0;
		else
			j = i+1;
		edge_line = make_line(polygon.p[i], polygon.p[j]);
		if(intersect(edge_line, line, &tmp_p) && collinear_point_in_segment(polygon.p[i], polygon.p[j], tmp_p) && tmp_p != polygon.p[j])
		{
			ip[t] = tmp_p;
			idx_edge_start[t] = i;
			t++;
			if(t > np)
				break;
		}
	}
	return t;
}

inline double signed_area(const Point& p1, const Point& p2, const Point& p3)
{
	return (p1.x*p2.y+p2.x*p3.y+p3.x*p1.y-p1.x*p3.y-p2.x*p1.y-p3.x*p2.y)/2.0;
}

inline bool ccw(const Point& p1, const Point& p2, const Point& p3)
{
	return signed_area(p1, p2, p3) > 0;
}

#define EPSILON 1e-9
bool has_area(const Polygon& polygon, const Line& mpline, const Point& cur_p, char dir)
{
	double x = cur_p.x*mpline.a+cur_p.y*mpline.b+mpline.c;
	double y = 0;
	for(int i = 0; i < polygon.n; i++)
		if((y = polygon.p[i].x*mpline.a+polygon.p[i].y*mpline.b+mpline.c) > EPSILON || y < -EPSILON)
			break;
	return x*y > 0 && dir == 'H' || x*y < 0 && dir == 'C';
}

void cut_polygon(Polygon& polygon, Point ip[2], int idx_edge_start[2], Point cur_p, char dir)	// dir: 'H' or 'C'
{
	int i, start, end;
	
	bool b = ccw(ip[0], ip[1], cur_p);
	if(b && dir == 'H' || !b && dir == 'C')
	{
		start = idx_edge_start[1]+1;
		end = idx_edge_start[0];
		if(polygon.p[end] != ip[0])
			end++;
	}
	else
	{
		start = idx_edge_start[0]+1;
		end = idx_edge_start[1];
		if(polygon.p[end] != ip[1])
			end++;
		Point tmp = ip[0];
		ip[0] = ip[1];
		ip[1] = tmp;
	}
	
	if(start == polygon.n)
		start = 0;
	if(end == polygon.n)
		end = 0;
	if(start > end)
	{
		if(end+1 == start)
		{
			for(i = polygon.n; i > start; i--)
				polygon.p[i] = polygon.p[i-1];
			polygon.p[end] = ip[0];
			polygon.p[end+1] = ip[1];
			polygon.n++;
		}
		else
		{
			polygon.p[end] = ip[0];
			polygon.p[end+1] = ip[1];
			for(i = end+2; i <= end+polygon.n-start+1; i++)
				polygon.p[i] = polygon.p[start+i-end-2];
			polygon.n = i;
		}
	}
	else	// start < end
	{
		for(i = start; i < end; i++)
			polygon.p[i-start] = polygon.p[i];
		polygon.p[end-start] = ip[0];
		polygon.p[end-start+1] = ip[1];
		polygon.n = end-start+2;
	}
}

double get_area(const Polygon& polygon)
{
	int i;
	Point orig = {0, 0};
	double area = polygon.p[polygon.n-1].x*polygon.p[0].y-polygon.p[polygon.n-1].y*polygon.p[0].x;
	for(i = 1; i < polygon.n; i++)
	{
		area += polygon.p[i-1].x*polygon.p[i].y-polygon.p[i-1].y*polygon.p[i].x;
	}
	area /= 2.0;
	return area;
}

int main()
{
	char hint[8];
	double area = SIZE*SIZE;
	Point prev_p = {0, 0};
	Point cur_p;
	Polygon polygon;
	
	polygon.n = 4;
	polygon.p[0].x = polygon.p[0].y = 0;
	polygon.p[1].x = SIZE;
	polygon.p[1].y = 0;
	polygon.p[2].x = polygon.p[2].y = SIZE;
	polygon.p[3].x = 0;
	polygon.p[3].y = SIZE;
	
	while(scanf("%lf%lf%s", &cur_p.x, &cur_p.y, hint) != EOF)
	{
		if(hint[0] == 'S' && cur_p != prev_p)
			area = 0;
		if(area > 0)
		{
			if(prev_p != cur_p)
			{
				Line mpline = midperpendicular(prev_p, cur_p);
				Point ipoint_set[2];
				int idx_edge_start[2];
				int nip = intersect(polygon, mpline, ipoint_set, 2, idx_edge_start);
				if(nip == 2)
				{
					cut_polygon(polygon, ipoint_set, idx_edge_start, cur_p, hint[0]);
					area = get_area(polygon);
				}
				else if(!has_area(polygon, mpline, cur_p, hint[0]))
				{
					area = 0;
				}
			}
			else if(hint[0] != 'S')
			{
				area = 0;
			}
		}
		printf("%.2lf\n", area);
		prev_p = cur_p;
	}
	return 0;
}
