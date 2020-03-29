#include <stdio.h>
#include <math.h>

int step_cw[3][2] = {{-1, 1}, {-1, 0}, {0, -1}};	// clockwise
int step_ccw[3][2] = {{0, -1}, {-1, 0}, {-1, 1}};	//counter-clockwise

inline void move_cw(int s, int *x, int *y)
{
	*x += step_cw[s][0];
	*y += step_cw[s][1];
}

inline void move_ccw(int s, int *x, int *y)
{
	*x += step_ccw[s][0];
	*y += step_ccw[s][1];
}

int main()
{
	int i, n, l, r, h, x, y;
	while(scanf("%d", &n) != EOF)
	{
		if(n == 1)
			printf("0 0\n");
		else
		{
			l = (int)(sqrt(((double)(n-1)-0.25)/3)-0.5);
			r = n-(3*l*l+3*l+1);
			l += 1;
			h = 6*l;
			x = l;
			y = 0;
			if(r <= h/2)
			{
				for(i = 0; i < r; i++)
				{
					if(i < l)
						move_cw(0, &x, &y);
					else if(i < 2*l)
						move_cw(1, &x, &y);
					else if(i < 3*l)
						move_cw(2, &x, &y);
				}
			}
			else
			{
				r = h - r;
				for(i = 0; i < r; i++)
				{
					if(i < l)
						move_ccw(0, &x, &y);
					else if(i < 2*l)
						move_ccw(1, &x, &y);
					else if(i < 3*l)
						move_ccw(2, &x, &y);
				}
			}
			printf("%d %d\n", x, y);
		}
	}
	return 0;
}
