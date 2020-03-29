#include <stdio.h>
#include <string>

int main()
{
	int i;
	char input[16];
	std::string output;
	char ascii;
	fgets(input, sizeof(input), stdin);
	i = 0;
	while(fgets(input, sizeof(input), stdin))
	{
		if(input[0] == '_')
			break;
		ascii = 0;
		if(input[2] == 'o')
			ascii += 64;
		if(input[3] == 'o')
			ascii += 32;
		if(input[4] == 'o')
			ascii += 16;
		if(input[5] == 'o')
			ascii += 8;
		if(input[7] == 'o')
			ascii += 4;
		if(input[8] == 'o')
			ascii += 2;
		if(input[9] == 'o')
			ascii += 1;
		output.append(1, ascii);
	}
	printf("%s", output.c_str());
	return 0;
}
