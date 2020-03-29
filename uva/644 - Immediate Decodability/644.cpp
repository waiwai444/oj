#include <stdio.h>
#include <string.h>

#define NONE 0
#define ONPATH 1
#define FINISH 2

char flag[2048];

int main()
{
	int i, j, tc;
	char code[11];
	bool decodable;
	tc = 0;
	while(scanf("%s", code) != EOF)
	{
		decodable = true;
		memset(flag, NONE, sizeof(flag));
		while(code[0] != '9')
		{
			i = j = 0;
			while(decodable && code[i] != '\0')
			{
				if(code[i] == '0')
					j = (j+1)*2-1;
				else
					j = (j+1)*2;
				if(flag[j] == FINISH)
					break;
				if(code[i+1] != '\0')
					flag[j] = ONPATH;
				i++;
			}
			if(flag[j] == ONPATH || flag[j] == FINISH)
				decodable = false;
			else
				flag[j] = FINISH;
			scanf("%s", code);
		}
		if(decodable)
			printf("Set %d is immediately decodable\n", ++tc);
		else
			printf("Set %d is not immediately decodable\n", ++tc);
	}
	return 0;
}