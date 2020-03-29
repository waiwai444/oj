#include <stdio.h>
#include <math.h>
#include <float.h>
#include <algorithm>

int nv;
int x[50], y[50];

bool linkable[50][50];
double dp[50][50];

#define EPS 1e-9
#define NEXT(i) ((i+1)%nv)
#define PREV(i) (i ? i-1 : nv-1)
#define EQUAL(x, y) (fabs(x-y) < EPS)

double get_area(double x1, double y1, double x2, double y2, double x3, double y3)
{
	return fabs(((x2-x1)*(y3-y1)-(y2-y1)*(x3-x1))/2);
}

bool line_seg_intersect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4)
{
	int p1 = (y2-y1)*(x3-x1)-(x2-x1)*(y3-y1);
	int p2 = (y2-y1)*(x4-x1)-(x2-x1)*(y4-y1);
	int q1 = (y4-y3)*(x1-x3)-(x4-x3)*(y1-y3);
	int q2 = (y4-y3)*(x2-x3)-(x4-x3)*(y2-y3);
	if(p1 == 0 && p2 == 0)
	{
		int l = std::min(x3, x4), r = std::max(x3, x4), b = std::min(y3, y4), t = std::max(y3, y4);
		return x1 >= l && x1 <= r && y1 >= b && y1 <= t || x2 >= l && x2 <= r && y2 >= b && y2 <= t;
	}
	return (long long)p1*p2 <= 0 && (long long)q1*q2 <= 0;
}

bool in_polygon(double xx, double yy)
{
	int i, j, x1, y1, x2, y2;
	bool in = false;
	for(j = nv-1, i = 0; i < nv; j = i++)
	{
		x1 = x[j]; y1 = y[j];
		x2 = x[i]; y2 = y[i];
		if(yy >= std::min(y1, y2) && yy < std::max(y1, y2) && (x2-x1)*(yy-y1)/(y2-y1)+x1 > xx) 
			in = !in;
	}
	return in;
}

void check_linkable()
{
	int i, j, k, l;
	for(i = 0; i < nv-1; i++)
	{
		linkable[i][i+1] = linkable[i+1][i] = true;
		for(j = i+2; j < nv; j++)
		{
			if(!in_polygon((double)(x[i]+x[j])/2, (double)(y[i]+y[j])/2))
			{
				linkable[i][j] = linkable[j][i] = false;
			}
			else
			{
				for(k = 0; k < nv; k++)
				{
					l = NEXT(k);
					if(k != i && k != j && l != i && l != j)
					{
						if(line_seg_intersect(x[i], y[i], x[j], y[j], x[k], y[k], x[l], y[l]))
						{
							break;
						}
					}
				}
				linkable[i][j] = linkable[j][i] = (k == nv);
			}
		}
	}
	linkable[0][nv-1] = linkable[nv-1][0] = true;
}

double solve()
{
	int d, i, j, k;
	double tmp;
	check_linkable();
	for(d = 2; d < nv; d++)
	{
		for(i = 0; i < nv; i++)
		{
			j = (i+d)%nv;
			dp[i][j] = DBL_MAX;
			if(linkable[i][j])
			{
				for(k = NEXT(i); k != j; k = NEXT(k))
				{
					if(linkable[i][k] && linkable[j][k])
					{
						tmp = get_area(x[i], y[i], x[j], y[j], x[k], y[k]);
						if(tmp < dp[i][k])
							tmp = dp[i][k];
						if(tmp < dp[k][j])
							tmp = dp[k][j];
						if(tmp < dp[i][j])
							dp[i][j] = tmp;
					}
				}
			}
		}
	}
	return dp[0][nv-1];
}

int main()
{
	int i, tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d", &nv);
		for(i = 0; i < nv; i++)
			scanf("%d%d", &x[i], &y[i]);
		printf("%.1lf\n", solve());
	}
	return 0;
}
