#include <stdio.h>

int x, k;
int r;

int main()
{
	int tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d", &x, &k);
		r = x%k;
		printf("%d %d\n", k-r, r);
	}
	return 0;
}
