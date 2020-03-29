#include <stdio.h>
#include <math.h>

#define PERIOD 2
#define PI 3.141592653589793
#define EPS (1e-8)

inline bool collinear(double x1, double y1, double x2, double y2, double x3, double y3)
{
	double sa = x1*y2+x2*y3+x3*y1-x1*y3-x2*y1-x3*y2;
	return sa < EPS && sa > -EPS;
}

inline bool ccw(double x1, double y1, double x2, double y2, double x3, double y3)
{
	return x1*y2+x2*y3+x3*y1-x1*y3-x2*y1-x3*y2 >= EPS;
}

inline bool cw(double x1, double y1, double x2, double y2, double x3, double y3)
{
	return x1*y2+x2*y3+x3*y1-x1*y3-x2*y1-x3*y2 <= -EPS;
}

inline bool on_origin(double x, double y)
{
	return x < EPS && x > -EPS && y < EPS && y > -EPS;
}

inline double to_degree(double arc)
{
	return 360*arc/(2*PI);
}

inline double to_arc(double degree)
{
	return (2*PI)*degree/360;
}

inline bool equal(double x, double y)
{
	return fabs(x-y) < EPS;
}

inline double get_included_angle(double a1, double a2)
{
	double included_angle = a2-a1;
	if(included_angle < 0)
		included_angle += 360;
	return included_angle;
}

inline void polar_to_cartesian(double a, double d, double *x, double *y)
{
	double arc = to_arc(a);
	*x = d*cos(arc);
	*y = d*sin(arc);
}

inline void cartesian_to_polar(double x, double y, double *a, double *d)
{
	*d = sqrt(x*x+y*y);
	*a = atan2(y, x);
	if(*a < 0)
		*a += 2*PI;
	*a = to_degree(*a);
}

inline double first_period_angle(double angle)
{
	if(angle >= 360)
		do{ angle -= 360; } while(angle >= 360);
	else if(angle < 0)
		do{ angle += 360; } while(angle < 0);
	return angle;
}

double angle_diff(double t, double radar_init_angle, double obj_init_x, double obj_init_y, double obj_vx, double obj_vy)	// take radar_init_angle as the starting angle
{
	double angle1 = to_degree(atan2(obj_init_y+obj_vy*t, obj_init_x+obj_vx*t));
	if(angle1 < 0)
		angle1 += 360;
	if(angle1 < radar_init_angle)
		angle1 += 360;
	double angle2 = radar_init_angle+360/PERIOD*t;
	return angle1-angle2;
}

bool next_intersect_time(double radar_init_angle, double obj_init_x, double obj_init_y, double obj_vx, double obj_vy, double time_lbound, double time_ubound, double *next_time)	// don't call this function when there are more than one intersection time in the time bounds
{
	const double TIME_EPS = 1e-15;
	time_ubound -= TIME_EPS;
	time_lbound += TIME_EPS;
	double dl, du, dm, time_mid = (time_ubound+time_lbound)/2.0;
	while(time_ubound-time_lbound >= TIME_EPS)
	{
		dl = angle_diff(time_lbound, radar_init_angle, obj_init_x, obj_init_y, obj_vx, obj_vy);
		du = angle_diff(time_ubound, radar_init_angle, obj_init_x, obj_init_y, obj_vx, obj_vy);
		dm = angle_diff(time_mid, radar_init_angle, obj_init_x, obj_init_y, obj_vx, obj_vy);
		if(equal(dm, 0.0))
		{
			*next_time = time_mid;
			return true;
		}
		else
		{
			if(dl*dm < 0)
				time_ubound = time_mid;
			else if(dm*du < 0)
				time_lbound = time_mid;
			else
				break;
			time_mid = (time_ubound+time_lbound)/2.0;
		}
	}
	*next_time = time_mid;
	if(equal(angle_diff(time_mid, radar_init_angle, obj_init_x, obj_init_y, obj_vx, obj_vy), 0.0))
		return true;
	else
		return false;
}

int process(double a1, double d1, double a2, double d2, double *a3, double *d3)
{
	int r = 0;
	double x1, y1, x2, y2, x3, y3;
	double vx, vy, t;
	
	a1 = first_period_angle(a1);
	a2 = first_period_angle(a2);
	
	polar_to_cartesian(a1, d1, &x1, &y1);
	polar_to_cartesian(a2, d2, &x2, &y2);
	if(collinear(x1, y1, x2, y2, 0.0, 0.0))	// through the origin
	{
		if(x1 >= 0 && x2 >= 0 || x1 < 0 && x2 < 0)	// p1 and p2 are in the same side of the origin
		{
			vx = (x2-x1)/PERIOD;
			vy = (y2-y1)/PERIOD;
			t = PERIOD/2;
			x3 = x2+vx*t;
			y3 = y2+vy*t;
			if(x1 > 0 && x3 < 0 || x1 < 0 && x3 > 0 || x1 == 0 && (y1 > 0 && y3 < 0 || y1 < 0 && y3 > 0))
			{
				cartesian_to_polar(x3, y3, a3, d3);
			}
			else if(on_origin(x3, y3))
			{
				x3 += vx*PERIOD;
				y3 += vy*PERIOD;
				cartesian_to_polar(x3, y3, a3, d3);
			}
			else
			{
				t = PERIOD/2;
				x3 += vx*t;
				y3 += vy*t;
				if(x1 > 0 && x3 > 0 || x1 < 0 && x3 < 0 || x1 == 0 && (y1 > 0 && y3 > 0 || y1 < 0 && y3 < 0))
				{
					cartesian_to_polar(x3, y3, a3, d3);
				}
				else
				{
					x3 += vx*t;
					y3 += vy*t;
					cartesian_to_polar(x3, y3, a3, d3);
				}
			}
			return r = 1;
		}
		else	// p1 and p2 are in different sides of the origin
		{
			// meet p2 at the first period (half cycle)
			t = PERIOD/2;
			vx = (x2-x1)/t;
			vy = (y2-y1)/t;
			x3 = x2+vx*PERIOD;
			y3 = y2+vy*PERIOD;
			cartesian_to_polar(x3, y3, a3, d3);
			r++;
			
			// meet p2 at the next period
			if(x1 != 0 && fabs(x2-x1) >= 2*fabs(x1) || x1 == 0 && fabs(y2-y1) >= 2*fabs(y1))
			{
				t = PERIOD*1.5;
				vx = (x2-x1)/t;
				vy = (y2-y1)/t;
				x3 = x2+vx*PERIOD;
				y3 = y2+vy*PERIOD;
				cartesian_to_polar(x3, y3, &a3[1], &d3[1]);
				r++;
			}
			
			return r;
		}
	}
	else	// not through the origin
	{
		double included_angle;
		if(ccw(x1, y1, 0.0, 0.0, x2, y2))
		{
			included_angle = get_included_angle(a2, a1);
			t = PERIOD*(360-included_angle)/360;
			vx = (x2-x1)/t;
			vy = (y2-y1)/t;
			x3 = x2+vx*PERIOD/2;
			y3 = y2+vy*PERIOD/2;
			next_intersect_time(a2+180, x3, y3, vx, vy, 0, PERIOD/2, &t);
			x3 += vx*t;
			y3 += vy*t;
			cartesian_to_polar(x3, y3, a3, d3);
			return r = 1;
		}
		else	// cw(x1, y1, 0.0, 0.0, x2, y2)
		{
			included_angle = get_included_angle(a1, a2);
			
			// meet p2 at the first period
			t = PERIOD*included_angle/360;
			vx = (x2-x1)/t;
			vy = (y2-y1)/t;
			//if(!next_intersect_time(a1, x1, y1, vx, vy, 0, t, &t))	// there is no intersection time between p1 and p2 (don't consider this case in the dataset of uva)
			{
				if(next_intersect_time(a2, x2, y2, vx, vy, 0, PERIOD/2, &t))	// if meet p3 at the same period
				{
					x3 = x2+vx*t;
					y3 = y2+vy*t;
				}
				else	// if meet p3 at the second period
				{
					x3 = x2+vx*PERIOD;
					y3 = y2+vy*PERIOD;
					next_intersect_time(a2, x3, y3, vx, vy, 0, PERIOD/2, &t);
					x3 += vx*t;
					y3 += vy*t;
				}
				cartesian_to_polar(x3, y3, a3, d3);
				r++;
			}
			
			// meet p2 at the second period
			t = PERIOD*included_angle/360+PERIOD;
			vx = (x2-x1)/t;
			vy = (y2-y1)/t;
			if(next_intersect_time(a2, x2, y2, vx, vy, 0, PERIOD/2, &t))	// if meet p3 at the same period
			{
				x3 = x2+vx*t;
				y3 = y2+vy*t;
			}
			else	// if meet p3 at the third period
			{
				x3 = x2+vx*PERIOD;
				y3 = y2+vy*PERIOD;
				next_intersect_time(a2, x3, y3, vx, vy, 0, PERIOD/2, &t);
				x3 += vx*t;
				y3 += vy*t;
			}
			cartesian_to_polar(x3, y3, &a3[r], &d3[r]);
			r++;
			return r;
		}
	}
}

inline double round2(double x)
{
	return (int)(x*100+0.5)/100.0;
}

int main()
{
	double a1, d1, a2, d2;
	double a3[2], d3[2];
	int r;
	while(scanf("%lf%lf%lf%lf", &a1, &d1, &a2, &d2) != EOF)
	{
		r = process(a1, d1, a2, d2, a3, d3);
		if(r == 1)
			printf("%.2lf %.2lf\n", a3[0], d3[0]);
		else
		{
			// sort the result
			a3[0] = round2(a3[0]);
			d3[0] = round2(d3[0]);
			a3[1] = round2(a3[1]);
			d3[1] = round2(d3[1]);
			if(a3[0] > a3[1] || a3[0] == a3[1] && d3[0] < d3[1])
			{
				double tmp = a3[0];
				a3[0] = a3[1];
				a3[1] = tmp;
				tmp = d3[0];
				d3[0] = d3[1];
				d3[1] = tmp;
			}
			printf("%.2lf %.2lf %.2lf %.2lf\n", a3[0], d3[0], a3[1], d3[1]);
		}
	}
	return 0;
}
