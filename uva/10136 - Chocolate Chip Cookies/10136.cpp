#include <stdio.h>
#include <math.h>

#define DIAMETER 5.0
#define RADIUS (DIAMETER/2.0)
#define PI 3.141592653589793

struct Point
{
	double x, y;
};

int nchips;
Point chip[200];

inline double distance(Point p1, Point p2)
{
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

void circle_center(Point p1, Point p2, double dist, Point *cc1, Point *cc2)
{
	double angle0, temp_angle, k1, k2;
	if(p1.x == p2.x)
		angle0 = PI/2;
	else
		angle0 = atan((p1.y-p2.y)/(p1.x-p2.x));
	temp_angle = acos(dist/DIAMETER);	// dist != 0
	if(temp_angle == 0)	// dist == DIAMETER, approximately
	{
		cc1->x = (p1.x+p2.x)/2;
		cc1->y = (p1.y+p2.y)/2;
		cc2->x = cc1->x;
		cc2->y = cc1->y;
		return;
	}
	// angle0 in (-PI/2,PI/2], temp_angle in (0,PI/2)
	k1 = tan(angle0+temp_angle);
	k2 = tan(angle0-temp_angle);
	// cc1
	double b1 = p1.y-k1*p1.x;
	double b2 = p2.y-k2*p2.x;
	cc1->x = (b1-b2)/(k2-k1);
	cc1->y = k1*cc1->x+b1;
	// cc2
	b1 = p1.y-k2*p1.x;
	b2 = p2.y-k1*p2.x;
	cc2->x = (b1-b2)/(k1-k2);
	cc2->y = k1*cc2->x+b2;
}

int main()
{
	int i, j, k, tc, c, maxc;
	char input[32];
	Point cc1, cc2;
	scanf("%d", &tc);
	fgets(input, sizeof(input), stdin);
	fgets(input, sizeof(input), stdin);
	while(tc--)
	{
		nchips = 0;
		while(fgets(input, sizeof(input), stdin))
		{
			if(input[0] == '\n')
				break;
			sscanf(input, "%lf%lf", &chip[nchips].x, &chip[nchips].y);
			nchips++;
		}
		if(nchips == 0)
			maxc = 0;
		else
			maxc = 1;
		for(i = 0; i < nchips; i++)
		{
			for(j = i+1; j < nchips; j++)
			{
				double dist = distance(chip[i], chip[j]);
				if(dist > DIAMETER)
					continue;
				circle_center(chip[i], chip[j], dist, &cc1, &cc2);
				c = 2;
				for(k = 0; k < nchips; k++)
				{
					if(k == i || k == j)
						continue;
					if(distance(chip[k], cc1) <= RADIUS)
						c++;
				}
				if(c > maxc)
					maxc = c;
				c = 2;
				for(k = 0; k < nchips; k++)
				{
					if(k == i || k == j)
						continue;
					if(distance(chip[k], cc2) <= RADIUS)
						c++;
				}
				if(c > maxc)
					maxc = c;
			}
		}
		printf("%d\n", maxc);
		if(tc > 0)
			printf("\n");
	}
	return 0;
}
