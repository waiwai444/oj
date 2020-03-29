#include <stdio.h>

double c[3000];

int main()
{
	int i, tc, n;
	double a0, anp;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%lf%lf", &n, &a0, &anp);
		for(i = 0; i < n; i++)
			scanf("%lf", &c[i]);
		double s1 = 0, s2 = 0;
		for(i = 0; i < n; i++)
		{
			s1 += c[i];
			s2 += (n-i-1)*c[i];
		}
		printf("%.2lf\n", (n*a0+anp-2*(s1+s2))/(n+1));
		if(tc > 0)
			printf("\n");
	}
	return 0;
}