#include <stdio.h>
#include <string.h>

int table[10000];

int main()
{
	int z, i, m, l, l0, tc = 0, count;
	while(scanf("%d%d%d%d", &z, &i, &m, &l), m != 0)
	{
		memset(table, 0, sizeof(table));
		l0 = l;
		table[l0] = count;
		while(table[l = (z*l+i)%m] == 0)
			table[l] = ++count;
		printf("Case %d: %d\n", ++tc, count-table[l]+1);
	}
	return 0;
}
