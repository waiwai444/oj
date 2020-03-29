#include <stdio.h>
#include <string.h>

int h, w;
char matrix[55][55];
int dot_num[7];

void dfs_dot(int row, int col)
{
	matrix[row][col] = '*';
	if(matrix[row-1][col] == 'X')
		dfs_dot(row-1, col);
	if(matrix[row][col-1] == 'X')
		dfs_dot(row, col-1);
	if(matrix[row+1][col] == 'X')
		dfs_dot(row+1, col);
	if(matrix[row][col+1] == 'X')
		dfs_dot(row, col+1);
}

void dfs_dice(int row, int col, int *cnt)
{
	if(matrix[row][col] == 'X')
	{
		++*cnt;
		dfs_dot(row, col);
	}
	matrix[row][col] = '.';
	if(matrix[row-1][col] != '.')
		dfs_dice(row-1, col, cnt);
	if(matrix[row][col-1] != '.')
		dfs_dice(row, col-1, cnt);
	if(matrix[row+1][col] != '.')
		dfs_dice(row+1, col, cnt);
	if(matrix[row][col+1] != '.')
		dfs_dice(row, col+1, cnt);
}

int main()
{
	int i, j, tc = 0;
	memset(matrix, '.', sizeof(matrix));
	while(scanf("%d%d", &w, &h), w)
	{
		fgets(&matrix[1][1], sizeof(matrix[1])-1, stdin);
		matrix[1][strlen(&matrix[1][1])] = 0;
		memset(dot_num, 0, sizeof(dot_num));
		for(i = 1; i <= h; i++)
		{
			fgets(&matrix[i][1], sizeof(matrix[i])-1, stdin);
			matrix[i][strlen(&matrix[i][1])] = 0;
			matrix[i][w+1] = '.';
		}
		int cnt;
		for(i = 1; i <= h; i++)
		{
			for(j = 1; j <= w; j++)
			{
				if(matrix[i][j] != '.')
				{
					cnt = 0;
					dfs_dice(i, j, &cnt);
					dot_num[cnt]++;
				}
			}
		}
		printf("Throw %d\n", ++tc);
		bool first = true;
		for(i = 1; i <= 6; i++)
		{
			while(dot_num[i] >= 1)
			{
				dot_num[i]--;
				if(first)
				{
					printf("%d", i);
					first = false;
				}
				else
					printf(" %d", i);
			}
		}
		printf("\n\n");
	}
	return 0;
}
