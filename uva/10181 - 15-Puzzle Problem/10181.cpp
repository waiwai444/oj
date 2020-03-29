#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

const int MAX_STEPS = 50;
int man_dist[16][16];

struct BoardState {
	char board[16];
	int epos;
	int score;
	int step_num;
	char steps[MAX_STEPS+1];
};

bool operator < (const BoardState &bs1, const BoardState &bs2)
{
	return bs1.score>bs2.score;
}

inline void copy_board(char *dest, char *src)
{
	for(int i=0; i<16; i++)
		dest[i] = src[i];
}

inline void swap(char *board, int pos1, int pos2)
{
	char t = board[pos1];
	board[pos1] = board[pos2];
	board[pos2] = t;
}

// check if the initial layout can be solved, according to some results of math
inline bool solvable(char *board, int epos)
{
	int inversion;
	inversion = 0;
	for(int i=0; i<15; i++)
	{
		if(board[i]==1 || board[i]==0)
			continue;
		for(int j=i+1; j<16; j++)
		{
			if(board[j]!=0 && board[i]>board[j])
				inversion++;
		}
	}
	return ((inversion+epos/4+1)&1)==0;
}

inline bool finished(char *board)
{
	if(board[0]==1 && board[1]==2 && board[2]==3 && board[3]==4 && board[4]==5 && board[5]==6 && board[6]==7 \
		&& board[7]==8 && board[8]==9 && board[9]==10 && board[10]==11 && board[11]==12 && board[12]==13 && board[13]==14 && board[14]==15)
		return true;
	return false;
}

inline void get_steps(const BoardState &bs, vector<char> &steps)
{
	for(int i=0; i<bs.step_num; i++)
		steps.push_back(bs.steps[i]);
}

// calculate the Manhattan distances
inline void get_man_dist()
{
	int i, j;
	for(i=0; i<16; i++)
		for(j=0; j<16; j++)	// the cost for tile i (include empty slot) being placed in slot j
			man_dist[i][j] = abs(j/4-((i+15)%16)/4)+abs(j%4-((i+15)%16)%4);
}

// use Manhattan distance to score the board layout
inline int score(char *board, int step_num)
{
	int i, s;
	s = 0;
	for(i=0; i<16; i++)
		s += man_dist[board[i]][i];
	return 2*s+step_num;
}

// map the board to an integer as the key for the map container
inline long long board_to_key(char *board)
{
	long long key = 0;
	for(int i=0; i<16; i++)
		key = key*16+board[i];
	return key;
}

// move the empty slot in four directions
void generate_candidates(const BoardState &bs, priority_queue<BoardState> &board_queue, map<long long, int> &record)
{
	long long key;
	BoardState new_bs;
	map<long long, int>::iterator it;
	if(bs.epos!=0 && bs.epos!=4 && bs.epos!=8 && bs.epos!=12 && bs.steps[bs.step_num-1]!='R')
	{
		new_bs = bs;
		swap(new_bs.board, bs.epos, bs.epos-1);
		new_bs.epos = bs.epos-1;
		new_bs.steps[bs.step_num] = 'L';
		new_bs.step_num = bs.step_num+1;
		new_bs.score = score(new_bs.board, new_bs.step_num);
		key = board_to_key(new_bs.board);
		if((it=record.find(key))==record.end())
		{
			board_queue.push(new_bs);
			record[key] = new_bs.step_num;
		}
		else if(it->second>new_bs.step_num)
		{
			board_queue.push(new_bs);
			it->second = new_bs.step_num;
		}
	}
	if(bs.epos!=3 && bs.epos!=7 && bs.epos!=11 && bs.epos!=15 && bs.steps[bs.step_num-1]!='L')
	{
		new_bs = bs;
		swap(new_bs.board, bs.epos, bs.epos+1);
		new_bs.epos = bs.epos+1;
		new_bs.steps[bs.step_num] = 'R';
		new_bs.step_num = bs.step_num+1;
		new_bs.score = score(new_bs.board, new_bs.step_num);
		key = board_to_key(new_bs.board);
		if((it=record.find(key))==record.end())
		{
			board_queue.push(new_bs);
			record[key] = new_bs.step_num;
		}
		else if(it->second>new_bs.step_num)
		{
			board_queue.push(new_bs);
			it->second = new_bs.step_num;
		}
	}
	if(bs.epos!=0 && bs.epos!=1 && bs.epos!=2 && bs.epos!=3 && bs.steps[bs.step_num-1]!='D')
	{
		new_bs = bs;
		swap(new_bs.board, bs.epos, bs.epos-4);
		new_bs.epos = bs.epos-4;
		new_bs.steps[bs.step_num] = 'U';
		new_bs.step_num = bs.step_num+1;
		new_bs.score = score(new_bs.board, new_bs.step_num);
		key = board_to_key(new_bs.board);
		if((it=record.find(key))==record.end())
		{
			board_queue.push(new_bs);
			record[key] = new_bs.step_num;
		}
		else if(it->second>new_bs.step_num)
		{
			board_queue.push(new_bs);
			it->second = new_bs.step_num;
		}
	}
	if(bs.epos!=12 && bs.epos!=13 && bs.epos!=14 && bs.epos!=15 && bs.steps[bs.step_num-1]!='U')
	{
		new_bs = bs;
		swap(new_bs.board, bs.epos, bs.epos+4);
		new_bs.epos = bs.epos+4;
		new_bs.steps[bs.step_num] = 'D';
		new_bs.step_num = bs.step_num+1;
		new_bs.score = score(new_bs.board, new_bs.step_num);
		key = board_to_key(new_bs.board);
		if((it=record.find(key))==record.end())
		{
			board_queue.push(new_bs);
			record[key] = new_bs.step_num;
		}
		else if(it->second>new_bs.step_num)
		{
			board_queue.push(new_bs);
			it->second = new_bs.step_num;
		}
	}
}

bool a_star_search(char *init_board, int epos, vector<char> &steps)
{
	priority_queue<BoardState> board_queue;	// priority queue
	map<long long, int> record;

	BoardState bs;
	copy_board(bs.board, init_board);
	bs.epos = epos;
	bs.step_num = 0;
	//bs.steps[0] = '\0';
	bs.score = score(bs.board, bs.step_num);
	board_queue.push(bs);
	record[board_to_key(bs.board)] = 0;

	while(!board_queue.empty())
	{
		bs = board_queue.top();
		board_queue.pop();

		if(finished(bs.board))
		{
			get_steps(bs, steps);
			return true;
		}
		if(bs.step_num==50)
			continue;

		generate_candidates(bs, board_queue, record);
	}

	return false;
}

int main()
{
	int i, n, t;
	char board[16];
	int epos;
	vector<char> steps;
	steps.reserve(50);
	get_man_dist();
	cin>>n;
	while(n-->0)
	{
		for(i=0; i<16; i++)
		{
			cin>>t;
			board[i] = (char)t;
			if(t==0)
				epos = i;
		}
		if(!solvable(board, epos))
			cout<<"This puzzle is not solvable."<<endl;
		else
		{
			a_star_search(board, epos, steps);
			for(i=0; i<steps.size(); i++)
				cout<<steps[i];
			cout<<endl;
			steps.clear();
		}
	}
	return 0;
}