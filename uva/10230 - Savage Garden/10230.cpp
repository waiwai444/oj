#include <cstdio>
#include <cstring>
#include <cctype>

const int pow2[11] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
const int dx[8] = { -1, -1, 0, 0, 1, 1, 2, 2 };
const int dy[8] = { 0, 1, -1, 2, -1, 2, 0, 1 };
const int dx2[4][4] = { { 0, -1, 2, 2 }, { 0, -1, 2, 2 }, { 1, -1, -1, 2 }, { 1, -1, -1, 2 } };
const int dy2[4][4] = { { 0, 2, -1, 2 }, { 1, -1, -1, 2 }, { 0, -1, 2, 2 }, { 1, -1, 2, -1 } };

int n, hx, hy;
char grid[1026][1026];

inline bool house_at(int ax, int ay, int sz)
{
	return hx >= ax && hx < ax+sz && hy >= ay && hy < ay+sz;
}

inline char get_ch(int f)
{
	for(int i = 0; i < 26; i++)
		if((f&(1<<i)) == 0)
			return 'a'+i;
	return 0;
}

void fill2(int x, int y)
{
	int i, f = 0;
	for(i = 0; i < 8; i++)
		if(isalpha(grid[y+dy[i]][x+dx[i]]))
			f |= (1<<(grid[y+dy[i]][x+dx[i]]-'a'));
	if(grid[y][x])
	{
		for(i = 0; i < 4; i++)
			if(isalpha(grid[y+dy2[0][i]][x+dx2[0][i]]))
				f |= (1<<(grid[y+dy2[0][i]][x+dx2[0][i]]-'a'));
		grid[y+1][x] = grid[y][x+1] = grid[y+1][x+1] = get_ch(f);
	}
	else if(grid[y+1][x])
	{
		for(i = 0; i < 4; i++)
			if(isalpha(grid[y+dy2[1][i]][x+dx2[1][i]]))
				f |= (1<<(grid[y+dy2[1][i]][x+dx2[1][i]]-'a'));
		grid[y][x] = grid[y][x+1] = grid[y+1][x+1] = get_ch(f);
	}
	else if(grid[y][x+1])
	{
		for(i = 0; i < 4; i++)
			if(isalpha(grid[y+dy2[2][i]][x+dx2[2][i]]))
				f |= (1<<(grid[y+dy2[2][i]][x+dx2[2][i]]-'a'));
		grid[y][x] = grid[y+1][x] = grid[y+1][x+1] = get_ch(f);
	}
	else if(grid[y+1][x+1])
	{
		for(i = 0; i < 4; i++)
			if(isalpha(grid[y+dy2[3][i]][x+dx2[3][i]]))
				f |= (1<<(grid[y+dy2[3][i]][x+dx2[3][i]]-'a'));
		grid[y][x] = grid[y][x+1] = grid[y+1][x] = get_ch(f);
	}
}

void recur(int ax, int ay, int sz)
{
	if(sz == 2)
	{
		fill2(ax, ay);
		return;
	}
	int mx = ax+sz/2, my = ay+sz/2;
	bool h = house_at(ax, ay, sz);
	if((h && hx < mx && hy < my) || grid[ay][ax])
		grid[my][mx] = grid[my][mx-1] = grid[my-1][mx] = 'a';
	else if((h && hx < mx && hy >= my) || grid[ay+sz-1][ax])
		grid[my][mx] = grid[my-1][mx] = grid[my-1][mx-1] = 'a';
	else if((h && hx >= mx && hy < my) || grid[ay][ax+sz-1])
		grid[my][mx] = grid[my][mx-1] = grid[my-1][mx-1] = 'a';
	else
		grid[my][mx-1] = grid[my-1][mx] = grid[my-1][mx-1] = 'a';
	recur(ax, ay, sz/2);
	recur(ax, my, sz/2);
	recur(mx, ay, sz/2);
	recur(mx, my, sz/2);
}

void solve()
{
	memset(grid, 0, sizeof(grid));
	grid[hy][hx] = '*';
	recur(1, 1, pow2[n]);
}

int main()
{
	int i;
	while(scanf("%d%d%d", &n, &hx, &hy) != EOF)
	{
		solve();
		for(i = 1; i <= pow2[n]; i++)
			printf("%s\n", &grid[i][1]);
		printf("\n");
	}
	return 0;
}

