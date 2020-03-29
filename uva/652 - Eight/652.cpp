#include <stdio.h>
#include <string.h>

const int BOARD_NUM = 362880;
const int DELTA_R[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const char DELTA_CH[4] = {'d', 'u', 'r', 'l'};

// the record of the state of the board in searching
struct BoardState {
    char board[9];
    int epos;
    int next_board_idx;
    char next_step;
    bool solvable;
} rec[BOARD_NUM];

int board_queue[BOARD_NUM];
int qfront, qback;

// use Cantor expansion to represent the index of each layout
inline int cantor_expansion(const char perm[])
{
    static const int FACT[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
    int i, j, cnt, ce = 0;
    for(i = 0; i < 8; i++)
    {
        cnt = 0;
        for(j = i+1; j < 9; j++)
            if(perm[j] < perm[i])
                cnt++;
        ce += cnt*FACT[8-i];
    }
    return ce;
}

// swap two numbers, used to move the number
inline void swap(char board[9], int pos1, int pos2)
{
    char t = board[pos1];
    board[pos1] = board[pos2];
    board[pos2] = t;
}

inline void copy_board(char dest[9], const char src[9])
{
    memcpy(dest, src, 9*sizeof(char));
}

// visit all adjacent nodes
void generate_candidates(int cur_board_idx)
{
    int i, ce, epos = rec[cur_board_idx].epos, erow, ecol, new_epos, new_erow, new_ecol;
    erow = epos/3;
    ecol = epos%3;
    char new_board[9];
    for(i = 0; i < 4; i++)
    {
        new_erow = erow+DELTA_R[i][0];
        new_ecol = ecol+DELTA_R[i][1];
        if(new_erow >= 0 && new_erow < 3 && new_ecol >= 0 && new_ecol < 3)
        {
            new_epos = new_erow*3+new_ecol;
            copy_board(new_board, rec[cur_board_idx].board);
            swap(new_board, epos, new_epos);
            ce = cantor_expansion(new_board);
            if(!rec[ce].solvable)
            {
                copy_board(rec[ce].board, new_board);
                rec[ce].epos = new_epos;
                rec[ce].next_board_idx = cur_board_idx;
                rec[ce].next_step = DELTA_CH[i];
                rec[ce].solvable = true;
                board_queue[qback++] = ce;
            }
        }
    }
}

// breadth first search from the destination
void bfs(const char dest_board[9], int dest_epos, int dest_ce)
{
    int i;
    memset(rec, 0, sizeof(rec));
    qfront = qback = 0;
    copy_board(rec[dest_ce].board, dest_board);
    rec[dest_ce].epos = dest_epos;
    rec[dest_ce].next_board_idx = -1;
    rec[dest_ce].solvable = true;
    board_queue[qback++] = dest_ce;
    
    while(qfront != qback)
    {
        i = board_queue[qfront++];
        generate_candidates(i);
    }
}

int main()
{
    int i, N, ce, dest_ce;
    char t[2];
    int epos = -1;	// the position of the empty slot
    char board[9];	// the board
    const char dest[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};	// the target layout
    dest_ce = cantor_expansion(dest);
    bfs(dest, 8, dest_ce);
    scanf("%d", &N);
    while(N--)
    {
        for(i=0; i<9; i++)
        {
            scanf("%s", &t[0]);
            if(t[0]=='x')
            {
                t[0] = 0;
                epos = i;
            }
            else
                t[0] -= '0';
            board[i] = t[0];
        }
        ce = cantor_expansion(board);
        if(!rec[ce].solvable)
            printf("unsolvable\n");
        else
        {
            for(i = ce; i != dest_ce; i = rec[i].next_board_idx)
                printf("%c", rec[i].next_step);
            printf("\n");
        }
        if(N)
            printf("\n");
    }
    return 0;
}