#include <stdio.h>
#include <string.h>
#include <algorithm>

#define FLAT 0
#define JUT 1
#define CAVITY 2

#define TOP 0
#define RIGHT 1
#define BOTTOM 2
#define LEFT 3

struct Piece
{
	unsigned char shape[4];
	unsigned char code;	// (MSD) LLBBRRTT (LSD)
};

int nrows, ncols, npieces;
Piece piece_set[36];
bool used[36];
int board[6][6];

bool compare_piece(const Piece &piece1, const Piece &piece2)
{
	return piece1.code < piece2.code;
}

void add_piece(int idx, char str[])
{
	Piece piece;
	piece.code = 0;
	for(int i = TOP; i <= LEFT; i++)
	{
		if(str[i] == 'F')
			piece.code += (piece.shape[i] = FLAT)<<i*2;
		else if(str[i] == 'O')
			piece.code += (piece.shape[i] = JUT)<<i*2;
		else
			piece.code += (piece.shape[i] = CAVITY)<<i*2;
	}
	piece_set[idx] = piece;
}

bool valid_place(int cur_row, int cur_col, const Piece& piece)
{
	if(cur_row == 0 && piece.shape[TOP] != FLAT)
		return false;
	if(cur_row == nrows-1 && piece.shape[BOTTOM] != FLAT)
		return false;
	if(cur_row < nrows-1 && piece.shape[BOTTOM] == FLAT)
		return false;
	if(cur_row > 0 && piece.shape[TOP] == FLAT)
		return false;
	if(cur_col == 0 && piece.shape[LEFT] != FLAT)
		return false;
	if(cur_col == ncols-1 && piece.shape[RIGHT] != FLAT)
		return false;
	if(cur_col < ncols-1 && piece.shape[RIGHT] == FLAT)
		return false;
	if(cur_col > 0 && piece.shape[LEFT] == FLAT)
		return false;
	
	if(cur_row > 0)
	{
		int upper_piece_idx = board[cur_row-1][cur_col];
		if(piece_set[upper_piece_idx].shape[BOTTOM] == piece.shape[TOP])
			return false;
	}
	if(cur_col > 0)
	{
		int left_piece_idx = board[cur_row][cur_col-1];
		if(piece_set[left_piece_idx].shape[RIGHT] == piece.shape[LEFT])
			return false;
	}
	return true;
}

bool backtrack(int cur_row, int cur_col)
{
	int next_row, next_col;
	for(int i = 0; i < npieces; i++)
	{
		if(!used[i] && (i == 0 || piece_set[i].code != piece_set[i-1].code || used[i-1]) && valid_place(cur_row, cur_col, piece_set[i]))
		{
			board[cur_row][cur_col] = i;
			used[i] = true;
			
			next_row = cur_row;
			next_col = cur_col+1;
			if(next_col >= ncols)
			{
				next_row++;
				next_col = 0;
			}
			if(next_row >= nrows)
			{
				return true;
			}
			else
			{
				if(backtrack(next_row, next_col))
					return true;
			}
			
			used[i] = false;
		}
	}
	return false;
}

int main()
{
	int i;
	char input[5];
	while(scanf("%d%d", &nrows, &ncols), nrows)
	{
		npieces = nrows*ncols;
		for(i = 0; i < npieces; i++)
		{
			scanf("%s", input);
			add_piece(i, input);
		}
		memset(used, false, sizeof(used));
		memset(board, -1, sizeof(board));
		std::sort(&piece_set[0], &piece_set[npieces], compare_piece);
		printf("%s\n", backtrack(0, 0) ? "YES" : "NO");
	}
	return 0;
}