#include <stdio.h>

int length, ant_num;

int main()
{
	int i, tc, pos, max, min, tmp;
	scanf("%d", &tc);
	while(tc--)
	{
		scanf("%d%d", &length, &ant_num);
		if(length == 0 || ant_num == 0)
		{
			printf("0 0\n");
			continue;
		}
		scanf("%d", &pos);
		pos > length-pos ? (max = pos, min = length-pos) : (max = length-pos, min = pos);
		for(i = 1; i < ant_num; i++)
		{
			scanf("%d", &pos);
			if(pos > max)
				max = pos;
			else if(length-pos > max)
				max = length-pos;
			tmp = pos > length-pos ? length-pos : pos;
			if(tmp > min)
				min = tmp;
		}
		printf("%d %d\n", min, max);
	}
	return 0;
}