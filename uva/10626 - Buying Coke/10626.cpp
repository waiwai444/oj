#include <stdio.h>

int nc, n1, n5, n10;

int main()
{
	int tc, result, tmp;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d%d%d", &nc, &n1, &n5, &n10);
		if(n10 >= nc)
			result = nc;
		else
		{
			result = n10;
			nc -= n10;
			if(n5 >= nc*2)
				result += nc*2;
			else if(n5 >= nc)
				result += n5+(2*nc-n5)*3;
			else
			{
				result += n5+nc*3;
				tmp = nc-n5;
				if(n10 < tmp)
					tmp = n10;
				result += tmp*4+(nc-n5-tmp)*5;
			}
		}
		printf("%d\n", result);
	}
	return 0;
}
