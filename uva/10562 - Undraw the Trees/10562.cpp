#include <stdio.h>
#include <string.h>

char prof_tree[201][205];
int line_num;
char our_tree[40000];
int our_idx;

void find_root(int *i, int *j)
{
	for(*i = 0; *i < line_num; ++*i)
		for(*j = 0; prof_tree[*i][*j] != '\0'; ++*j)
			if(prof_tree[*i][*j] != ' ')
				return;
}

void convert(int row, int col)
{
	int i;
	our_tree[our_idx++] = prof_tree[row][col];
	our_tree[our_idx++] = '(';
	if(row+1 < line_num && prof_tree[row+1][col] == '|')
	{
		for(i = col; i >= 0 && prof_tree[row+2][i] != ' '; i--);
		for(i++; prof_tree[row+2][i] == '-'; i++)
			if(prof_tree[row+3][i] == '\0')
				break;
			else if(prof_tree[row+3][i] != ' ' && prof_tree[row+3][i] != '|' && prof_tree[row+3][i] != '-' && prof_tree[row+3][i] != '#')
				convert(row+3, i);
	}
	our_tree[our_idx++] = ')';
}

int main()
{
	int i, j, tc;
	scanf("%d", &tc);
	fgets(prof_tree[0], sizeof(prof_tree[0]), stdin);
	prof_tree[0][strlen(prof_tree[0])-1] = 0;
	while(tc--)
	{
		line_num = 0;
		while(true)
		{
			fgets(prof_tree[line_num], sizeof(prof_tree[line_num]), stdin);
			prof_tree[line_num][strlen(prof_tree[line_num])-1] = 0;
			if(prof_tree[line_num][0] == '#')
				break;
			line_num++;
		}
		our_idx = 0;
		our_tree[our_idx++] = '(';
		if(line_num > 0)
		{
			find_root(&i, &j);
			convert(i, j);			
		}
		our_tree[our_idx++] = ')';
		our_tree[our_idx] = '\0';
		printf("%s\n", our_tree);
	}
	return 0;
}
