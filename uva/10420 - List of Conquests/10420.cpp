#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>

int main()
{
	int i, j, n;
	char input[85];
	char country[50];
	std::map<std::string, int> counter;
	scanf("%d", &n);
	fgets(input, sizeof(input), stdin);
	for(i = 0; i < n; i++)
	{
		fgets(input, sizeof(input), stdin);
		sscanf(input, "%s", country);
		counter[std::string(country)]++;
	}
	std::map<std::string, int>::const_iterator it;
	for(it = counter.begin(); it != counter.end(); ++it)
		printf("%s %d\n", it->first.c_str(), it->second);
	return 0;
}
