#include <stdio.h>
#include <math.h>

int main()
{
	int i, m, p, a, b;
	double s, sum1, sump, ub, lb, ubp, lbp;
	while(scanf("%d%d%d%d", &m, &p, &a, &b) != EOF)
	{
		ub = sqrt((double)a);
		lb = -1/ub;
		ubp = pow((double)a, p/2);
		lbp = 1/ubp;
		sum1 = b*ub;
		s = sump = 0;
		if(a >= 1)
		{
			for(i = 0; i < m && s+ub+lb*(m-i-1) <= sum1; ++i)
			{
				sump += ubp;
				s += ub;
			}
			sump += lbp*(m-1-i)+pow(s+lb*(m-1-i)-sum1, p);
		}
		else
		{
			for(i = 0; i < m && s+lb+ub*(m-i-1) >= sum1; ++i)
			{
				sump += lbp;
				s += lb;
			}
			sump += ubp*(m-1-i)+pow(sum1-s-ub*(m-1-i), p);
		}
		printf("%lld\n", (long long)(sump+0.5));
	}
	return 0;
}
