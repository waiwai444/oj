#include <stdio.h>
#include <string.h>

struct Coord
{
	int r, c;
};

int size[12] = {11, 9, 9, 11, 11, 9, 9, 11, 11, 9, 9, 11};
Coord line[12][11] = {{{5, 0}, {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {5, 7}, {5, 8}, {5, 9}, {5, 10}},
			{{4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7}, {4, 8}, {4, 9}},
			{{3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}, {3, 8}, {3, 9}},
			{{2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {2, 8}, {2, 9}, {2, 10}},
			{{2, 0}, {2, 1}, {3, 1}, {3, 2}, {4, 2}, {4, 3}, {5, 3}, {5, 4}, {6, 4}, {6, 5}, {7, 5}},
			{{2, 2}, {2, 3}, {3, 3}, {3, 4}, {4, 4}, {4, 5}, {5, 5}, {5, 6}, {6, 6}},
			{{1, 4}, {2, 4}, {2, 5}, {3, 5}, {3, 6}, {4, 6}, {4, 7}, {5, 7}, {5, 8}},
			{{0, 5}, {1, 5}, {1, 6}, {2, 6}, {2, 7}, {3, 7}, {3, 8}, {4, 8}, {4, 9}, {5, 9}, {5, 10}},
			{{0, 5}, {1, 5}, {1, 4}, {2, 4}, {2, 3}, {3, 3}, {3, 2}, {4, 2}, {4, 1}, {5, 1}, {5, 0}},
			{{1, 6}, {2, 6}, {2, 5}, {3, 5}, {3, 4}, {4, 4}, {4, 3}, {5, 3}, {5, 2}},
			{{2, 8}, {2, 7}, {3, 7}, {3, 6}, {4, 6}, {4, 5}, {5, 5}, {5, 4}, {6, 4}},
			{{2, 10}, {2, 9}, {3, 9}, {3, 8}, {4, 8}, {4, 7}, {5, 7}, {5, 6}, {6, 6}, {6, 5}, {7, 5}}};

struct Cell
{
	int nlines;
	char line[3];
};

Cell cell_info[8][11];

int main()
{
	int i, j, k, min, max;
	int largest[12];
	unsigned int max_value[8][11];
	bool flag[12];
	bool feasible;
	while(scanf("%d", &largest[0]) != EOF)
	{
		memset(max_value, -1, sizeof(max_value));
		memset(cell_info, 0, sizeof(cell_info));
		min = largest[0];
		for(i = 1; i < 12; i++)
		{
			scanf("%d", &largest[i]);
			min += largest[i];
		}
		for(i = 0; i < 12; i++)
		{
			for(j = 0; j < size[i]; j++)
			{
				cell_info[line[i][j].r][line[i][j].c].line[cell_info[line[i][j].r][line[i][j].c].nlines++] = i;
				if(max_value[line[i][j].r][line[i][j].c] > largest[i])
					max_value[line[i][j].r][line[i][j].c] = largest[i];
			}
		}
		
		for(i = 0; i < 12; i++)
		{
			feasible = false;
			for(j = 0; j < size[i]; j++)
				if(max_value[line[i][j].r][line[i][j].c] == largest[i])
				{
					feasible = true;
					break;
				}
			if(!feasible)
				break;
		}
		if(!feasible)
		{
			printf("NO SOLUTION\n");
			continue;
		}
		
		memset(flag, false, sizeof(flag));
		for(i = 5; i >= 2; i--)
		{
			for(j = i == 5 || i == 2 ? 3 : 2, k = 10 - j; j <= k; j++)
			{
				int l1 = cell_info[i][j].line[0];
				int l2 = cell_info[i][j].line[1];
				int l3 = cell_info[i][j].line[2];
				if(!flag[l1] && !flag[l2] && !flag[l3] && largest[l1] == largest[l2] && largest[l1] == largest[l3])
				{
					min -= 2 * largest[l1];
					flag[l1] = flag[l2] = flag[l3] = true;
					break;
				}
			}
		}
		for(i = 0; i < 12; i++)
		{
			if(flag[i])
				continue;
			for(j = 0; j < size[i]; j++)
			{
				if(max_value[line[i][j].r][line[i][j].c] < largest[i])
					continue;
				Cell& cell = cell_info[line[i][j].r][line[i][j].c];
				for(k = 0; k < cell.nlines; k++)
				{
					if(cell.line[k] != i && !flag[cell.line[k]] && largest[cell.line[k]] == largest[i])
					{
						min -= largest[i];
						flag[cell.line[k]] = true;
						goto next;
					}
				}
			}
			next:
			flag[i] = true;
		}
		
		max = 0;
		for(i = 0; i < 8; i++)
			for(j = 0; j < 11; j++)
				if(max_value[i][j] != (unsigned int)-1)
					max += max_value[i][j];
		printf("%d %d\n", min, max);
	}
	return 0;
}
