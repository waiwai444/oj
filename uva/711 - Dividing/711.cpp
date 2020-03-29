#include <stdio.h>
#include <string.h>

int main()
{
	int i, j, k, tc = 0, marble[6], sum, half, cur_max;
	bool dptable[60001];
	while(scanf("%d%d%d%d%d%d", &marble[0], &marble[1], &marble[2], &marble[3], &marble[4], &marble[5]))
	{
		if(marble[0] == 0 && marble[1] == 0 && marble[2] == 0 && marble[3] == 0 && marble[4] == 0 && marble[5] == 0)
			break;
		for(i = 0; i < 6; i++)
			if(marble[i] > 6)
				if((marble[i]&1) == 1)
					marble[i] = 7;
				else
					marble[i] = 6;
		for(sum = 0, i = 0; i < 6; i++)
			sum += marble[i]*(i+1);
		if((sum&1) == 1)
		{
			printf("Collection #%d:\nCan't be divided.\n\n", ++tc);
			continue;
		}
		half = sum/2;
		memset(dptable, false, sizeof(dptable));
		dptable[0] = true;
		cur_max = 0;
		for(i = 0; i < 6; i++)
		{
			if(marble[i] == 0)
				continue;
			for(j = cur_max; j >= 0; j--)
			{
				if(dptable[j] == true)
				{
					for(k = 1; k <= marble[i]; k++)
					{
						int tmp = j+(i+1)*k;
						if(tmp > half)
							break;
						else if(tmp == half)
							goto finished;
						dptable[tmp] = true;
						if(tmp > cur_max)
							cur_max = tmp;
					}
				}
			}
		}
		printf("Collection #%d:\nCan't be divided.\n\n", ++tc);
		continue;
finished:
		printf("Collection #%d:\nCan be divided.\n\n", ++tc);
	}
	return 0;
}
