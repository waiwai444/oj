#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <vector>

#define MAX_ROW 999
#define MAX_COL 999

int nrows, ncols;
int sheet[MAX_ROW][MAX_COL];

struct position
{
    short row, col;
};

std::vector<position> determine_chain[MAX_ROW][MAX_COL];
std::vector<position> topo_order;

inline int get_col(char **ptr)
{
    int col = 0;
    while(**ptr != '\0' && isalpha(**ptr))
        col = col*26+*((*ptr)++)-'A'+1;
    return col-1;
}

inline int get_row(char **ptr)
{
    int row = 0;
    while(**ptr != '\0' && isdigit(**ptr))
        row = row*10+*((*ptr)++)-'0';
    return row-1;
}

void solve_formula(int row, int col, char formula[])
{
    char *ptr = formula;
    int row2, col2;
    position pos;
    do
    {
        ptr++;
        col2 = get_col(&ptr);
        row2 = get_row(&ptr);
	pos.row = row;
	pos.col = col;
        determine_chain[row2][col2].push_back(pos);
    } while(*ptr == '+');
}

bool visited[MAX_ROW][MAX_COL];

void dfs(int row, int col)
{
    int i;
    position pos;
    visited[row][col] = true;
    for(i = 0; i < determine_chain[row][col].size(); i++)
    {
        pos.row = determine_chain[row][col][i].row;
        pos.col = determine_chain[row][col][i].col;
        if(!visited[pos.row][pos.col])
                dfs(pos.row, pos.col);
    }
    pos.row = row;
    pos.col = col;
    topo_order.push_back(pos);
}

void toposort()
{
    int i, j;
    memset(visited, false, sizeof(visited));
    for(i = 0; i < nrows; i++)
    {
        for(j = 0; j < ncols; j++)
        {
            if(!visited[i][j])
            {
                dfs(i, j);
            }
        }
    }
}

int main()
{
    int tc, i, j;
    char input[1000];
    scanf("%d", &tc);
    topo_order.reserve(MAX_ROW*MAX_COL);
    while(tc--)
    {
        scanf("%d%d", &ncols, &nrows);
        for(i = 0; i < nrows; i++)
        {
            for(j = 0; j < ncols; j++)
            {
                scanf("%s", input);
                if(input[0] == '=')
                {
                    sheet[i][j] = 0;
                    solve_formula(i, j, input);
                }
                else
                {
                    sheet[i][j] = atoi(input);
                }
            }
        }
        topo_order.clear();
        toposort();
        for(i = topo_order.size()-1; i >= 0; i--)
        {
            for(j = 0; j < determine_chain[topo_order[i].row][topo_order[i].col].size(); j++)
            {
                position &cell = determine_chain[topo_order[i].row][topo_order[i].col][j];
                sheet[cell.row][cell.col] += sheet[topo_order[i].row][topo_order[i].col];
            }
            determine_chain[topo_order[i].row][topo_order[i].col].clear();
        }
        
        for(i = 0; i < nrows; i++)
        {
            for(j = 0; j < ncols-1; j++)
                printf("%d ", sheet[i][j]);
            printf("%d\n", sheet[i][j]);
        }
    }
    return 0;
}
