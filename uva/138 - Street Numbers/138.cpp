#include <stdio.h>

const int tab[10][2] = {
	{6, 8},
	{35, 49},
	{204, 288},
	{1189, 1681},
	{6930, 9800},
	{40391, 57121},
	{235416, 332928},
	{1372105, 1940449},
	{7997214, 11309768},
	{46611179, 65918161}
};

int main()
{
	int i;
	for(i = 0; i < 10; i++)
		printf("%10d%10d\n", tab[i][0], tab[i][1]);
	return 0;
}
