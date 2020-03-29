#include <stdio.h>
#include <ctype.h>

int main()
{
	int i, count;
	bool in;
	char line[1024];
	while(fgets(line, 1024, stdin))
	{
		count = 0;
		i = 0;
		in = false;
		while(line[i] != '\0')
		{
			if(isalpha(line[i]))
			{
				if(!in)
					in = true;
			}
			else if(in)
			{
				count++;
				in = false;
			}
			i++;
		}
		printf("%d\n", count);
	}
	return 0;
}
