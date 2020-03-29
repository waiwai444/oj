#include <stdio.h>

int main()
{
	int i, j, n;
	int line_count[13], max_count, nvoids;
	char line[30];
	while(fgets(line, 30, stdin))
	{
		sscanf(line, "%d", &n);
		if(n == 0)
			break;
		max_count = 0;
		for(i = 0; i < n; i++)
		{
			fgets(line, 30, stdin);
			line_count[i] = 0;
			for(j = 0; j < 25; j++)
			{
				if(line[j] == ' ')
					break;
				line_count[i]++;
			}
			if(j < 25)
			{
				for(j = 24; j >= 0; j--)
				{
					if(line[j] == ' ')
						break;
					line_count[i]++;
				}
			}
			if(line_count[i] > max_count)
				max_count = line_count[i];
		}
		nvoids = 0;
		for(i = 0; i < n; i++)
		{
			nvoids += max_count-line_count[i];
		}
		printf("%d\n", nvoids);
	}
	return 0;
}
