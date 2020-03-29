#include <stdio.h>

int main()
{
	int a, b, tc;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d", &a, &b);
		if(a < b)
			printf("<\n");
		else if(a > b)
			printf(">\n");
		else
			printf("=\n");
	}
	return 0;
}