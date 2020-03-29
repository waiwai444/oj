#include <stdio.h>
#include <string.h>

struct coord
{
	int col, row;
};

struct board_square
{
	int adj_num;
	coord pos[8];
};

board_square chess_board[8][8];

void init()
{
	int i, j, k, n;
	const int move[8][2] = {{-1, -2}, {1, -2}, {2, -1}, {2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}};
	for(i = 0; i < 8; i++)
	{
		for(j = 0; j < 8; j++)
		{
			n = 0;
			for(k = 0; k < 8; k++)
			{
				int ti = i+move[k][0], tj = j+move[k][1];
				if(ti >= 0 && ti < 8 && tj >= 0 && tj < 8)
				{
					chess_board[i][j].pos[n].col = ti;
					chess_board[i][j].pos[n].row = tj;
					n++;
				}
			}
			chess_board[i][j].adj_num = n;
		}
	}
}

int find_shortest_path(coord start, coord end)
{
	int i;
	if(start.col == end.col && start.row == end.row)
		return 0;
	coord queue[64], cur_pos, next_pos;
	int front, back;
	front = back = 0;
	int step[64], cur_step;
	int step_front, step_back;
	step_front = step_back = 0;
	bool visited[8][8];
	memset(visited, false, sizeof(visited));
	queue[back++] = start;
	step[step_back++] = 0;
	visited[start.col][start.row] = true;
	while(front != back)
	{
		cur_pos = queue[front++];
		cur_step = step[step_front++];
		for(i = 0; i < chess_board[cur_pos.col][cur_pos.row].adj_num; i++)
		{
			next_pos = chess_board[cur_pos.col][cur_pos.row].pos[i];
			if(next_pos.col == end.col && next_pos.row == end.row)
				return cur_step+1;
			if(!visited[next_pos.col][next_pos.row])
			{
				visited[next_pos.col][next_pos.row] = true;
				queue[back++] = next_pos;
				step[step_back++] = cur_step+1;
			}
		}
	}
	return -1;
}

int main()
{
	coord start, end;
	char start_str[3], end_str[3];
	init();
	while(scanf("%s%s", start_str, end_str) != EOF)
	{
		start.col = start_str[0]-'a';
		start.row = start_str[1]-'1';
		end.col = end_str[0]-'a';
		end.row = end_str[1]-'1';
		printf("To get from %s to %s takes %d knight moves.\n", start_str, end_str, find_shortest_path(start, end));
	}
	return 0;
}