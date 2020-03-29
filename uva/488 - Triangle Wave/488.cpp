#include <stdio.h>

int main()
{
	int i, j, k, l, ampl, freq, tc;
	char output[100];
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d", &ampl, &freq);
		for(i = 0; i < freq; i++)
		{
			l = 0;
			for(j = 1; j <= ampl; j++)
			{
				for(k = 0; k < j; k++)
				{
					output[l++] = '0'+j;
				}
				output[l++] = '\n';
			}
			for(j = ampl-1; j > 0; j--)
			{
				for(k = 0; k < j; k++)
				{
					output[l++] = '0'+j;
				}
				output[l++] = '\n';
			}
			output[l] = '\0';			
			if(i < freq-1 || tc > 0)
				printf("%s\n", output);
			else
				printf("%s", output);
		}
	}
	return 0;
}
