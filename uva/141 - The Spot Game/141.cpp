#include <stdio.h>
#include <string.h>
#include <vector>

int size;

struct Board
{
	bool sq[50][50];
};

std::vector<Board> table[100];

bool board_equal(const Board &b1, const Board &b2)
{
	int i, j;
	bool eq = true;
	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++)
			if(b1.sq[i][j] != b2.sq[i][j])
				eq = false;
	if(eq)
		return true;
	eq = true;
	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++)
			if(b1.sq[i][j] != b2.sq[j][size-i-1])
				eq = false;
	if(eq)
		return true;
	eq = true;
	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++)
			if(b1.sq[i][j] != b2.sq[size-i-1][size-j-1])
				eq = false;
	if(eq)
		return true;
	eq = true;
	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++)
			if(b1.sq[i][j] != b2.sq[size-j-1][i])
				eq = false;
	return eq;
}

int main()
{
	int i, j, r, c, s;
	char op[2];
	bool over;
	Board board;
	while(scanf("%d", &size), size)
	{
		s = 0;
		over = false;
		memset(board.sq, false, sizeof(board.sq));
		for(i = 0; i < 100; i++)
			table[i].clear();
		for(i = 1; i <= 2*size; i++)
		{
			scanf("%d%d%s", &r, &c, op);
			if(over)
				continue;
			if(op[0] == '+')
			{
				board.sq[r-1][c-1] = true;
				s++;
			}
			else
			{
				board.sq[r-1][c-1] = false;
				s--;
			}
			for(j = 0; j < table[s].size(); j++)
				if(board_equal(board, table[s][j]))
					break;
			if(j < table[s].size())
			{
				printf("Player %d wins on move %d\n", i%2+1, i);
				over = true;
			}
			table[s].push_back(board);
		}
		if(!over)
			printf("Draw\n");
	}
	return 0;
}