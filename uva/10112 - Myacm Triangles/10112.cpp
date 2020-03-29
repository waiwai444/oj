#include <stdio.h>
#include <math.h>

#define EPS 1e-9

struct Monument
{
	char label;
	int x, y;
};

double get_area(int x1, int y1, int x2, int y2, int x3, int y3)
{
	return fabs(0.5*((y3-y1)*(x2-x1)-(y2-y1)*(x3-x1)));
}

int main()
{
	int n, i, j, k, l;
	char label[2];
	Monument mon[15];
	while(scanf("%d", &n), n)
	{
		for(i = 0; i < n; i++)
		{
			scanf("%s%d%d", label, &mon[i].x, &mon[i].y);
			mon[i].label = label[0];
		}
		int max_i, max_j, max_k;
		double max_area = 0, cur_area;
		for(i = 0; i < n-2; i++)
		{
			for(j = 0; j < n-1; j++)
			{
				for(k = 0; k < n; k++)
				{
					cur_area = get_area(mon[i].x, mon[i].y, mon[j].x, mon[j].y, mon[k].x, mon[k].y);
					for(l = 0; l < n; l++)
					{
						if(l == i || l == j || l == k)
							continue;
						if(get_area(mon[i].x, mon[i].y, mon[j].x, mon[j].y, mon[l].x, mon[l].y)+
							get_area(mon[i].x, mon[i].y, mon[l].x, mon[l].y, mon[k].x, mon[k].y)+
							get_area(mon[l].x, mon[l].y, mon[j].x, mon[j].y, mon[k].x, mon[k].y) < cur_area+EPS)
							break;
					}
					if(l == n && cur_area > max_area)
					{
						max_area = cur_area;
						max_i = i;
						max_j = j;
						max_k = k;
					}
				}
			}
		}
		printf("%c%c%c\n", mon[max_i].label, mon[max_j].label, mon[max_k].label);
	}
	return 0;
}