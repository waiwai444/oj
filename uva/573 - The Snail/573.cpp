#include <stdio.h>

int main()
{
	int t, h, u, d, f;
	while(scanf("%d%d%d%d", &h, &u, &d, &f), h)
	{
		h *= 100;
		u *= 100;
		d *= 100;
		int delta = u*f/100;
		t = 1;
		int cur_h = u;
		int cur_u = u;
		while(cur_h <= h)
		{
			cur_h -= d;
			if(cur_h < 0)
				break;
			cur_u -= delta;
			if(cur_u < 0)
				cur_u = 0;
			t++;
			cur_h += cur_u;
		}
		if(cur_h < 0)
			printf("failure on day %d\n", t);
		else
			printf("success on day %d\n", t);
	}
	return 0;
}