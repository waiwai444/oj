#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <utility>

#define SHIP 'x'
#define NOSHIP 'o'
#define COVERED '.'
#define DETERMINED '!'

struct Point
{
	int r, c;
};

struct ShipCoord
{
	Point sq[4];
};

struct ShipShape
{
	int type;
	std::vector<ShipCoord> tr;	// translations
};

struct Board
{
	char sq[20][20];
	bool ship_found[7];
};

int width, height;

std::vector<ShipShape> ship_set;
const int basic_shape[7][4][2] = {
	{{0, 0}, {0, 1}, {1, 0}, {1, 1}},
	{{0, 0}, {0, 1}, {1, 1}, {1, 2}},
	{{0, 0}, {0, 1}, {1, -1}, {1, 0}},
	{{0, 0}, {1, 0}, {1, 1}, {1, 2}},
	{{0, 0}, {1, 0}, {1, -1}, {1, -2}},
	{{0, 0}, {1, -1}, {1, 0}, {1, 1}},
	{{0, 0}, {0, 1}, {0, 2}, {0, 3}}
};

bool compare_point(const Point &p1, const Point &p2)
{
	if(p1.r < p2.r)
		return true;
	else if(p1.r > p2.r)
		return false;
	else if(p1.c < p2.c)
		return true;
	return false;
}

bool dup_shape(const ShipCoord &ship_coord)
{
	int i, j, k;
	for(i = 0; i < ship_set.size(); i++)
	{
		for(j = 0; j < ship_set[i].tr.size(); j++)
		{
			for(k = 0; k < 4; k++)
				if(ship_set[i].tr[j].sq[k].r != ship_coord.sq[k].r || ship_set[i].tr[j].sq[k].c != ship_coord.sq[k].c)
					break;
			if(k == 4)
				return true;
		}
	}
	return false;
}

void rotate(const ShipCoord &ship_coord, ShipCoord &new_ship_coord)
{
	for(int i = 0; i < 4; i++)
	{
		new_ship_coord.sq[i].r = ship_coord.sq[i].c;
		new_ship_coord.sq[i].c = -ship_coord.sq[i].r;
	}
	std::sort(new_ship_coord.sq, &new_ship_coord.sq[4], compare_point);
}

void translate(const ShipCoord &ship_coord, ShipCoord &new_ship_coord, int orig_idx)
{
	int old_orig_r = ship_coord.sq[orig_idx].r;
	int old_orig_c = ship_coord.sq[orig_idx].c;
	for(int i = 0; i < 4; i++)
	{
		new_ship_coord.sq[i].r = ship_coord.sq[i].r-old_orig_r;
		new_ship_coord.sq[i].c = ship_coord.sq[i].c-old_orig_c;
	}
	std::sort(new_ship_coord.sq, &new_ship_coord.sq[4], compare_point);
}

void generate_all_ships()
{
	ship_set.reserve(30);
	int i, j, k;
	ShipShape ship;
	ship.tr.reserve(4);
	ShipCoord ship_coord, new_ship_coord;
	for(i = 0; i < 7; i++)
	{
		ship.type = i;
		ship.tr.clear();
		for(j = 0; j < 4; j++)
		{
			ship_coord.sq[j].r = basic_shape[i][j][0];
			ship_coord.sq[j].c = basic_shape[i][j][1];
		}
		std::sort(ship_coord.sq, &ship_coord.sq[4], compare_point);
		ship.tr.push_back(ship_coord);
		for(k = 0; k < 4; k++)	// translate
		{
			if(ship_coord.sq[k].r == 0 && ship_coord.sq[k].c == 0)
				continue;
			translate(ship_coord, new_ship_coord, k);
			if(!dup_shape(new_ship_coord))
				ship.tr.push_back(new_ship_coord);
		}
		ship_set.push_back(ship);
		
		for(j = 0; j < 3; j++)	// rotate
		{
			rotate(ship_coord, new_ship_coord);
			ship_coord = new_ship_coord;
			if(!dup_shape(ship_coord))
			{
				ship.tr.clear();
				ship.tr.push_back(new_ship_coord);
				for(k = 0; k < 4; k++)	// translate
				{
					if(ship_coord.sq[k].r == 0 && ship_coord.sq[k].c == 0)
						continue;
					translate(ship_coord, new_ship_coord, k);
					if(!dup_shape(new_ship_coord))
						ship.tr.push_back(new_ship_coord);
				}
				ship_set.push_back(ship);
			}
		}
	}
}

bool placable(const Board &board, int row, int col, int shape_idx, int coord_idx)
{
	ShipCoord &ship_coord = ship_set[shape_idx].tr[coord_idx];
	for(int i = 0; i < 4; i++)
	{
		int r = row+ship_coord.sq[i].r;
		int c = col+ship_coord.sq[i].c;
		if(r < 0 || r >= height || c < 0 || c >= width || board.sq[r][c] == NOSHIP || board.sq[r][c] == DETERMINED)
			return false;
	}
	return true;
}

void place(Board &board, int row, int col, int shape_idx, int coord_idx)
{
	ShipCoord &ship_coord = ship_set[shape_idx].tr[coord_idx];
	for(int i = 0; i < 4; i++)
		board.sq[row+ship_coord.sq[i].r][col+ship_coord.sq[i].c] = DETERMINED;
}

int intersection_flag[20][20];	// used for recording if a square is occupied by a ship in any possible layout

inline void init_intersection_flag()
{
	memset(intersection_flag, 0, sizeof(intersection_flag));
}

void inc_intersection_flag(int row, int col, int shape_idx, int coord_idx, int delta)
{
	ShipCoord &ship_coord = ship_set[shape_idx].tr[coord_idx];
	for(int i = 0; i < 4; i++)
		intersection_flag[row+ship_coord.sq[i].r][col+ship_coord.sq[i].c] += delta;
}

void find_intersection(Board &board, int n)
{
	int i, j;
	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++)
			if(intersection_flag[i][j] == n && board.sq[i][j] != DETERMINED)
				board.sq[i][j] = SHIP;
}

int uncover(Board &board, int row, int col)
{
	int i, j;
	init_intersection_flag();
	std::vector<std::pair<int, int> > ship_coord_idx;
	
	for(i = 0; i < ship_set.size(); i++)
	{
		if(!board.ship_found[ship_set[i].type])
		{
			for(j = 0; j < ship_set[i].tr.size(); j++)
				if(placable(board, row, col, i, j))
					ship_coord_idx.push_back(std::make_pair(i, j));
		}
	}
	
	if(ship_coord_idx.size() > 0)
	{
		for(i = 0; i < ship_coord_idx.size(); i++)
			inc_intersection_flag(row, col, ship_coord_idx[i].first, ship_coord_idx[i].second, 1);
		find_intersection(board, (int)ship_coord_idx.size());
	}
	
	if(ship_coord_idx.size() == 1)
	{
		place(board, row, col, ship_coord_idx[0].first, ship_coord_idx[0].second);
		board.ship_found[ship_set[ship_coord_idx[0].first].type] = true;
	}
	
	return (int)ship_coord_idx.size();
}

void mark_noship(Board &board)
{
	int i, j, k, l, m, r, c;
	for(i = 0; i < height; i++)
		for(j = 0; j < width; j++)
			if(board.sq[i][j] == COVERED)
			{
				for(k = 0; k < ship_set.size(); k++)
				{
					if(board.ship_found[ship_set[k].type])
						continue;
					for(l = 0; l < ship_set[k].tr.size(); l++)
					{
						for(m = 0; m < 4; m++)
						{
							r = i+ship_set[k].tr[l].sq[m].r;
							c = j+ship_set[k].tr[l].sq[m].c;
							if(r < 0 || r >= height || c < 0 || c >= width)
								break;
							char flag = board.sq[r][c];
							if(flag == NOSHIP || flag == DETERMINED)
								break;
						}
						if(m == 4)	// ok, may have a ship
							break;
					}
					if(l < ship_set[k].tr.size())	// ok, may have a ship
						break;
				}
				if(k == ship_set.size())
					board.sq[i][j] = NOSHIP;
			}
}

bool all_ships_found(const Board &board)
{
	for(int i = 0; i < 7; i++)
		if(!board.ship_found[i])	// make sure all 7 ships are found
			return false;
	return true;
}

bool ship_undetermined(const Board &board)
{
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			if(board.sq[i][j] == 'x')
				return true;
	return false;
}

int find_first_unfound_ship(const Board &board)
{
	for(int i = 0; i < 7; i++)
		if(!board.ship_found[i])
			return i;
	return -1;
}

int try_uncovered(Board &board)
{
	int i, j, k;
	if(all_ships_found(board))
	{
		if(ship_undetermined(board))
			return 0;
		return 1;
	}
	int total = 0, count = 0;
	bool det = false;
	Board new_board, tmp_board;
	int type = find_first_unfound_ship(board);
	for(k = 0; k < ship_set.size(); k++)
	{
		if(ship_set[k].type == type)
		{
			for(i = 0; i < height; i++)
			{
				for(j = 0; j < width; j++)
				{
					if(board.sq[i][j] == COVERED || board.sq[i][j] == SHIP)
					{
						if(placable(board, i, j, k, 0))
						{
							new_board = board;
							place(new_board, i, j, k, 0);
							new_board.ship_found[ship_set[k].type] = true;
							count = try_uncovered(new_board);
							if(count > 0)
							{
								if(total == 0)
								{
									tmp_board = new_board;
									det = true;
								}
								else if(memcmp(&tmp_board, &new_board, sizeof(tmp_board)) != 0)
									det = false;
								inc_intersection_flag(i, j, k, 0, count);
								total += count;
								if(total >= 30)
									return total;
							}
						}
					}
				}
			}
		}
	}
	if(det)
		board = tmp_board;
	return total;
}

bool solve(Board& board, bool allow_miss)
{
	int i, j, ret;
	
	// determine those that can be determined without a guess
	bool finished = true, has_change = false;
	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			if(board.sq[i][j] == SHIP)
			{
				ret = uncover(board, i, j);
				if(ret == 0)
					return false;
				else if(ret == 1)
					has_change = true;
				else
					finished = false;
			}
			else if(board.sq[i][j] == COVERED)
				finished = false;
		}
		
		if(i == height-1 && !finished && has_change)
		{
			i = -1;
			finished = true;
			has_change = false;
		}
	}
	
	if(finished)
		return true;
	
	mark_noship(board);
	
	// backtrack on different ship shapes for possible layouts
	init_intersection_flag();
	int cnt = try_uncovered(board);
	find_intersection(board, cnt);
	if(cnt == 0 || cnt >= 30)
		return false;
	else if(cnt == 1 || all_ships_found(board))
		return true;
	
	if(!allow_miss)
		return false;
	
	mark_noship(board);
	
	// try to guess with one miss
	Board new_board;
	for(i = 0; i < height; i++)
	{
		for(j = 0; j < width; j++)
		{
			if(board.sq[i][j] == COVERED)
			{
				new_board = board;
				new_board.sq[i][j] = NOSHIP;	// missed
				if(!solve(new_board, false))	// recursion
					continue;
				new_board = board;
				new_board.sq[i][j] = SHIP;	// hit
				if(solve(new_board, true))	// recursion
					return true;
			}
		}
	}
	
	return false;
}

int main()
{
	int i, tc(0);
	Board board;
	generate_all_ships();
	while(scanf("%d%d", &width, &height), width)
	{
		for(i = 0; i < height; i++)
			scanf("%s", board.sq[i]);
		memset(board.ship_found, false, sizeof(board.ship_found));
		if(solve(board, true))
			printf("Game #%d\nyes.\n\n", ++tc);
		else
			printf("Game #%d\nno.\n\n", ++tc);
	}
	return 0;
}