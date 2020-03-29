#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	int i, l;
	char line[1024];
	char map[127];
	map[' '] = ' ';
	map['1'] = '`';
	for(i=2; i<=9; i++)
		map['0'+i] = '0'+i-1;
	map['0'] = '9';
	map['-'] = '0';
	map['='] = '-';
	map['W'] = 'Q';
	map['E'] = 'W';
	map['R'] = 'E';
	map['T'] = 'R';
	map['Y'] = 'T';
	map['U'] = 'Y';
	map['I'] = 'U';
	map['O'] = 'I';
	map['P'] = 'O';
	map['['] = 'P';
	map[']'] = '[';
	map['\\'] = ']';
	map['S'] = 'A';
	map['D'] = 'S';
	map['F'] = 'D';
	map['G'] = 'F';
	map['H'] = 'G';
	map['J'] = 'H';
	map['K'] = 'J';
	map['L'] = 'K';
	map[';'] = 'L';
	map['\''] = ';';
	map['X'] = 'Z';
	map['C'] = 'X';
	map['V'] = 'C';
	map['B'] = 'V';
	map['N'] = 'B';
	map['M'] = 'N';
	map[','] = 'M';
	map['.'] = ',';
	map['/'] = '.';
	while(cin.getline(line, 1024))
	{
		l = strlen(line);
		for(i=0; i<l; i++)
		{
			cout<<map[line[i]];
		}
		cout<<endl;
	}
	return 0;
}