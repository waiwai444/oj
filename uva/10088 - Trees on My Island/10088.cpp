#include <stdio.h>

#define MAXP 1000

struct Point
{
	int x, y;
};

int n;
Point pt[MAXP];

inline double polygon_area()
{
	double area = (long long)pt[n-1].x*pt[0].y-(long long)pt[0].x*pt[n-1].y;
	for(int i = 1; i < n; i++)
		area += (long long)pt[i-1].x*pt[i].y-(long long)pt[i].x*pt[i-1].y;
	area /= 2.0;
	return area > 0 ? area : -area;
}

int gcd(int x, int y)
{
	return y == 0 ? x : gcd(y, x%y);
}

int count_integral_pt(int x1, int y1, int x2, int y2)
{
	int i, j, cnt;
	if(x1 == x2)
	{
		if(y1 > y2)
		{
			i = y2;
			j = y1;
		}
		else
		{
			i = y1;
			j = y2;
		}
		cnt = j-i;
	}
	else if(y1 == y2)
	{
		if(x1 > x2)
		{
			i = x2;
			j = x1;
		}
		else
		{
			i = x1;
			j = x2;
		}
		cnt = j-i;
	}
	else
	{
		if(y1 > y2)
		{
			i = y2;
			j = y1;
		}
		else
		{
			i = y1;
			j = y2;
		}
		int dx = x2-x1;
		if(dx < 0)
			dx = -dx;
		int dy = y2-y1;
		if(dy < 0)
			dy = -dy;
		int d = gcd(dx, dy);
		cnt = d;
	}
	
	return cnt;
}

int main()
{
	int i;
	while(scanf("%d", &n), n)
	{
		for(i = 0; i < n; i++)
			scanf("%d%d", &pt[i].x, &pt[i].y);

		double area = polygon_area();

		long long border_pt = count_integral_pt(pt[n-1].x, pt[n-1].y, pt[0].x, pt[0].y);
		for(i = 1; i < n; i++)
			border_pt += count_integral_pt(pt[i-1].x, pt[i-1].y, pt[i].x, pt[i].y);

		long long inner_pt = ((long long)(area*2)-border_pt+2)/2;
		printf("%lld\n", inner_pt);
	}
	return 0;
}
