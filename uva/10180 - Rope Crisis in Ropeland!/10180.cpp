#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793

struct Point
{
	double x, y;
};

struct Line
{
	double a, b, c;
};

inline Line get_line(Point p1, Point p2)
{
	Line line;
	line.a = p2.y-p1.y;
	line.b = p1.x-p2.x;
	line.c = -line.a*p1.x-line.b*p1.y;
	return line;
}

inline Line get_line(Point p, double slope)
{
	Line line;
	line.a = slope;
	line.b = -1;
	line.c = p.y-slope*p.x;
	return line;
}

inline double distance(Point p1, Point p2)
{
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

inline double distance_to_line(Line line, Point p)
{
	return fabs(line.a*p.x+line.b*p.y+line.c)/sqrt(line.a*line.a+line.b*line.b);
}

inline bool intersection_point(Line line1, Line line2, Point *ip)
{
	if(line1.b == 0 && line1.b == line2.b || line1.a/line1.b == line2.a/line2.b)
		return false;
	ip->x = (line1.b*line2.c-line2.b*line1.c)/(line1.a*line2.b-line2.a*line1.b);
	if(line1.b != 0)
		ip->y = -line1.a/line1.b*ip->x-line1.c/line1.b;
	else
		ip->y = -line2.a/line2.b*ip->x-line2.c/line2.b;
	return true;
}

Point project_point(Point p, Line line)
{
	Line pline;
	if(line.a == 0)
	{
		Point p2;
		p2.x = p.x;
		p2.y = p.y+1;
		pline = get_line(p, p2);
	}
	else
		pline = get_line(p, line.b/line.a);
	Point ip;
	intersection_point(line, pline, &ip);
	return ip;
}

void tangent_point(Point p, double r, Point* tp1, Point* tp2)	// circle center (0,0)
{
	double tmp1, tmp2;
	if(p.y != 0)
	{
		tmp1 = p.x*p.x+p.y*p.y;
		tmp2 = p.y*r*sqrt(tmp1-r*r);
		tp1->x = (r*r*p.x+tmp2)/tmp1;
		tp1->y = (r*r-p.x*tp1->x)/p.y;
		tp2->x = (r*r*p.x-tmp2)/tmp1;
		tp2->y = (r*r-p.x*tp2->x)/p.y;
	}
	else
	{
		tp1->x = tp2->x = r*r/p.x;
		tp1->y = sqrt(r*r-tp1->x*tp1->x);
		tp2->y = -tp1->y;
	}
}

double min_angle(Point p11, Point p12, Point p21, Point p22)
{
	double temp, min = 2*PI, a11, a12, a21, a22;
	a11 = atan2(p11.y, p11.x);
	a12 = atan2(p12.y, p12.x);
	a21 = atan2(p21.y, p21.x);
	a22 = atan2(p22.y, p22.x);
	
	temp = fabs(a11-a21);
	if(temp > PI)
		temp = 2*PI-temp;
	if(temp < min)
		min = temp;
	temp = fabs(a11-a22);
	if(temp > PI)
		temp = 2*PI-temp;
	if(temp < min)
		min = temp;
	temp = fabs(a12-a21);
	if(temp > PI)
		temp = 2*PI-temp;
	if(temp < min)
		min = temp;
	temp = fabs(a12-a22);
	if(temp > PI)
		temp = 2*PI-temp;
	if(temp < min)
		min = temp;

	return min;
}

inline bool on_line_seg(Point p1, Point p2, Point pt)
{
	return (pt.x-p1.x)*(pt.x-p2.x)+(pt.y-p1.y)*(pt.y-p2.y) < 0;
}

int main()
{
	int i, n;
	Point p1, p2;
	const Point cc = {0.0, 0.0};
	double r;
	double dist_to_cc, line_len;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
	{
		scanf("%lf%lf%lf%lf%lf", &p1.x, &p1.y, &p2.x, &p2.y, &r);
		Line line = get_line(p1, p2);
		dist_to_cc = distance_to_line(line, cc);
		Point pp = project_point(cc, line);
		if(dist_to_cc >= r || !on_line_seg(p1, p2, pp))
		{
			line_len = sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
		}
		else
		{
			Point tp1, tp2, tp3, tp4;
			tangent_point(p1, r, &tp1, &tp2);
			line_len = distance(p1, tp1);
			tangent_point(p2, r, &tp3, &tp4);
			line_len += distance(p2, tp3);
			double angle = min_angle(tp1, tp2, tp3, tp4);
			line_len += angle*r;
		}
		printf("%.3lf\n", line_len);
	}
	return 0;
}
