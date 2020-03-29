#include <stdio.h>
#include <string.h>

int m, n;
char rect[100][105];

void dfs(int row, int col)
{
	rect[row][col] = '*';
	if(row > 0)
	{
		if(rect[row-1][col] == '@')
			dfs(row-1, col);
		else
		{
			if(col > 0 && rect[row-1][col-1] == '@')
				dfs(row-1, col-1);
			if(col < n-1 && rect[row-1][col+1] == '@')
				dfs(row-1, col+1);
		}
	}
	if(row < m-1)
	{
		if(rect[row+1][col] == '@')
			dfs(row+1, col);
		else
		{
			if(col > 0 && rect[row+1][col-1] == '@')
				dfs(row+1, col-1);
			if(col < n-1 && rect[row+1][col+1] == '@')
				dfs(row+1, col+1);
		}
	}
	if(col > 0 && rect[row][col-1] == '@')
		dfs(row, col-1);
	if(col < n-1 && rect[row][col+1] == '@')
		dfs(row, col+1);
}

int main()
{
	int i, j, count;
	while(scanf("%d%d", &m, &n), m)
	{
		fgets(rect[0], sizeof(rect[0]), stdin);
		rect[0][strlen(rect[0])-1] = 0;
		for(i = 0; i < m; i++)
		{
			fgets(rect[i], sizeof(rect[i]), stdin);
			rect[i][strlen(rect[i])-1] = 0;
		}
		count = 0;
		for(i = 0; i < m; i++)
		{
			for(j = 0; j < n; j++)
			{
				if(rect[i][j] == '@')
				{
					count++;
					dfs(i, j);
				}
			}
		}
		printf("%d\n", count);
	}
	return 0;
}
