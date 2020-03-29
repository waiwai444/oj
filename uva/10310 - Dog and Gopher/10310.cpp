#include <stdio.h>

int main()
{
	int i, n;
	double xd, yd, xg, yg, xh, yh;
	double dd, dg;
	bool escaped;
	while(scanf("%d%lf%lf%lf%lf", &n, &xg, &yg, &xd, &yd) != EOF)
	{
		escaped = false;
		for(i = 0; i < n; i++)
		{
			scanf("%lf%lf", &xh, &yh);
			if(!escaped)
			{
				dd = (xd-xh)*(xd-xh)+(yd-yh)*(yd-yh);
				dg = (xg-xh)*(xg-xh)+(yg-yh)*(yg-yh);
				if(dd/4 >= dg)
				{
					printf("The gopher can escape through the hole at (%.3lf,%.3lf).\n", xh, yh);
					escaped = true;
				}
			}
		}
		if(!escaped)
			printf("The gopher cannot escape.\n");
	}
}
