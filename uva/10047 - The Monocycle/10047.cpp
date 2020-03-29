#include <stdio.h>
#include <string.h>
#include <deque>

#define INF 0x3f3f3f3f
#define GREEN 0
#define BLACK 1
#define RED 2
#define BLUE 3
#define WHITE 4
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

char table[25][25];
int mtime[25][25][5][4];
int m, n;

struct Status
{
	int row, col, color, dir;
};

inline int get_time(const Status& stat)
{
	return mtime[stat.row][stat.col][stat.color][stat.dir];
}

inline void set_time(const Status& stat, int t)
{
	mtime[stat.row][stat.col][stat.color][stat.dir] = t;
}

inline void output(int test_case, int t)
{
	if(t < INF)
		printf("Case #%d\nminimum time = %d sec\n", test_case, t);
	else
		printf("Case #%d\ndestination not reachable\n", test_case);
}

int main()
{
	int i, j, test_case, time1, time2;
	int si, sj, ti, tj;
	char line[32];
	bool movable, reached;
	std::deque<Status> queue;
	test_case = 0;
	while(scanf("%d%d", &m, &n) && m)
	{
		test_case++;
		if(test_case > 1)
			printf("\n");
		fgets(line, 32, stdin);
		memset(mtime, INF, sizeof(mtime));
		queue.clear();
		si = sj = ti = tj = -1;
		for(i = 0; i < m; i++)
		{
			fgets(line, 32, stdin);
			for(j = 0; j < n; j++)
			{
				sscanf(line + j, "%c", &table[i][j]);
				if(table[i][j] == 'S')
				{
					si = i;
					sj = j;
				}
				else if(table[i][j] == 'T')
				{
					ti = i;
					tj = j;
				}
			}			
		}
		if(m == 1 && n == 1 || si == -1 || ti == -1)
		{
			output(test_case, INF);
			continue;
		}
		reached = false;
		Status stat = {si, sj, GREEN, NORTH};
		set_time(stat, 0);
		queue.push_back(stat);
		while(!queue.empty())
		{
			stat = queue.front();
			queue.pop_front();
			time1 = get_time(stat);
			// turn right
			Status new_stat = stat;
			new_stat.dir = (stat.dir + 1) % 4;
			time2 = get_time(new_stat);
			if(time1 + 1 < time2)
			{
				set_time(new_stat, time1 + 1);
				queue.push_back(new_stat);
			}
			// turn left
			new_stat = stat;
			new_stat.dir = (stat.dir + 3) % 4;
			time2 = get_time(new_stat);
			if(time1 + 1 < time2)
			{
				set_time(new_stat, time1 + 1);
				queue.push_back(new_stat);
			}
			// move forward
			movable = false;
			new_stat = stat;
			if(stat.dir == NORTH && stat.row > 0 && table[stat.row - 1][stat.col] != '#')
			{
				new_stat.row--;
				movable = true;
			}
			else if(stat.dir == EAST && stat.col < n - 1 && table[stat.row][stat.col + 1] != '#')
			{
				new_stat.col++;
				movable = true;
			}
			else if(stat.dir == SOUTH && stat.row < m - 1 && table[stat.row + 1][stat.col] != '#')
			{
				new_stat.row++;
				movable = true;
			}
			else if(stat.dir == WEST && stat.col > 0 && table[stat.row][stat.col - 1] != '#')
			{
				new_stat.col--;
				movable = true;
			}
			if(!movable)
				continue;
			new_stat.color = (stat.color + 1) % 5;
			time2 = get_time(new_stat);
			if(time1 + 1 < time2)
			{
				if(new_stat.row == ti && new_stat.col == tj && new_stat.color == GREEN)
				{
					output(test_case, time1 + 1);
					reached = true;
					break;
				}
				set_time(new_stat, time1 + 1);
				queue.push_back(new_stat);
			}
		}
		if(!reached)
			output(test_case, INF);
	}
	return 0;
}
