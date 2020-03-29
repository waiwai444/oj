#include <stdio.h>
#include <string.h>
#include <string>
#include <map>

std::map<std::string, std::string> dict;

int main()
{
	char line[30], *word;
	while(fgets(line, sizeof(line), stdin))
	{
		if(line[0] == '\n')
			break;
		line[strlen(line)-1] = 0;
		word = strtok(line, " ");
		dict[std::string(strtok(NULL, " "))] = std::string(word);
	}
	std::string key;
	while(fgets(line, sizeof(line), stdin))
	{
		line[strlen(line)-1] = 0;
		key = line;
		std::map<std::string, std::string>::iterator it;
		if((it = dict.find(key)) != dict.end())
			printf("%s\n", it->second.c_str());
		else
			printf("eh\n");
	}
	return 0;
}
