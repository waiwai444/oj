#include <stdio.h>
#include <string.h>

// the index of direction: 0 for top left to bottom right, 1 for top to bottom, 2 for the third

struct Cell
{
	int num[3];
	bool filled[3];
} cells[19];	// indexed from top to bottom and from left to right

const int cell_num_in_row[5] = {3, 4, 5, 4, 3};
const int cell_idx_in_row[3][5][5] = {
	{{2, 6, 11}, {1, 5, 10, 15}, {0, 4, 9, 14, 18}, {3, 8, 13, 17}, {7, 12, 16}},
	{{0, 1, 2}, {3, 4, 5, 6}, {7, 8, 9, 10, 11}, {12, 13, 14, 15}, {16, 17, 18}},
	{{7, 3, 0}, {12, 8, 4, 1}, {16, 13, 9, 5, 2}, {17, 14, 10, 6}, {18, 15, 11}}
};
const int row_idx_for_cell[19][3] = {
	{2, 0, 0}, {1, 0, 1}, {0, 0, 2},
	{3, 1, 0}, {2, 1, 1}, {1, 1, 2}, {0, 1, 3},
	{4, 2, 0}, {3, 2, 1}, {2, 2, 2}, {1, 2, 3}, {0, 2, 4},
	{4, 3, 1}, {3, 3, 2}, {2, 3, 3}, {1, 3, 4},
	{4, 4, 2}, {3, 4, 3}, {2, 4, 4}
};

int candidate_layout_num;
int candidate_layout[1500][3][5];

bool piece_used[27];	// only numbers 0, 1, and 2

inline bool use_piece(int num[])
{
	int p = 9*num[0]+3*num[1]+num[2];
	if(piece_used[p])
		return false;
	return piece_used[p] = true;
}

inline void unuse_piece(int num[])
{
	piece_used[9*num[0]+3*num[1]+num[2]] = false;
}

void pre_arrange(int cell_idx, int dir, int num)
{
	int row_idx = row_idx_for_cell[cell_idx][dir];
	int cell_num = cell_num_in_row[row_idx];
	const int *cell_idx_list = cell_idx_in_row[dir][row_idx];
	for(int i = 0; i < cell_num; i++)
	{
		if(cell_idx_list[i] != cell_idx)
		{
			Cell& cell = cells[cell_idx_list[i]];
			cell.num[dir] = num;
			cell.filled[dir] = true;
		}
	}
}

void un_pre_arrange(int cell_idx, int dir)
{
	int row_idx = row_idx_for_cell[cell_idx][dir];
	int cell_num = cell_num_in_row[row_idx];
	const int *cell_idx_list = cell_idx_in_row[dir][row_idx];
	for(int i = 0; i < cell_num; i++)
	{
		if(cell_idx_list[i] != cell_idx)
		{
			cells[cell_idx_list[i]].filled[dir] = false;
		}
	}
}

void store_layout()
{
	int *pl = candidate_layout[candidate_layout_num][0];
	pl[0] = cells[2].num[0];
	pl[1] = cells[1].num[0];
	pl[2] = cells[0].num[0];
	pl[3] = cells[3].num[0];
	pl[4] = cells[7].num[0];
	pl = candidate_layout[candidate_layout_num][1];
	pl[0] = cells[0].num[1];
	pl[1] = cells[3].num[1];
	pl[2] = cells[7].num[1];
	pl[3] = cells[12].num[1];
	pl[4] = cells[16].num[1];
	pl = candidate_layout[candidate_layout_num][2];
	pl[0] = cells[0].num[2];
	pl[1] = cells[1].num[2];
	pl[2] = cells[2].num[2];
	pl[3] = cells[6].num[2];
	pl[4] = cells[11].num[2];
	candidate_layout_num++;
}

void backtrack(int cell_idx, int dir)
{
	if(cell_idx == 19)
	{
		store_layout();
		return;
	}
	
	Cell& cur_cell = cells[cell_idx];
	if(cur_cell.filled[dir])
	{
		if(dir < 2)
			backtrack(cell_idx, dir+1);
		else
		{
			if(!use_piece(cur_cell.num))
				return;
			backtrack(cell_idx+1, 0);
			unuse_piece(cur_cell.num);
		}
	}
	else
	{
		cur_cell.filled[dir] = true;
		for(int i = 0; i < 3; i++)
		{
			cur_cell.num[dir] = i;
			if(dir == 2 && !use_piece(cur_cell.num))
				continue;
			pre_arrange(cell_idx, dir, i);
			
			if(dir < 2)
				backtrack(cell_idx, dir+1);
			else
				backtrack(cell_idx+1, 0);
			
			un_pre_arrange(cell_idx, dir);
			if(dir == 2)
				unuse_piece(cur_cell.num);
		}
		cur_cell.filled[dir] = false;
	}
}

int main()
{
	int i, j, tc, max_score, score;
	int numbers[3][3];
    
	backtrack(0, 0);
	
	scanf("%d", &tc);
	for(int c = 1; c <= tc; c++)
	{
		for(i = 0; i < 3; i++)
			scanf("%d%d%d", &numbers[i][0], &numbers[i][1], &numbers[i][2]);
		
		max_score = -1000;
		for(i = 0; i < candidate_layout_num; i++)
		{
			score = 0;
			for(j = 0; j < 5; j++)
			{
				score += cell_num_in_row[j]*(numbers[0][candidate_layout[i][0][j]]+numbers[1][candidate_layout[i][1][j]]+numbers[2][candidate_layout[i][2][j]]);
			}
			if(score > max_score)
				max_score = score;
		}
		
		printf("Test #%d\n%d\n\n", c, max_score);
	}
	return 0;
}