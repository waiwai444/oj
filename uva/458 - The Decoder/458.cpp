#include <stdio.h>

#define OFFSET 7

int main()
{
	int i;
	char line[1024];
	while(fgets(line, 1024, stdin))
	{
		for(i = 0; i < 1024; i++)
		{
			if(line[i] == '\n')
				break;
			line[i] -= OFFSET;
		}
		printf("%s", line);
	}
	return 0;
}
