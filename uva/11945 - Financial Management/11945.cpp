#include <stdio.h>
#include <string.h>

int main()
{
	int tc, i, j, n, l;
	float cb;
	float avg;
	char temp[64], output[64];
	scanf("%d", &n);
	for(tc = 1; tc <= n; tc++)
	{
		avg = 0;
		for(i=0;i<12;i++)
		{
			scanf("%f",&cb);
			avg+=cb;
		}
		avg/=12;
		sprintf(temp, "%.2f", avg);
		l = strlen(temp);
		for(i = j = 0; i < l; i++)
		{
			output[j++] = temp[i];
			if(i < l-6 && (l-7-i)%3 == 0)
				output[j++] = ',';
		}
		output[j] = '\0';
		printf("%d $%s\n", tc, output);
	}
	return 0;
}
