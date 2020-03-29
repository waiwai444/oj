#include <stdio.h>
#include <string.h>
#include <queue>
#include <set>

const int move_step[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};
const char target[5] = {31, 30, 24, 16, 0};

struct Board
{
	char row[5];
	char empty_r, empty_c;
};

std::set<unsigned long> visited;

void read_input(Board &board)
{
	char input[10];
	memset(&board, 0, sizeof(board));
	for(int i = 0; i < 5; i++)
	{
		fgets(input, sizeof(input), stdin);
		for(char *p = input, b = 1; *p != '\n' && *p != '\0'; ++p, b <<= 1)
		{
            if(*p == '1')
				board.row[i] |= b;
			else if(*p == ' ')
			{
				board.empty_r = i;
				board.empty_c = p-input;
			}
		}
	}
}

unsigned long hash(const Board &board)
{
    unsigned long h = 0;
	h |= (unsigned long)board.row[0];
	h |= (unsigned long)board.row[1]<<5;
	h |= (unsigned long)board.row[2]<<10;
	h |= (unsigned long)board.row[3]<<15;
	h |= (unsigned long)board.row[4]<<20;
    h |= (unsigned long)board.empty_r<<25;
    h |= (unsigned long)board.empty_c<<28;
    return h;
}

bool move(const Board &cur_board, Board &new_board, int step_idx)
{
	int new_r = cur_board.empty_r+move_step[step_idx][0], new_c = cur_board.empty_c+move_step[step_idx][1];
	if(new_r < 0 || new_r > 4 || new_c < 0 || new_c > 4)
		return false;
	new_board = cur_board;
	new_board.empty_r = new_r;
	new_board.empty_c = new_c;
    bool black = cur_board.row[new_r] & (1<<new_c);
    if(black)
	{
        new_board.row[new_r] &= ~(1<<new_c);
        new_board.row[(int)cur_board.empty_r] |= 1<<cur_board.empty_c;
	}
	return true;
}

bool finished(const Board &board)
{
    if(board.empty_r != 2 || board.empty_c != 2)
		return false;
	for(int i = 0; i < 5; i++)
		if(board.row[i] != target[i])
			return false;
	return true;
}

int bfs(const Board &init_board)
{
	if(finished(init_board))
		return 0;
	Board board, new_board;
	int i, step;
	unsigned long h = hash(init_board);
	std::queue<Board> board_q;
	std::queue<int> step_q;
	board_q.push(init_board);
	step_q.push(0);
	visited.insert(h);
	while(!board_q.empty())
	{
		step = step_q.front();
		if(step == 10)
			return -1;
		step_q.pop();
		board = board_q.front();
		board_q.pop();
		for(i = 0; i < 8; i++)
		{
			if(!move(board, new_board, i))
				continue;
			h = hash(new_board);
			if(visited.find(h) != visited.end())
				continue;
			if(finished(new_board))
				return step+1;
			visited.insert(h);
			board_q.push(new_board);
			step_q.push(step+1);
		}
	}
	return -1;
}

int main()
{
	int tc, step;
	char input[10];
	Board init_board;
	scanf("%d", &tc);
	fgets(input, sizeof(input), stdin);
	while(tc--)
	{
		read_input(init_board);
		visited.clear();
		if((step = bfs(init_board)) >= 0)
			printf("Solvable in %d move(s).\n", step);
		else
			printf("Unsolvable in less than 11 move(s).\n");
	}
	return 0;
}
