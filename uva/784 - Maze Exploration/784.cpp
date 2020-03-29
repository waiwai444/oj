#include <stdio.h>
#include <string.h>

char maze[31][85];
int line_num;

void dfs(int srow, int scol)
{
	maze[srow-1][scol-1] = '#';
	maze[srow-1][scol] = '#';
	maze[srow-1][scol+1] = '#';
	maze[srow][scol-1] = '#';
	maze[srow][scol] = '#';
	maze[srow][scol+1] = '#';
	maze[srow+1][scol-1] = '#';
	maze[srow+1][scol] = '#';
	maze[srow+1][scol+1] = '#';
	if(maze[srow][scol-2] == ' ')
	{
		maze[srow][scol-2] = '#';
		dfs(srow, scol-4);
	}
	if(maze[srow][scol+2] == ' ')
	{
		maze[srow][scol+2] = '#';
		dfs(srow, scol+4);
	}
	if(maze[srow-2][scol] == ' ')
	{
		maze[srow-2][scol] = '#';
		dfs(srow-4, scol);
	}
	if(maze[srow+2][scol] == ' ')
	{
		maze[srow+2][scol] = '#';
		dfs(srow+4, scol);
	}
}

int main()
{
	int i, j, tc, srow, scol;
	scanf("%d", &tc);
	fgets(maze[0], sizeof(maze[0]), stdin);
	maze[0][strlen(maze[0])-1] = 0;
	while(tc--)
	{
		line_num = 0;
		while(fgets(maze[line_num], sizeof(maze[line_num]), stdin))
		{
			maze[line_num][strlen(maze[line_num])-1] = 0;
			if(maze[line_num][0] == '_')
				break;
			line_num++;
		}
		for(i = 0; i < line_num; i++)
		{
			for(j = 0; maze[i][j] != '\0'; j++)
				if(maze[i][j] == '*')
				{
					srow = i;
					scol = j;
					break;
				}
			if(maze[i][j] != '\0')
				break;
		}
		srow = srow/4*4+2;
		scol = scol/4*4+2;
		dfs(srow, scol);
		for(i = 0; i <= line_num; i++)
			printf("%s\n", maze[i]);
	}
	return 0;
}
