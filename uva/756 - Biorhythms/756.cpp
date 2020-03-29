#include <stdio.h>

int main()
{
	int p, e, i, d;
	int c;
	int result;
	c = 0;
	while(1)
	{
		c++;
		scanf("%d %d %d %d", &p, &e, &i, &d);
		if(p==-1)
			break;
		result = (1288*i+5544*p+14421*e-21252)%21252;
		if(result<=d)
			result += 21252;
		printf("Case %d: the next triple peak occurs in %d days.\n", c, result-d);
	}
	return 0;
}