#include <stdio.h>
#include <string.h>

#define FULCRUM_L -3
#define FULCRUM_R 3

struct Package
{
	int pos, weight;
	int torque_l, torque_r;	// positive for cw, negative for ccw
};

int board_length;
int board_weight;
int n;
int n_flank, n_central;
Package flank_pkg[20], central_pkg[20];

int torque_l, torque_r;
bool removed[20];
bool memo[1048580];
int pkg_order[20];

inline void remove_pkg(Package pkg_set[], int idx)
{
	torque_r -= pkg_set[idx].torque_r;
	torque_l -= pkg_set[idx].torque_l;
}

inline void place_pkg(Package pkg_set[], int idx)
{
	torque_r += pkg_set[idx].torque_r;
	torque_l += pkg_set[idx].torque_l;
}

inline int set_bit(int cur_memo, int idx)
{
	return cur_memo | 1<<idx;
}

bool backtrack(int cur_depth, int cur_memo)
{
	if(cur_depth == n_flank)
		return true;
	
	int new_memo;
	for(int i = 0; i < n_flank; i++)
	{
		if(!removed[i])
		{
			removed[i] = true;
			new_memo = set_bit(cur_memo, i);
			if(memo[new_memo])
			{
				removed[i] = false;
				continue;
			}
			remove_pkg(flank_pkg, i);
			
			if(torque_r <= 0 && torque_l >= 0)
			{
				pkg_order[cur_depth] = i;
				if(backtrack(cur_depth+1, new_memo))
					return true;
				else
					memo[new_memo] = true;
			}
			else
				memo[new_memo] = true;
			
			place_pkg(flank_pkg, i);
			removed[i] = false;
		}
	}
	
	return false;
}

int main()
{
	int i, tc = 0;
	while(scanf("%d%d%d", &board_length, &board_weight, &n), board_length)
	{
		board_length *= 2;
		n_flank = n_central = 0;
		Package pkg;
		for(i = 0; i < n; i++)
		{
			scanf("%d%d", &pkg.pos, &pkg.weight);
			pkg.pos *= 2;
			pkg.torque_l = pkg.weight*(pkg.pos-FULCRUM_L);
			pkg.torque_r = pkg.weight*(pkg.pos-FULCRUM_R);
			if(pkg.pos > FULCRUM_R || pkg.pos < FULCRUM_L)
				flank_pkg[n_flank++] = pkg;
			else
				central_pkg[n_central++] = pkg;
		}
        
		printf("Case %d:\n", ++tc);
		if(board_length == FULCRUM_R-FULCRUM_L)
			for(i = 0; i < n_central; i++)
				printf("%d %d\n", central_pkg[i].pos, central_pkg[i].weight);
		else
		{
			memset(removed, false, sizeof(removed));
			memset(memo, false, sizeof(memo));
			
			const int flank_length = board_length/2-FULCRUM_R;
			//torque_r = board_weight*(flank_length/board_length)*flank_length/2-board_weight*((board_length-flank_length)/board_length)*(board_length-flank_length)/2;
			torque_r = board_weight*(2*flank_length-board_length)/2;
			torque_l = -torque_r;
			
			for(i = 0; i < n_central; i++)
				place_pkg(central_pkg, i);
			for(i = 0; i < n_flank; i++)
				place_pkg(flank_pkg, i);
			
			if(torque_r > 0 || torque_l < 0)
				printf("Impossible\n");
			else
			{
				if(backtrack(0, 0))
				{
					for(i = 0; i < n_flank; i++)
						printf("%d %d\n", flank_pkg[pkg_order[i]].pos/2, flank_pkg[pkg_order[i]].weight);
					for(i = 0; i < n_central; i++)
						printf("%d %d\n", central_pkg[i].pos/2, central_pkg[i].weight);
				}
				else
					printf("Impossible\n");
			}
		}
	}
	return 0;
}