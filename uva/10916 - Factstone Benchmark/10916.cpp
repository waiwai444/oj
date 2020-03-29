#include <stdio.h>
#include <math.h>

int rec[21] = { 3, 5, 8, 12, 20, 34, 57, 98, 170, 300, 536, 966, 1754, 3210, 5910, 10944, 20366, 38064, 71421, 134480, 254016 };

int main()
{
	int y;
	while(scanf("%d", &y), y)
		printf("%d\n", rec[(y-1960)/10]);
	return 0;
}