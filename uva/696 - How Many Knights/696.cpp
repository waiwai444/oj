#include <stdio.h>

int m, n;

int solve()
{
	if(m == 0 || n == 0) return 0;
	if(m == 1) return n;
	if(n == 1) return m;
	if(m == 2) return n%4 == 1 ? n+1 : ((n-1)/4+1)*4;
	if(n == 2) return m%4 == 1 ? m+1 : ((m-1)/4+1)*4;
	return (m*n+1)/2;
}

int main()
{
	while(scanf("%d%d", &m, &n), m || n)
	{
		printf("%d knights may be placed on a %d row %d column board.\n", solve(), m, n);
	}
	return 0;
}

