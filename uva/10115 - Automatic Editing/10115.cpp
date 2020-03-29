#include <stdio.h>
#include <string.h>
#include <string>

int main()
{
	int i, n;
	char temp[300];
	std::string find[10], replace[10], text;
	size_t pos;
	while(scanf("%d", &n), n)
	{
		fgets(temp, sizeof(temp), stdin);
		for(i = 0; i < n; i++)
		{
			fgets(temp, sizeof(temp), stdin);
			temp[strlen(temp)-1] = 0;
			find[i] = temp;
			fgets(temp, sizeof(temp), stdin);
			temp[strlen(temp)-1] = 0;
			replace[i] = temp;
		}
		fgets(temp, sizeof(temp), stdin);
		temp[strlen(temp)-1] = 0;
		text = temp;

		for(i = 0; i < n; i++)
		{
			while((pos = text.find(find[i])) != std::string::npos)
			{
				text.replace(pos, find[i].size(), replace[i]);
			}
		}

		printf("%s\n", text.c_str());
	}
	return 0;
}
