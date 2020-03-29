#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#define ORIGIN 50
#define SIZE 100
#define EAST 0
#define NORTH 1
#define SOUTH 2
#define WEST 3

int longest;
char blocked[SIZE][SIZE];
char vis[SIZE][SIZE];
char x_blk[SIZE], y_blk[SIZE];
int total_cnt;
std::string dir_st;
const char dir_name[] = {'e', 'n', 's', 'w'};
const int dx[] = {1, 0, 0, -1};
const int dy[] = {0, 1, -1, 0};
int dist_sum[21][21];

void init_dist_sum()
{
	for(int i = 1; i <= 20; ++i)
	{
		dist_sum[i][i] = i;
		if(i > 1)
			dist_sum[i][i-1] = i-1;
		for(int j = i-2; j >= 1; --j)
		{
			dist_sum[i][j] = dist_sum[i][j+2]+j;
		}
	}
}

bool is_inboard(int x, int y)
{
	return x < SIZE && y < SIZE && x >= 0 && y >= 0;
}

bool is_path_blocked(int x, int y, int dir, int step)
{
	int i;
	if((dir == EAST || dir == WEST) && !y_blk[y])
		return false;
	if((dir == NORTH || dir == SOUTH) && !x_blk[x])
		return false;
	for(i = 0; i < step; ++i)
	{
		x += dx[dir], y += dy[dir];
		if(blocked[x][y])
			return true;
	}
	return false;
}

void dfs(int step, int x, int y, int prev_dir)
{
    if(step > longest)
    {
        if(x == ORIGIN && y == ORIGIN)
        {
			std::puts(dir_st.c_str());
            ++total_cnt;
        }
        return;
    }
	if(prev_dir == NORTH || prev_dir == SOUTH)
	{
		if(std::abs(x-ORIGIN) > dist_sum[longest][step])
			return;
	}
	else if(prev_dir == EAST || prev_dir == WEST)
	{
		if(std::abs(y-ORIGIN) > dist_sum[longest][step])
			return;
	}
    for(int i = 0; i < 4; ++i)
    {
        if(prev_dir >= 0 && (dx[i] == dx[prev_dir] || dy[i] == dy[prev_dir]))
            continue;
		if(is_path_blocked(x, y, i, step))
			continue;
        int x2 = x+dx[i]*step, y2 = y+dy[i]*step;
		if(!is_inboard(x2, y2) || vis[x2][y2])
			continue;
        dir_st.push_back(dir_name[i]);
		vis[x2][y2] = 1;
        dfs(step+1, x2, y2, i);
		vis[x2][y2] = 0;
        dir_st.pop_back();
    }
}

void solve()
{
    total_cnt = 0;
	if(longest >= 7)
	{
		dir_st.clear();
		dir_st.reserve(longest+1);
		std::memset(vis, 0, sizeof(vis));
		dfs(1, ORIGIN, ORIGIN, -1);
	}
    std::printf("Found %d golygon(s).\n\n", total_cnt);
}

int main()
{
    int tc, nb, x, y;
	init_dist_sum();
    std::scanf("%d", &tc);
    while(tc--)
    {
        std::scanf("%d%d", &longest, &nb);
        std::memset(blocked, 0, sizeof(blocked));
		std::memset(x_blk, 0, sizeof(x_blk));
		std::memset(y_blk, 0, sizeof(y_blk));
        for(int i = 0; i < nb; ++i)
        {
            std::scanf("%d%d", &x, &y);
			if(is_inboard(ORIGIN+x, ORIGIN+y))
			{
				blocked[ORIGIN+x][ORIGIN+y] = 1;
				x_blk[ORIGIN+x] = y_blk[ORIGIN+y] = 1;
			}
        }
        solve();
    }
    return 0;
}
