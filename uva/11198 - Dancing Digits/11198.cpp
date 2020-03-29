#include <stdio.h>
#include <string.h>
#include <set>
#include <queue>

bool prime[16] = { false, false, true, true, false, true, false, true, false, false, false, true, false, true, false, false };

struct State
{
	int digit[8];
	bool neg[8];
	int step;
};
std::set<int> key_set;

bool read_input(State &state)
{
	for(int i = 0; i < 8; i++)
	{
		scanf("%d", &state.digit[i]);
		if(state.digit[i] == 0)
			return false;
		if(state.digit[i] < 0)
		{
			state.digit[i] = -state.digit[i];
			state.neg[i] = true;
		}
		else
			state.neg[i] = false;
	}
	return true;
}

bool finished(const State &state)
{
	for(int i = 0; i < 8; i++)
		if(state.digit[i] != i+1)
			return false;
	return true;
}

int get_key(const State &state)
{
	int key = 0;
	for(int i = 0; i < 8; i++)
		key = key*10+state.digit[i];
	return key;
}

bool move(const State &state, int from, int to, State &new_state)
{
	int i;
	memcpy(&new_state, &state, sizeof(State));
	if(from < to)
	{
		if(state.neg[from] != state.neg[to] && prime[state.digit[from]+state.digit[to]] || to < 7 && state.neg[from] != state.neg[to+1] && prime[state.digit[from]+state.digit[to+1]])
		{
			new_state.digit[to] = state.digit[from];
			new_state.neg[to] = state.neg[from];
			for(i = from; i < to; i++)
			{
				new_state.digit[i] = state.digit[i+1];
				new_state.neg[i] = state.neg[i+1];
			}
			new_state.step++;
			return true;
		}
		else
			return false;
	}
	else	// from > to
	{
		if(state.neg[from] != state.neg[to] && prime[state.digit[from]+state.digit[to]] || to > 0 && state.neg[from] != state.neg[to-1] && prime[state.digit[from]+state.digit[to-1]])
		{
			new_state.digit[to] = state.digit[from];
			new_state.neg[to] = state.neg[from];
			for(i = to+1; i <= from; i++)
			{
				new_state.digit[i] = state.digit[i-1];
				new_state.neg[i] = state.neg[i-1];
			}
			new_state.step++;
			return true;
		}
		else
			return false;
	}
}

int bfs(const State &init)
{
	int i, j, key;
	State state, new_state;
	std::queue<State> sq;
	key_set.clear();
	if(finished(init))
		return 0;
	sq.push(init);
	key_set.insert(get_key(init));
	while(!sq.empty())
	{
		state = sq.front();
		sq.pop();
		for(i = 0; i < 8; i++)
		{
			for(j = 0; j < 8; j++)
			{
				if(i == j)
					continue;
				if(move(state, i, j, new_state))
				{
					key = get_key(new_state);
					if(key_set.insert(key).second == false)
						continue;
					if(finished(new_state))
						return new_state.step;
					sq.push(new_state);
				}
			}
		}
	}
	return -1;
}

int main()
{
	int tc(0);
	State state;
	while(true)
	{
		if(!read_input(state))
			break;
		state.step = 0;
		printf("Case %d: %d\n", ++tc, bfs(state)); 
	}
	return 0;
}
