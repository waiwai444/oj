#include <stdio.h>

int main()
{
	int s, d, m;
	while(scanf("%d%d", &s, &d) != EOF)
	{
		if(4*s < d)
			m = 10*s-2*d;
		else if(3*s < 2*d)
			m = 8*s-4*d;
		else if(2*s < 3*d)
			m = 6*s-6*d;
		else if(s < 4*d)
			m = 3*s-9*d;
		else
			m = -12*d;
		if(m >= 0)
			printf("%d\n", m);
		else
			printf("Deficit\n");
	}
	return 0;
}
