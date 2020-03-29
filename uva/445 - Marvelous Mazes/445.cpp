#include <stdio.h>
#include <string.h>
#include <ctype.h>

char maze_row[133];

int main()
{
	int i, k, num;
	char ch, line[520];
	bool printed = false;
	while(fgets(line, sizeof(line), stdin))
	{
		line[strlen(line)-1] = 0;
		if(line[0] == '\0')
		{
			printf("\n");
			continue;
		}
		i = k = num = 0;
		while(line[i] != '\0')
		{
			if(printed)
				printed = false;
			if(isdigit(line[i]))
				num += line[i]-'0';
			else if(line[i] == '!')
			{
				maze_row[k] = '\0';
				printf("%s\n", maze_row);
				k = 0;
				printed = true;
			}
			else
			{
				if(line[i] == 'b')
					ch = ' ';
				else
					ch = line[i];
				while(num > 0)
				{
					maze_row[k++] = ch;
					num--;
				}
			}
			i++;
		}
		if(!printed)
		{
			maze_row[k] = '\0';
			printf("%s\n", maze_row);
		}
	}
	return 0;
}
