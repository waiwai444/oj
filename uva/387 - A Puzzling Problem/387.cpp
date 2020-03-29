#include <stdio.h>
#include <string.h>
#include <vector>

unsigned short square;

struct OriginalPiece
{
	char shape[4][4];
	int nrows, ncols;
};

struct PieceLayout
{
	unsigned short shape;
	int pos_row, pos_col;
};

int piece_num;
OriginalPiece piece_set[16];
std::vector<PieceLayout> layout_set[16];

int result[4][4];
int piece_pos_idx[16];

void translate_all()
{
	int nrows, ncols;
	PieceLayout layout;
	for(int i = 0; i < piece_num; i++)
	{
		nrows = piece_set[i].nrows;
		ncols = piece_set[i].ncols;
		for(int j = 0; j <= 4-nrows; j++)
		{
			for(int k = 0; k <= 4-ncols; k++)
			{
				if(j == 0 && k == 0)
					continue;
				layout.pos_row = j;
				layout.pos_col = k;
				layout.shape = layout_set[i][0].shape;
				layout.shape >>= 4*j;
				layout.shape >>= k;
				layout_set[i].push_back(layout);
			}
		}
	}
}

bool init()
{
	int i, j, k, total_area = 0;
	char input[5];
	unsigned short shape, flag;
	PieceLayout layout;
	square = 0;
	memset(piece_set, 0, sizeof(piece_set));
	for(i = 0; i < piece_num; i++)
	{
		scanf("%d%d", &piece_set[i].nrows, &piece_set[i].ncols);
		shape = 0;
		for(j = 0; j < piece_set[i].nrows; j++)
		{
			scanf("%s", input);
			memcpy(piece_set[i].shape[j], input, piece_set[i].ncols);
			
			flag = 8;
			shape <<= 4;
			for(k = 0; k < piece_set[i].ncols; k++)
			{
				if(input[k] == '1')
				{
					shape |= flag>>k;
					total_area++;
				}
			}
		}
		for(; j < 4; j++)
			shape <<= 4;
		layout_set[i].clear();
		layout.shape = shape;
		layout.pos_row = layout.pos_col = 0;
		layout_set[i].push_back(layout);
	}
	if(total_area != 16)
		return false;
	translate_all();
	return true;
}

void output_result()
{
	int pos_row, pos_col;
	for(int i = 0; i < piece_num; i++)
	{
		PieceLayout& layout = layout_set[i][piece_pos_idx[i]];
		pos_row = layout.pos_row;
		pos_col = layout.pos_col;
		for(int j = pos_row; j < pos_row+piece_set[i].nrows; j++)
		{
			for(int k = pos_col; k < pos_col+piece_set[i].ncols; k++)
			{
				if(piece_set[i].shape[j-pos_row][k-pos_col] == '1')
					result[j][k] = i+1;
			}
		}
	}
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			printf("%d", result[i][j]);
		}
		printf("\n");
	}
}

bool backtrack(int cur_piece)
{
	if(cur_piece == piece_num)
	{
		output_result();
		return true;
	}
	
	std::vector<PieceLayout>& ps = layout_set[cur_piece];
	for(int i = 0; i < ps.size(); i++)
	{
		if((square & ps[i].shape) == 0)
		{
			square |= ps[i].shape;
			piece_pos_idx[cur_piece] = i;
			if(backtrack(cur_piece+1))
				return true;
			square &= ~ps[i].shape;
		}
	}
	return false;
}

int main()
{
	bool first = true;
	while(scanf("%d", &piece_num), piece_num)
	{
		if(!first)
			printf("\n");
		else
			first = false;
		
		if(!init() || !backtrack(0))
			printf("No solution possible\n");
	}
	return 0;
}