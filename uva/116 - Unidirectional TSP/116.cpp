
#include <stdio.h>

#define MAXROW 10
#define MAXCOL 100

int m, n;

int dptable[MAXROW][MAXCOL];
int dpnext[MAXROW][MAXCOL];

int main()
{
	int i, j, min_id, min_weight, tmp_w, tmp_i;
	while(scanf("%d%d", &m, &n) != EOF)
	{
		for(i = 0; i < m; i++)
		{
			for(j = 0; j < n; j++)
				scanf("%d", &dptable[i][j]);
		}
		if(m == 1)
		{
			min_weight = dptable[0][0];
			printf("1");
			for(j = 1; j < n; j++)
			{
				min_weight += dptable[0][j];
				printf(" 1");
			}
			printf("\n%d\n", min_weight);
		}
		else
		{
			for(j = n - 2; j >= 0; j--)
			{				
				for(i = 0; i < m; i++)
				{
					tmp_i = (i - 1 + m) % m;
					tmp_w = dptable[tmp_i][j + 1];
					if(tmp_w > dptable[i][j + 1] || tmp_w == dptable[i][j + 1] && tmp_i > i)
					{
						tmp_i = i;
						tmp_w = dptable[i][j + 1];
					}
					if(tmp_w > dptable[(i + 1) % m][j + 1] || tmp_w == dptable[(i + 1) % m][j + 1] && tmp_i > (i + 1) % m)
					{
						tmp_i = (i + 1) % m;
						tmp_w = dptable[tmp_i][j + 1];
					}
					dptable[i][j] += tmp_w;
					dpnext[i][j] = tmp_i;
				}
			}
			min_id = 0;
			min_weight = dptable[0][0];
			for(i = 1; i < m; i++)
			{
				if(dptable[i][0] < min_weight)
				{
					min_id = i;
					min_weight = dptable[i][0];
				}
			}
			printf("%d", min_id + 1);
			for(j = 0; j < n - 1; j++)
			{
				min_id = dpnext[min_id][j];
				printf(" %d", min_id + 1);
			}
			printf("\n%d\n", min_weight);
		}
	}
	return 0;
}
