#include <stdio.h>
#include <string.h>

int l, r, c;
char dungeon[32][32][32];

struct move_pos
{
	int lvl, row, col;
	int step;
};

const int step[6][3] = {{0, 0, -1}, {0, 0, 1}, {0, -1, 0}, {0, 1, 0}, {-1, 0, 0}, {1, 0, 0}};
move_pos queue[27000];
int front, back;

int bfs(move_pos start)
{
	int i;
	move_pos cur, next;
	front = back = 0;
	queue[back++] = start;
	dungeon[start.lvl][start.row][start.col] = '#';
	while(front != back)
	{
		cur = queue[front++];
		for(i = 0; i < 6; i++)
		{
			next.lvl = cur.lvl+step[i][0];
			next.row = cur.row+step[i][1];
			next.col = cur.col+step[i][2];
			char &tmp = dungeon[next.lvl][next.row][next.col];
			if(tmp == '#')
				continue;
			next.step = cur.step+1;
			if(tmp == 'E')
				return next.step;
			queue[back++] = next;
			tmp = '#';
		}
	}
	return -1;
}

int main()
{
	int i, j, k, result;
	move_pos start;
	memset(dungeon, '#', sizeof(dungeon));
	while(scanf("%d%d%d", &l, &r, &c), l)
	{
		for(i = 1; i <= l; i++)
		{
			for(j = 1; j <= r; j++)
			{
				scanf("%s", &dungeon[i][j][1]);
				dungeon[i][j][c+1] = '#';
				for(k = 1; k <= c; k++)
				{
					if(dungeon[i][j][k] == 'S')
					{
						start.lvl = i;
						start.row = j;
						start.col = k;
						start.step = 0;
					}
				}
			}
		}
		result = bfs(start);
		if(result > 0)
			printf("Escaped in %d minute(s).\n", result);
		else
			printf("Trapped!\n");
	}
	return 0;
}