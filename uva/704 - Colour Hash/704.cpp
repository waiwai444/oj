
#include <stdio.h>
#include <queue>
#include <set>

#define LEFT_CLOCKWISE 1
#define RIGHT_CLOCKWISE 2
#define LEFT_COUNTERCLOCKWISE 3
#define RIGHT_COUNTERCLOCKWISE 4

using namespace std;

// represent the position
struct Position
{
	char pos[21];
	char& operator[](size_t i) { return pos[i]; }
	const char& operator[](size_t i) const { return pos[i]; }
	bool operator==(const Position& pos) const { for(int i = 0; i < 21; i++) if(this->pos[i] != pos.pos[i]) return false; return true; }
	bool operator!=(const Position& pos) const { return !(*this == pos); }
};

namespace std
{
	template<>
	class less<Position>
	{
	public:
		bool operator()(const Position& pos1, const Position& pos2) const
		{
			for(int i = 0; i < 21; i++)
				if(pos1[i] < pos2[i])
					return true;
				else if(pos1[i] > pos2[i])
					return false;
			return false;
		}
	};
}

// represent the operation path to the position from a initial position
struct Path
{
	char oper[16];
};

Position init_pos;
const Position final_pos = { { '0', '3', '4', '3', '0', '5', '6', '5', '0', '1', '2', '1', '0', '7', '8', '7', '0', '9', 'A', '9', '0' } };

set<Position> forward_rec;
set<Position> backward_rec;

queue<Position> forward;
queue<Position> backward;

queue<Path> forward_path;
queue<Path> backward_path;

inline void left_clockwise(const Position& cur_pos, Position& res_pos)
{
	int i;
	res_pos[1] = cur_pos[11];
	res_pos[0] = cur_pos[10];
	for(i = 9; i >= 0; i--)
		res_pos[i + 2] = cur_pos[i];
	for(i = 12; i <= 20; i++)
		res_pos[i] = cur_pos[i];
}

inline void right_clockwise(const Position& cur_pos, Position& res_pos)
{
	int i;
	res_pos[19] = cur_pos[9];
	res_pos[20] = cur_pos[10];
	for(i = 11; i <= 20; i++)
		res_pos[i - 2] = cur_pos[i];
	for(i = 0; i <= 8; i++)
		res_pos[i] = cur_pos[i];
}

inline void left_counterclockwise(const Position& cur_pos, Position& res_pos)
{
	int i;
	res_pos[10] = cur_pos[0];
	res_pos[11] = cur_pos[1];
	for(i = 2; i <= 11; i++)
		res_pos[i - 2] = cur_pos[i];
	for(i = 12; i <= 20; i++)
		res_pos[i] = cur_pos[i];
}

inline void right_counterclockwise(const Position& cur_pos, Position& res_pos)
{
	int i;
	res_pos[10] = cur_pos[20];
	res_pos[9] = cur_pos[19];
	for(i = 18; i >= 9; i--)
		res_pos[i + 2] = cur_pos[i];
	for(i = 0; i <= 8; i++)
		res_pos[i] = cur_pos[i];
}

// bi-directional bfs
bool bbfs()
{
	int i, j;
	bool ffound = false;
	bool bfound = false;
	int fcount, bcount;
	Position cur_pos, new_pos;
	forward.push(init_pos);
	backward.push(final_pos);
	forward_rec.insert(init_pos);
	backward_rec.insert(final_pos);

	Path cur_path;
	forward_path.push(cur_path);
	backward_path.push(cur_path);

	fcount = bcount = 1;
	for(i = 1; i <= 8; i++)		// consider at most 16 steps
	{
		// forward search
		while(fcount--)
		{
			cur_pos = forward.front();
			forward.pop();
			cur_path = forward_path.front();
			forward_path.pop();
			for(j = LEFT_CLOCKWISE; j <= RIGHT_COUNTERCLOCKWISE; j++)
			{
				switch(j)
				{
				case LEFT_CLOCKWISE:
					left_clockwise(cur_pos, new_pos);
					break;
				case RIGHT_CLOCKWISE:
					right_clockwise(cur_pos, new_pos);
					break;
				case LEFT_COUNTERCLOCKWISE:
					left_counterclockwise(cur_pos, new_pos);
					break;
				case RIGHT_COUNTERCLOCKWISE:
					right_counterclockwise(cur_pos, new_pos);
					break;
				}
				cur_path.oper[i - 1] = j;
				if(backward_rec.find(new_pos) != backward_rec.end())
				{
					ffound = true;
					goto out;
				}
				if(forward_rec.find(new_pos) == forward_rec.end())
				{
					forward.push(new_pos);
					forward_path.push(cur_path);
					forward_rec.insert(new_pos);
				}
			}
		}
		fcount = forward.size();
		// backward search
		while(bcount--)
		{
			cur_pos = backward.front();
			backward.pop();
			cur_path = backward_path.front();
			backward_path.pop();
			for(j = LEFT_CLOCKWISE; j <= RIGHT_COUNTERCLOCKWISE; j++)
			{
				switch(j)
				{
				case LEFT_CLOCKWISE:
					left_clockwise(cur_pos, new_pos);
					break;
				case RIGHT_CLOCKWISE:
					right_clockwise(cur_pos, new_pos);
					break;
				case LEFT_COUNTERCLOCKWISE:
					left_counterclockwise(cur_pos, new_pos);
					break;
				case RIGHT_COUNTERCLOCKWISE:
					right_counterclockwise(cur_pos, new_pos);
					break;
				}
				cur_path.oper[i - 1] = j;
				if(forward_rec.find(new_pos) != forward_rec.end())
				{
					bfound = true;
					goto out;
				}
				if(backward_rec.find(new_pos) == backward_rec.end())
				{
					backward.push(new_pos);
					backward_path.push(cur_path);
					backward_rec.insert(new_pos);
				}
			}
		}
		bcount = backward.size();
	}
out:
	if(ffound)
	{
		while(1)
		{
			if(backward.front() != new_pos)
			{
				backward.pop();
				backward_path.pop();
			}
			else
			{
				for(j = 0; j < i; j++)
					printf("%d", cur_path.oper[j]);
				for(j = i - 2; j >= 0; j--)
				{
					switch(backward_path.front().oper[j])
					{
					case LEFT_CLOCKWISE:
						printf("%d", LEFT_COUNTERCLOCKWISE);
						break;
					case RIGHT_CLOCKWISE:
						printf("%d", RIGHT_COUNTERCLOCKWISE);
						break;
					case LEFT_COUNTERCLOCKWISE:
						printf("%d", LEFT_CLOCKWISE);
						break;
					case RIGHT_COUNTERCLOCKWISE:
						printf("%d", RIGHT_CLOCKWISE);
						break; 
					}
				}
				printf("\n");
				return true;
			}
		}
	}
	if(bfound)
	{
		while(1)
		{
			if(forward.front() != new_pos)
			{
				forward.pop();
				forward_path.pop();
			}
			else
			{
				for(j = 0; j < i; j++)
					printf("%d", forward_path.front().oper[j]);
				for(j = i - 1; j >= 0; j--)
				{
					switch(cur_path.oper[j])
					{
					case LEFT_CLOCKWISE:
						printf("%d", LEFT_COUNTERCLOCKWISE);
						break;
					case RIGHT_CLOCKWISE:
						printf("%d", RIGHT_COUNTERCLOCKWISE);
						break;
					case LEFT_COUNTERCLOCKWISE:
						printf("%d", LEFT_CLOCKWISE);
						break;
					case RIGHT_COUNTERCLOCKWISE:
						printf("%d", RIGHT_CLOCKWISE);
						break; 
					}
				}
				printf("\n");
				return true;
			}
		}
	}
	return false;
}

int main()
{
	int i, j, k, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < 21; j++)
		{
			scanf("%d", &k);
			init_pos[j] = (k == 10) ? 'A' : '0' + k;
		}
		for(j = 0; j < 3; j++)
			scanf("%d", &k);
		if(init_pos == final_pos)
		{
			printf("PUZZLE ALREADY SOLVED\n");
			continue;
		}
		if(!bbfs())
			printf("NO SOLUTION WAS FOUND IN 16 STEPS\n");
		if(i < n - 1)
		{
			forward_rec.clear();
			backward_rec.clear();
			while(!forward.empty())
				forward.pop();
			while(!backward.empty())
				backward.pop();
			while(!forward_path.empty())
				forward_path.pop();
			while(!backward_path.empty())
				backward_path.pop();
		}
	}
	return 0;
}
