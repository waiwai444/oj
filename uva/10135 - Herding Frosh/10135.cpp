#include <stdio.h>
#include <math.h>
#include <algorithm>

struct Point
{
	double x, y;
	double polar_angle;
};

int n;
Point frosh[1002];

struct Polygon
{
	int n;
	int p_idx[1002];
};

inline double distance(const Point& p1, const Point& p2)
{
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

inline double signed_area(const Point& p1, const Point& p2, const Point& p3)
{
	return p1.x*p3.y+p2.x*p1.y+p3.x*p2.y-p1.x*p2.y-p2.x*p3.y-p3.x*p1.y;
}

inline bool ccw(const Point& p1, const Point& p2, const Point& p3)
{
	return signed_area(p1, p2, p3) > 0;
}

inline bool collinear(const Point& p1, const Point& p2, const Point& p3)
{
	return signed_area(p1, p2, p3) == 0;
}

bool small_polar_angle(const Point& p1, const Point& p2)
{
	return p1.polar_angle < p2.polar_angle;
}

void sort_and_remove_duplicates()
{
	int i, j, k, far;
	double dist, max_dist;
	Point orig = {0.0, 0.0};
	std::sort(frosh, frosh+n, small_polar_angle);
	for(i = 0, j = 0; i < n; )
	{
		far = i;
		max_dist = distance(frosh[i], orig);
		for(k = i+1; frosh[k].polar_angle == frosh[i].polar_angle; k++)
		{
			dist = distance(frosh[k], orig);
			if(dist > max_dist)
			{
				max_dist = dist;
				far = k;
			}
		}
		frosh[j++] = frosh[far];
		i = k;
	}
	n = j;
}

bool intersect(int first, int cur1, int cur2)	// line segs [0,first], [cur1,cur2]
{
	int sign0 = (int)(-frosh[cur1].y*(frosh[cur2].x-frosh[cur1].x)+frosh[cur1].x*(frosh[cur2].y-frosh[cur1].y));
	int sign1 = (int)((frosh[first].y-frosh[cur1].y)*(frosh[cur2].x-frosh[cur1].x)-(frosh[first].x-frosh[cur1].x)*(frosh[cur2].y-frosh[cur1].y));
	int sign2 = (int)(frosh[first].y*frosh[cur1].x-frosh[first].x*frosh[cur1].y);
	int sign3 = (int)(frosh[first].y*frosh[cur2].x-frosh[first].x*frosh[cur2].y);
	if(sign0*sign1 >= 0 || sign2*sign3 >= 0)
		return false;
	return true;
}

double draw_line()
{
	int i, j, k;
	Polygon polygon;
	int last_idx;
	bool finished;
	double len, min_len = 0xffffffff;
	
	sort_and_remove_duplicates();
	
	if(n == 1)
		min_len = 2.0;
	else if(n == 2)
		min_len = 2.0+2*sqrt(frosh[1].x*frosh[1].x+frosh[1].y*frosh[1].y);
	else
	{
		for(i = 1; i < n; i++)
		{
			polygon.n = 2;
			polygon.p_idx[0] = 0;
			polygon.p_idx[1] = i;
			if(i == 1)
				last_idx = n-1;
			else
				last_idx = i-1;
			finished = false;
			for(j = i+1; ; j++)
			{
				if(j >= n)
					j = 1;
				if(polygon.p_idx[polygon.n-1] != i && intersect(i, polygon.p_idx[polygon.n-1], j))
					break;
				for(k = polygon.n-1; k > 0; k--)
				{
					if(ccw(frosh[polygon.p_idx[k-1]], frosh[polygon.p_idx[k]], frosh[j]) || collinear(frosh[0], frosh[polygon.p_idx[k]], frosh[j]))
					{
						polygon.p_idx[k+1] = j;
						break;
					}
				}
				polygon.n = k+2;
				if(k == 0)
					break;
				if(j == last_idx)
				{
					if(ccw(frosh[polygon.p_idx[k]], frosh[j], frosh[0]) || collinear(frosh[0], frosh[polygon.p_idx[k]], frosh[j]))
						finished = true;
					break;
				}
			}
			if(finished)
			{
				len = 2.0;
				polygon.p_idx[polygon.n] = 0;
				for(k = 0; k < polygon.n; k++)
				{
					len += distance(frosh[polygon.p_idx[k]], frosh[polygon.p_idx[k+1]]);
				}
				if(len < min_len)
					min_len = len;
			}
		}
	}
	return min_len;
}

int main()
{
	int test_case, i;
	double length;
	scanf("%d", &test_case);
	while(test_case--)
	{
		scanf("%d", &n);
		for(i = 0; i < n; i++)
		{
			scanf("%lf%lf", &frosh[i].x, &frosh[i].y);
			if(frosh[i].x == 0 && frosh[i].y == 0)
				frosh[i].polar_angle = -100;
			else
				frosh[i].polar_angle = atan2(frosh[i].x, frosh[i].y);
		}
		frosh[n].x = frosh[n].y = 0;
		frosh[n].polar_angle = -100;
		n++;
		
		length = draw_line();
		
		printf("%.2lf\n", length);
		if(test_case)
			printf("\n");
	}
	return 0;
}
