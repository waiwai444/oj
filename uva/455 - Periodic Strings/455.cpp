#include <stdio.h>
#include <string.h>

int main()
{
	int i, j, k, n;
	char input[81];
	scanf("%d", &n);
	while(n--)
	{
		scanf("%s", input);
		int len = strlen(input);
		for(i = 1; i <= len; i++)
		{
			if(len%i == 0)
			{
				for(j = 0; j < i; j++)
				{
					for(k = len/i-1; k > 0; k--)
						if(input[j] != input[j+k*i])
							goto failed;
				}
				break;
			}
			failed:;
		}
		printf("%d\n", i);
		if(n > 0)
			printf("\n");
	}
	return 0;
}
