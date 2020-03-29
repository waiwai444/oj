#include <stdio.h>
#include <string.h>
#include <vector>

int row, col;

struct Node
{
	bool inuse;
	bool valid;	// Contains garbage, [1,1] and [row][col] may be dummies for source and sink
	int row, col;
	std::vector<struct Node *> from;
	struct Node *rnext;

	int max_ga;
	int path_cnt;
} field[101][101];

void init()
{
	for(int i = 1; i <= 100; i++)
		for(int j = 1; j <= 100; j++)
		{
			field[i][j].row = i;
			field[i][j].col = j;
		}
}

void reset()
{
	for(int i = 1; i <= row; i++)
		for(int j = 1; j <= col; j++)
			if(field[i][j].inuse)
			{
				field[i][j].inuse = false;
				field[i][j].from.clear();
				field[i][j].max_ga = field[i][j].path_cnt = 0;
			}
	// Preset dummies [1][1] and [row][col]
	field[1][1].inuse = field[row][col].inuse = true;
	field[1][1].valid = field[row][col].valid = false;
}

void construct_next_link()
{
	int i, j, k;
	for(i = 1; i <= row; i++)
	{
		for(k = 0, j = 1; j <= col; j++)
		{
			if(!field[i][j].inuse)
				continue;
			field[i][k].rnext = &field[i][j];
			k = j;
		}
		field[i][k].rnext = NULL;
	}
}

inline void add_adjacent_node(struct Node *cur, struct Node *adj, int *adj_col)
{
	if(adj && adj->col < *adj_col)
	{
		adj->from.push_back(cur);
		*adj_col = adj->col;
	}
}

void construct_graph()
{
	int i, j, c;
	struct Node *cur = NULL;
	struct Node *adj = NULL;
	for(i = 1; i <= row; i++)
	{
		cur = field[i][0].rnext;
		while(cur)
		{
			c = col+1;
			adj = cur->rnext;
			add_adjacent_node(cur, adj, &c);
			for(j = i+1; j <= row; j++)
			{
				adj = field[j][0].rnext;
				while(adj && adj->col < cur->col)
					adj = adj->rnext;
				add_adjacent_node(cur, adj, &c);
			}
			cur = cur->rnext;
		}
	}
}

void dfs(struct Node *cur)
{
	int i;
	struct Node *adj;
	for(i = 0; i < cur->from.size(); i++)
	{
		adj = cur->from[i];
		if(adj->path_cnt == 0)
			dfs(adj);
		if(adj->max_ga > cur->max_ga)
		{
			cur->max_ga = adj->max_ga;
			cur->path_cnt = adj->path_cnt;
		}
		else if(adj->max_ga == cur->max_ga)
			cur->path_cnt += adj->path_cnt;
	}
	if(cur->valid)	// Only source and sink may be invalid.
		++cur->max_ga;
}

void solve()
{
	int i;

	construct_next_link();
	construct_graph();

	field[1][1].max_ga = field[1][1].valid ? 1 : 0;
	field[1][1].path_cnt = 1;

	if(row > 1 || col > 1)
		dfs(&field[row][col]);
}

void print_path(struct Node *cur)
{
	int i, d;
	d = cur->valid ? 1 : 0;
	for(i = 0; i < cur->from.size(); i++)
	{
		if(cur->from[i]->max_ga == cur->max_ga-d)
		{
			print_path(cur->from[i]);
			break;
		}
	}
	if(d)
		printf(" %d", (cur->row-1)*col+cur->col);
}

int main()
{
	int r, c, test_case = 0;
	init();
	while(scanf("%d%d", &row, &col), row >= 0)
	{
		reset();
		while(scanf("%d%d", &r, &c), r > 0)
			field[r][c].inuse = field[r][c].valid = true;
		solve();
		printf("CASE#%d: %d %d", ++test_case, field[row][col].max_ga, field[row][col].path_cnt);
		print_path(&field[row][col]);
		printf("\n");
	}
	return 0;
}
