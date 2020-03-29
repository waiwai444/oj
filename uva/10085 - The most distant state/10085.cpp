#include <stdio.h>

const char result_board[9][10] = {
    "876041253",	// for 0 1 2 3 4 5 6 7 8
    "086743251",	// for 1 0 2 3 4 5 6 7 8
    "806743251",	// ...
    "876342051",
    "476208351",
    "840756321",
    "864057321",
    "847652310",
    "867254301"
};

const char result_step[9][32] = {
	"DDRUULDDRRUULDRULLDDRULDRRUULLD",
	"LDDRUULDDRURULLDRRDLULDRURULDLU",
	"LLDDRURDLURULLDRRDLURULLDDRRUUL",
	"URDLDRURDLUULDDRURULLDRRULLDRDL",
	"ULDDRUULDDRUULDRRULLDRRDLULDRU",
	"ULLDDRULDRRUULDDLURDRUULLDDRRUU",
	"UURDDLUURRDLDRULDLUURDLURRDDLLU",
	"UULDDRRUULDLDRRUULDLDRRUULLDDRR",
	"UULLDDRUULDDRURULLDRRDLLURRULDD"
};

int map[9];

int main()
{
	int i, j, k, c, tc, t;
	char sq[3][3], ch, res_sq[20];
	int empty_pos;
	scanf("%d", &tc);
	for(c = 1; c <= tc; c++)
	{
		for(i = 0, k = 1; i < 3; i++)
			for(j = 0; j < 3; j++)
			{
                scanf("%d", &t);
                sq[i][j] = (char)t+'0';
                if(sq[i][j] == '0')
					empty_pos = 3*i+j;
				else
					map[k++] = sq[i][j];
			}

		for(i = j = 0; i < 9; i++)
		{
			ch = result_board[empty_pos][i];
			if(ch != '0')
				res_sq[j++] = map[ch-'0'];
			else
				res_sq[j++] = '0';
			if((i+1)%3 == 0)
				res_sq[j++] = '\n';
			else
				res_sq[j++] = ' ';
		}
		res_sq[j] = '\0';
		printf("Puzzle #%d\n%s%s\n\n", c, res_sq, result_step[empty_pos]);
	}
	return 0;
}
