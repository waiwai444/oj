#include <stdio.h>
#include <string.h>

#define OCCUPIED 'o'

int n;
struct Board
{
    char cell[4][4];
};

void occupy(Board &board, int row, int col)
{
    int i;
    board.cell[row][col] = OCCUPIED;
    for(i = 1; col+i < n && board.cell[row][col+i] != 'X'; i++)
        board.cell[row][col+i] = OCCUPIED;
    for(i = 1; col-i >= 0 && board.cell[row][col-i] != 'X'; i++)
        board.cell[row][col-i] = OCCUPIED;
    for(i = 1; row+i < n && board.cell[row+i][col] != 'X'; i++)
        board.cell[row+i][col] = OCCUPIED;
    for(i = 1; row-i >= 0 && board.cell[row-i][col] != 'X'; i++)
        board.cell[row-i][col] = OCCUPIED;
}

int dfs(const Board& board)
{
    int i, j, rook_num = 0, tmp;
    Board new_board;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(board.cell[i][j] == '.')
            {
                new_board = board;
                occupy(new_board, i, j);
                tmp = dfs(new_board)+1;
                if(tmp > rook_num)
                    rook_num = tmp;
            }
        }
    }
    return rook_num;
}

int main()
{
    int i;
    Board board;
    char input[5];
    while(scanf("%d", &n), n)
    {
        for(i = 0; i < n; i++)
        {
            scanf("%s", input);
            memcpy(board.cell[i], input, n*sizeof(char));
        }
        printf("%d\n", dfs(board));
    }
    return 0;
}