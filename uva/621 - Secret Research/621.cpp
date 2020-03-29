#include <stdio.h>
#include <string.h>

int main()
{
	int n;
	char code[1000];
	scanf("%d", &n);
	while(n--)
	{
		scanf("%s", code);
		int len = strlen(code);
		if(len <= 2)
			printf("+\n");
		else if(code[len-2] == '3' && code[len-1] == '5')
			printf("-\n");
		else if(code[0] == '9' && code[len-1] == '4')
			printf("*\n");
		else
			printf("?\n");
	}
	return 0;
}
