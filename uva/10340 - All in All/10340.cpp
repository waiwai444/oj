#include <stdio.h>

char s[100000], t[100000];

int main()
{
	int i, j;
	while(scanf("%s%s", s, t) != EOF)
	{
		i = j = 0;
		while(t[j] != '\0')
		{
			if(s[i] == t[j])
			{
				i++;
				if(s[i] == '\0')
					break;
			}
			j++;
		}
		if(s[i] == '\0')
			printf("Yes\n");
		else
			printf("No\n");
	}
	return 0;
}
