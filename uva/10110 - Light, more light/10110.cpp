#include <cstdio>
#include <cmath>

int main()
{
	unsigned int n;
	unsigned int sr;
	while(scanf("%d", &n)!=EOF)
	{
		if(n==0)
			break;
		sr = (unsigned int)sqrt((double)n);
		if(sr*sr==n || (sr+1)*(sr+1)==n)
			printf("yes\n");
		else
			printf("no\n");
	}
	return 0;
}