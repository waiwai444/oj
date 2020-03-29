#include <stdio.h>
#include <string.h>

int board[8][8];

int max_sum, cur_sum;
int queue_pos[8];   // index by row
bool col_flag[8];
bool main_diag[15];
bool minor_diag[15];

void dfs(int row)
{
    for(int col = 0; col < 8; col++)
    {
        if(!col_flag[col] && !main_diag[row-col+7] && !minor_diag[row+col])
        {
            queue_pos[row] = col;
            col_flag[col] = main_diag[row-col+7] = minor_diag[row+col] = true;
            cur_sum += board[row][col];
            if(row < 7)
                dfs(row+1);
            else
            {
                if(cur_sum > max_sum)
                    max_sum = cur_sum;
            }
            col_flag[col] = main_diag[row-col+7] = minor_diag[row+col] = false;
            cur_sum -= board[row][col];
        }
    }
}

int main()
{
    int k, i, j;
    scanf("%d", &k);
    while(k--)
    {
        for(i = 0; i < 8; i++)
            for(j = 0; j < 8; j++)
                scanf("%d", &board[i][j]);
        max_sum = cur_sum = 0;
        memset(col_flag, false, sizeof(col_flag));
        memset(main_diag, false, sizeof(main_diag));
        memset(minor_diag, false, sizeof(minor_diag));
        dfs(0);
        printf("%5d\n", max_sum);
    }
    return 0;
}