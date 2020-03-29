#include <stdio.h>
#include <string.h>

#define MAX_DEPTH 16

int n;

// the smallest number of dissection of each odd big square
const int depth[24] = { 6, 8, 9, 6, 11, 11, 6, 12, 13, 6, 13, 8, 6, 14, 15, 6, 8, 15, 6, 15, 16, 6, 16, 9 };

// precalculated sum-of-squares of each large prime number
const int sqsum_decomp[24][MAX_DEPTH] = {
	{},
	{},
	{},
	{},
	{ 6, 5, 5, 4, 2, 2, 2, 2, 1, 1, 1 },	// 11
	{ 7, 6, 6, 4, 3, 3, 2, 2, 2, 1, 1 },	// 13
	{},
	{ 9, 8, 8, 5, 4, 4, 3, 2, 2, 2, 1, 1 },	// 17
	{ 10, 9, 9, 7, 3, 3, 3, 3, 2, 2, 2, 1, 1 },	// 19
	{},
	{ 12, 11, 11, 7, 5, 5, 4, 3, 3, 2, 2, 1, 1 },	// 23
	{},
	{},
	{ 15, 14, 14, 8, 7, 7, 5, 3, 3, 3, 2, 2, 1, 1 },	// 29
	{ 16, 15, 15, 11, 5, 5, 5, 5, 4, 2, 2, 2, 2, 1, 1 },	// 31
	{},
	{},
	{ 19, 18, 18, 12, 7, 7, 7, 5, 4, 3, 3, 2, 2, 1, 1 },	// 37
	{}, 
	{ 23, 18, 18, 12, 11, 11, 7, 5, 4, 3, 3, 2, 2, 1, 1 },	// 41
	{ 22, 21, 21, 15, 7, 7, 7, 7, 5, 3, 3, 3, 2, 2, 1, 1 },	// 43
	{},
	{ 24, 23, 23, 14, 10, 10, 8, 6, 6, 4, 4, 2, 2, 1, 1, 1 },	// 47
	{}
};

int cur_decomp[MAX_DEPTH];
int cur_decomp_size = 0;

struct Square
{
	bool grid[50][50];
};

struct Tile
{
	int x, y, l;
};

Square cur_square;
Tile cur_path[MAX_DEPTH];
int cur_path_len = 0;

int get_tiling_pos(int tile_side, Tile candidate_pos[])
{
	int i, j, k, l;
	int candidate_num = 0;
	for(i = 0; i <= n - tile_side; i++)
		for(j = 0; j <= n - tile_side; j++)
			if(!cur_square.grid[i][j])
			{
				bool overlap = false;
				for(k = i; k < i + tile_side; k++)
				{
					for(l = j; l < j + tile_side; l++)
						if(cur_square.grid[k][l])
						{
							overlap = true;
							break;
						}
					if(overlap)
						break;
				}
				if(!overlap)
				{
					Tile tile;
					tile.x = i;
					tile.y = j;
					candidate_pos[candidate_num++] = tile;
				}
			}
	return candidate_num;
}

inline void fill_square(int x, int y, int l, bool value = true)
{
	for(int i = x; i < x + l; i++)
		for(int j = y; j < y + l; j++)
			cur_square.grid[i][j] = value;
}

inline void print_result()
{
	printf("%d\n", cur_path_len);
	for(int i = 0; i < cur_path_len; i++)
		printf("%d %d %d\n", cur_path[i].x, cur_path[i].y, cur_path[i].l);
}

bool tiling(int cur_tile_idx)
{
	int i;
	Tile tile;
	if(cur_tile_idx >= cur_decomp_size)	// all small squares have been embedded into the big square
	{
		return true;
	}
	if(cur_tile_idx == 0)	// heuristic: the first small square will be on the upper left corner
	{
		tile.x = 1;
		tile.y = 1;
		tile.l = cur_decomp[0];
		cur_path[cur_path_len++] = tile;
		fill_square(0, 0, tile.l);
		if(tiling(1))
			return true;
		--cur_path_len;
	}
	else if(cur_tile_idx == 1)	// heuristic: the second small square will be on the upper right corner
	{
		tile.x = 1;
		tile.y = cur_decomp[0] + 1;
		tile.l = cur_decomp[1];
		cur_path[cur_path_len++] = tile;
		fill_square(0, cur_decomp[0], tile.l);
		if(tiling(2))
			return true;
		--cur_path_len;
	}
	else if(cur_tile_idx == 2)	// heuristic: the third small square will be on the bottom left corner
	{
		tile.x = cur_decomp[0] + 1;
		tile.y = 1;
		tile.l = cur_decomp[2];
		cur_path[cur_path_len++] = tile;
		fill_square(cur_decomp[0], 0, tile.l);
		if(tiling(3))
			return true;
		--cur_path_len;
	}
	else if(cur_tile_idx == 3)	// heuristic: the fourth small square will be on the right side
	{
		for(i = cur_decomp[1]; i <= n - cur_decomp[3]; i++)
		{
			tile.x = i + 1;
			tile.y = n - cur_decomp[3] + 1;
			tile.l = cur_decomp[3];
			cur_path[cur_path_len++] = tile;
			fill_square(i, n - cur_decomp[3], tile.l);
			if(tiling(4))
				return true;
			fill_square(i, n - cur_decomp[3], tile.l, false);
			--cur_path_len;
		}
	}
	else
	{
		Tile candidate_pos[n * n];
		int candidate_num = get_tiling_pos(cur_decomp[cur_tile_idx], candidate_pos);
		if(candidate_num == 0)
			return false;
		for(i = 0; i < candidate_num; i++)
		{
			if(cur_tile_idx == 4 && candidate_pos[i].x != n - cur_decomp[4] && candidate_pos[i].y != n - cur_decomp[4])	// heuristic: the fifth small square will be on the bottom or the right side
				continue;
			
			tile.x = candidate_pos[i].x + 1;
			tile.y = candidate_pos[i].y + 1;
			tile.l = cur_decomp[cur_tile_idx];
			cur_path[cur_path_len++] = tile;
			fill_square(candidate_pos[i].x, candidate_pos[i].y, tile.l);
			if(tiling(cur_tile_idx + 1))
				return true;
			fill_square(candidate_pos[i].x, candidate_pos[i].y, tile.l, false);
			--cur_path_len;
		}
	}
	return false;
}

void search_solution()
{
	int idx = n / 2 - 1;
	cur_decomp_size = depth[idx];
	memcpy(cur_decomp, sqsum_decomp[idx], cur_decomp_size * sizeof(int));
	cur_path_len = 0;
	memset(cur_square.grid, false, 50 * 50 * sizeof(bool));
	tiling(0);
	print_result();
}

int main()
{
	int t;
	scanf("%d", &t);
	while(t-- > 0)
	{
		scanf("%d", &n);
		if((n & 1) == 0)	// n is even, 4 sub-squares is optimal
		{
			int m = n / 2;
			printf("4\n");
			printf("1 1 %d\n", m);
			printf("1 %d %d\n", m + 1, m);
			printf("%d 1 %d\n", m + 1, m);
			printf("%d %d %d\n", m + 1, m + 1, m);
		}
		else if(n % 3 == 0)
		{
			int m = n / 3;
			printf("6\n");
			printf("1 1 %d\n", m * 2);
			printf("1 %d %d\n", m * 2 + 1, m);
			printf("%d %d %d\n", m + 1, m * 2 + 1, m);
			printf("%d 1 %d\n", m * 2 + 1, m);
			printf("%d %d %d\n", m * 2 + 1, m + 1, m);
			printf("%d %d %d\n", m * 2 + 1, m * 2 + 1, m);
		}
		else if(n % 5 == 0)
		{
			int m = n / 5;
			printf("8\n");
			printf("1 1 %d\n", m * 3);
			printf("1 %d %d\n", m * 3 + 1, m * 2);
			printf("%d 1 %d\n", m * 3 + 1, m * 2);
			printf("%d %d %d\n", m * 3 + 1, m * 3 + 1, m * 2);
			printf("%d %d %d\n", m * 2 + 1, m * 3 + 1, m);
			printf("%d %d %d\n", m * 2 + 1, m * 4 + 1, m);
			printf("%d %d %d\n", m * 3 + 1, m * 2 + 1, m);
			printf("%d %d %d\n", m * 4 + 1, m * 2 + 1, m);
		}
		else if(n % 7 == 0)
		{
			int m = n / 7;
			printf("9\n");
			printf("1 1 %d\n", m * 2);
			printf("1 %d %d\n", m * 2 + 1, m * 2);
			printf("1 %d %d\n", m * 4 + 1, m * 3);
			printf("%d 1 %d\n", m * 2 + 1, m);
			printf("%d %d %d\n", m * 2 + 1, m + 1, m * 2);
			printf("%d %d %d\n", m * 2 + 1, m * 3 + 1, m);
			printf("%d 1 %d\n", m * 3 + 1, m);
			printf("%d %d %d\n", m * 3 + 1, m * 3 + 1, m * 4);
			printf("%d 1 %d\n", m * 4 + 1, m * 3);
		}
		else
		{
			search_solution();
		}
	}
	return 0;
}