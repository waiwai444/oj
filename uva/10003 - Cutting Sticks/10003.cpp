
#include <stdio.h>

#define MAX_CUTTING 50

int dptable[MAX_CUTTING + 2][MAX_CUTTING + 2];	// upper triangular matrix

int main()
{
	int i, j, k, stick_len, cut_times, tmp;
	int cut_pos[MAX_CUTTING + 1];
	while(scanf("%d", &stick_len))
	{
		if(stick_len == 0)
			break;
		
		scanf("%d", &cut_times);
		cut_pos[0] = 0;
		for(i = 1; i <= cut_times; i++)
			scanf("%d", &cut_pos[i]);
		cut_pos[cut_times + 1] = stick_len;
		
		for(i = 0; i < cut_times; i++)
		{
			dptable[i][i + 1] = 0;
			dptable[i][i + 2] = cut_pos[i + 2] - cut_pos[i];
		}
		dptable[cut_times][cut_times + 1] = 0;
		
		for(i = 3; i <= cut_times + 1; i++)
		{
			for(j = 0; j <= cut_times + 1 - i; j++)
			{
				dptable[j][j + i] = dptable[j][j + 1] + dptable[j + 1][j + i];
				for(k = j + 2; k < j + i; k++)
				{
					tmp = dptable[j][k] + dptable[k][j + i];
					if(dptable[j][j + i] > tmp)
						dptable[j][j + i] = tmp;
				}
				dptable[j][j + i] += cut_pos[j + i] - cut_pos[j];
			}
		}
		
		printf("The minimum cutting is %d.\n", dptable[0][cut_times + 1]);
	}
	return 0;
}
