#include <stdio.h>
#include <string.h>

int main()
{
	int i, j, len;
	char input[1000], output[1500];
	bool open = true;
	while(fgets(input, 1000, stdin) != NULL)
	{
		len = strlen(input);
		for(i = j = 0; i < len; i++)
		{
			if(input[i] == '"')
			{
				if(open)
				{
					output[j++] = '`';
					output[j++] = '`';
				}
				else
				{
					output[j++] = '\'';
					output[j++] = '\'';
				}
				open = !open;
			}
			else
				output[j++] = input[i];
		}
		output[j] = '\0';
		printf("%s", output);
	}
	return 0;
}
