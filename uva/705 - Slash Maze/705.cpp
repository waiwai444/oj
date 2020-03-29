
#include <stdio.h>
#include <string.h>

#define TL 0
#define TR 1
#define BL 2
#define BR 3

struct Maze
{
	bool s_line[75][74][4];
	bool l_line[74][75][4];
	int w;
	int h;
} maze;

int s_line_visited[75][74];	// 0 for not visited, positive for visited
int l_line_visited[74][75];

void read_layout()
{
	int i, j;
	char slash;
	if(maze.w == 0 || maze.h == 0)
		return;
	// i == 0, j == 0
	scanf("%*c");
	scanf("%c", &slash);
	if(slash == '/')
	{
		maze.s_line[0][0][BL] = true;
		maze.l_line[0][0][TR] = true;
	}
	else
	{
		maze.s_line[0][0][TL] = true;
		maze.l_line[0][0][TL] = true;
	}
	// i == 0, 1 <= j <= w-2
	for(j = 1; j < maze.w - 1; j++)
	{
		scanf("%c", &slash);
		if(slash == '/')
		{
			maze.s_line[0][j - 1][TR] = true;
			maze.s_line[0][j][BL] = true;
			maze.l_line[0][j][TR] = true;
		}
		else
		{
			maze.s_line[0][j - 1][BR] = true;
			maze.s_line[0][j][TL] = true;
			maze.l_line[0][j][TL] = true;
		}
	}
	// i == 0, j == w-1
	if(maze.w > 1)
	{
		scanf("%c", &slash);
		if(slash == '/')
		{
			maze.s_line[0][j - 1][TR] = true;
			maze.l_line[0][j][TR] = true;
		}
		else
		{
			maze.s_line[0][j - 1][BR] = true;
			maze.l_line[0][j][TL] = true;
		}
	}
	// 1 <= i <= h-2
	for(i = 1; i < maze.h - 1; i++)
	{
		// j == 0
		scanf("%*c");
		scanf("%c", &slash);
		if(slash == '/')
		{
			maze.s_line[i][0][BL] = true;
			maze.l_line[i - 1][0][BL] = true;
			maze.l_line[i][0][TR] = true;
		}
		else
		{
			maze.s_line[i][0][TL] = true;
			maze.l_line[i - 1][0][BR] = true;
			maze.l_line[i][0][TL] = true;
		}
		// 1 <= j <= w-2
		for(j = 1; j < maze.w - 1; j++)
		{
			scanf("%c", &slash);
			if(slash == '/')
			{
				maze.s_line[i][j - 1][TR] = true;
				maze.s_line[i][j][BL] = true;
				maze.l_line[i - 1][j][BL] = true;
				maze.l_line[i][j][TR] = true;
			}
			else
			{
				maze.s_line[i][j - 1][BR] = true;
				maze.s_line[i][j][TL] = true;
				maze.l_line[i - 1][j][BR] = true;
				maze.l_line[i][j][TL] = true;
			}
		}
		// j == w-1
		if(maze.w > 1)
		{
			scanf("%c", &slash);
			if(slash == '/')
			{
				maze.s_line[i][j - 1][TR] = true;
				maze.l_line[i - 1][j][BL] = true;
				maze.l_line[i][j][TR] = true;
			}
			else
			{
				maze.s_line[i][j - 1][BR] = true;
				maze.l_line[i - 1][j][BR] = true;
				maze.l_line[i][j][TL] = true;
			}
		}
	}
	// i == h-1, j == 0
	scanf("%*c");
	if(maze.h > 1)
	{
		scanf("%c", &slash);
		if(slash == '/')
		{
			maze.s_line[maze.h - 1][0][BL] = true;
			maze.l_line[maze.h - 2][0][BL] = true;
		}
		else
		{
			maze.s_line[maze.h - 1][0][TL] = true;
			maze.l_line[maze.h - 2][0][BR] = true;
		}
		// i == h-1, 1 <= j <= w-2
		for(j = 1; j < maze.w - 1; j++)
		{
			scanf("%c", &slash);
			if(slash == '/')
			{
				maze.s_line[maze.h - 1][j - 1][TR] = true;
				maze.s_line[maze.h - 1][j][BL] = true;
				maze.l_line[maze.h - 2][j][BL] = true;
			}
			else
			{
				maze.s_line[maze.h - 1][j - 1][BR] = true;
				maze.s_line[maze.h - 1][j][TL] = true;
				maze.l_line[maze.h - 2][j][BR] = true;
			}
		}
		// i == h-1, j == w-1
		if(maze.w > 1)
		{
			scanf("%c", &slash);
			if(slash == '/')
			{
				maze.s_line[maze.h - 1][j - 1][TR] = true;
				maze.l_line[maze.h - 2][j][BL] = true;
			}
			else
			{
				maze.s_line[maze.h - 1][j - 1][BR] = true;
				maze.l_line[maze.h - 2][j][BR] = true;
			}
		}
	}
}

void search()
{
	static int count = 0;
	int i, j;
	int cur_path_id = 0;
	int cur_path_len;
	int ncycles = 0;
	int longest_cycle = 0;
	int tmp_i, tmp_j;
	int prev_step;
	memset(s_line_visited, 0, sizeof(s_line_visited));
	memset(l_line_visited, 0, sizeof(l_line_visited));
	for(i = 0; i < maze.h; i++)
	{
		for(j = 0; j < maze.w - 1; j++)
		{
			if(s_line_visited[i][j] > 0)
				continue;
			++cur_path_id;
			s_line_visited[i][j] = cur_path_id;
			cur_path_len = 1;
			tmp_i = i;
			tmp_j = j;
			prev_step = -1;
			while(true)
			{
				if(maze.s_line[tmp_i][tmp_j][TL] && prev_step != BR)
				{
					if(tmp_i == 0)
						break;
					--tmp_i;
					prev_step = TL;
				}
				else if(maze.s_line[tmp_i][tmp_j][TR] && prev_step != BL)
				{
					if(tmp_i == 0)
						break;
					--tmp_i;
					++tmp_j;
					prev_step = TR;
				}
				else if(maze.s_line[tmp_i][tmp_j][BL] && prev_step != TR)
				{
					if(tmp_i == maze.h - 1)
						break;
					prev_step = BL;
				}
				else if(maze.s_line[tmp_i][tmp_j][BR] && prev_step != TL)
				{
					if(tmp_i == maze.h - 1)
						break;
					++tmp_j;
					prev_step = BR;
				}
				if(l_line_visited[tmp_i][tmp_j] > 0)
				{
					if(l_line_visited[tmp_i][tmp_j] == cur_path_id)
					{
						++ncycles;
						if(cur_path_len > longest_cycle)
							longest_cycle = cur_path_len;
					}
					break;
				}
				l_line_visited[tmp_i][tmp_j] = cur_path_id;
				++cur_path_len;
				if(maze.l_line[tmp_i][tmp_j][TL] && prev_step != BR)
				{
					if(tmp_j == 0)
						break;
					--tmp_j;
					prev_step = TL;
				}
				else if(maze.l_line[tmp_i][tmp_j][TR] && prev_step != BL)
				{
					if(tmp_j == maze.w - 1)
						break;
					prev_step = TR;
				}
				else if(maze.l_line[tmp_i][tmp_j][BL] && prev_step != TR)
				{
					if(tmp_j == 0)
						break;
					++tmp_i;
					--tmp_j;
					prev_step = BL;
				}
				else if(maze.l_line[tmp_i][tmp_j][BR] && prev_step != TL)
				{
					if(tmp_j == maze.w - 1)
						break;
					++tmp_i;
					prev_step = BR;
				}
				if(s_line_visited[tmp_i][tmp_j] > 0)
				{
					if(s_line_visited[tmp_i][tmp_j] == cur_path_id)
					{
						++ncycles;
						if(cur_path_len > longest_cycle)
							longest_cycle = cur_path_len;
					}
					break;
				}
				s_line_visited[tmp_i][tmp_j] = cur_path_id;
				++cur_path_len;
			}
		}
	}
	if(ncycles > 0)
		printf("Maze #%d:\n%d Cycles; the longest has length %d.\n", ++count, ncycles, longest_cycle);
	else
		printf("Maze #%d:\nThere are no cycles.\n", ++count);
	printf("\n");
}

int main()
{
	while(scanf("%d%d", &maze.w, &maze.h))
	{
		if(maze.w == 0 && maze.h == 0)
			break;
		memset(maze.s_line, false, sizeof(maze.s_line));
		memset(maze.l_line, false, sizeof(maze.l_line));
		read_layout();
		search();
	}
	return 0;
}
